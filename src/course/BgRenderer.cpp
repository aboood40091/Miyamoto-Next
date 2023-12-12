#include <course/Bg.h>
#include <course/BgTexMgr.h>
#include <course/BgUnitFile.h>
#include <course/BgRenderer.h>
#include <course/CourseDataFile.h>

#include <gpu/rio_Drawer.h>
#include <math/rio_Matrix.h>
#include <misc/rio_MemUtil.h>

BgRenderer* BgRenderer::sInstance = nullptr;

bool BgRenderer::createSingleton()
{
    if (sInstance)
        return false;

    sInstance = new BgRenderer();
    return true;
}

void BgRenderer::destroySingleton()
{
    if (!sInstance)
        return;

    delete sInstance;
    sInstance = nullptr;
}

BgRenderer::BgRenderer()
    : mShader()
    , mVertexBuffer(0)
    , mSelectionVertexBuffer(1)
    , mPosStream()
    , mTexStream()
    , mItemIDStream()
    , mIsSelectedStream()
    , mVertexArray()
    , mpCamera(nullptr)
    , mpProjection(nullptr)
    , mTextureSampler()
{
    mTextureSampler.setMinFilter(rio::TEX_XY_FILTER_MODE_LINEAR);
    mTextureSampler.setMagFilter(rio::TEX_XY_FILTER_MODE_LINEAR);
    mTextureSampler.setMipFilter(rio::TEX_MIP_FILTER_MODE_LINEAR);

    rio::MemUtil::set(mDrawNum, 0, sizeof(mDrawNum));
    rio::MemUtil::set(mDynamicDrawNum, 0, sizeof(mDynamicDrawNum));

    initialize_();
}

BgRenderer::~BgRenderer()
{
    destroy_();
}

void BgRenderer::initialize_()
{
    // destroy_();

    constexpr u32 block_max_num = BG_MAX_UNIT_X * BG_MAX_UNIT_Y * CD_FILE_LAYER_MAX_NUM
                                + cDynamicMaxNum * CD_FILE_ENV_MAX_NUM * CD_FILE_LAYER_MAX_NUM;

    constexpr size_t vtx_data_size = sizeof(Vertex) * cVtxPerBlock * block_max_num;
    constexpr size_t sel_data_size = sizeof(   s32) * cVtxPerBlock * block_max_num;
    constexpr size_t idx_data_size = sizeof(   u32) * cIdxPerBlock * block_max_num;

    Vertex* vtx_data = static_cast<Vertex*>(rio::MemUtil::alloc(vtx_data_size, rio::Drawer::cVtxAlignment));
    s32*    sel_data = static_cast<   s32*>(rio::MemUtil::alloc(sel_data_size, rio::Drawer::cVtxAlignment));
    u32*    idx_data = static_cast<   u32*>(rio::MemUtil::alloc(idx_data_size, rio::Drawer::cIdxAlignment));

    RIO_ASSERT(vtx_data != nullptr);
    RIO_ASSERT(sel_data != nullptr);
    RIO_ASSERT(idx_data != nullptr);

    mVtxData = std::span{ vtx_data, vtx_data_size };
    mSelData = std::span{ sel_data, sel_data_size };
    mIdxData = std::span{ idx_data, idx_data_size };

    rio::MemUtil::set(vtx_data, 0, vtx_data_size);
    rio::MemUtil::set(sel_data, 0, sel_data_size);

    for (u32 i = 0; i < block_max_num; i++)
    {
        idx_data[i * cIdxPerBlock + 0] = i * cVtxPerBlock + 0;  // Top left
        idx_data[i * cIdxPerBlock + 1] = i * cVtxPerBlock + 1;  // Bottom left
        idx_data[i * cIdxPerBlock + 2] = i * cVtxPerBlock + 2;  // Bottom right
        idx_data[i * cIdxPerBlock + 3] = i * cVtxPerBlock + 2;  // Bottom right
        idx_data[i * cIdxPerBlock + 4] = i * cVtxPerBlock + 3;  // Top right
        idx_data[i * cIdxPerBlock + 5] = i * cVtxPerBlock + 0;  // Top left
    }

    rio::VertexBuffer::invalidateCache(idx_data, idx_data_size);

    mShader.load("bg_renderer", rio::Shader::MODE_UNIFORM_REGISTER);
    mMVPLocation = mShader.getVertexUniformLocation("mvp");
    mTexLocation = mShader.getFragmentSamplerLocation("texture0");

    mVertexBuffer.setStride(sizeof(Vertex));
    mVertexBuffer.setData(vtx_data, vtx_data_size);

    mSelectionVertexBuffer.setStride(sizeof(s32));
    mSelectionVertexBuffer.setDataInvalidate(sel_data, sel_data_size);

    mPosStream   .setLayout(0, rio::VertexStream::FORMAT_32_32_32_FLOAT, offsetof(Vertex, pos));
    mTexStream   .setLayout(1, rio::VertexStream::FORMAT_32_32_FLOAT,    offsetof(Vertex, tex));
    mItemIDStream.setLayout(2, rio::VertexStream::FORMAT_32_UINT,        offsetof(Vertex, item_id));

    mVertexArray.addAttribute(mPosStream,       mVertexBuffer);
    mVertexArray.addAttribute(mTexStream,       mVertexBuffer);
    mVertexArray.addAttribute(mItemIDStream,    mVertexBuffer);

    mIsSelectedStream.setLayout(3, rio::VertexStream::FORMAT_32_SINT, 0);
    mVertexArray.addAttribute(mIsSelectedStream, mSelectionVertexBuffer);

    mVertexArray.process();
}

void BgRenderer::destroy_()
{
    if (!mVtxData.data())
        return;

    mShader.unload();

    RIO_ASSERT(mVtxData.data() != nullptr);
    RIO_ASSERT(mSelData.data() != nullptr);
    RIO_ASSERT(mIdxData.data() != nullptr);

    rio::MemUtil::free(mVtxData.data());
    rio::MemUtil::free(mSelData.data());
    rio::MemUtil::free(mIdxData.data());

    mVtxData = std::span<Vertex>();
    mSelData = std::span<   s32>();
    mIdxData = std::span<   u32>();
}

void BgRenderer::setUnitVertexBuffer_(Vertex* vtx_data, const rio::BaseVec3f& tl_pos, u8 unit_idx, ItemID item_id)
{
    Vertex& vtx_tl = vtx_data[0];
    Vertex& vtx_bl = vtx_data[1];
    Vertex& vtx_br = vtx_data[2];
    Vertex& vtx_tr = vtx_data[3];

    vtx_tr.pos.x = tl_pos.x + 16;
    vtx_tr.pos.y = tl_pos.y;
    vtx_tr.pos.z = tl_pos.z;

    vtx_br.pos.x = tl_pos.x + 16;
    vtx_br.pos.y = tl_pos.y - 16;
    vtx_br.pos.z = tl_pos.z;

    vtx_bl.pos.x = tl_pos.x;
    vtx_bl.pos.y = tl_pos.y - 16;
    vtx_bl.pos.z = tl_pos.z;

    vtx_tl.pos = tl_pos;

    const u32 row = unit_idx / cUnitsPerRow;
    const u32 col = unit_idx % cUnitsPerRow;
    RIO_ASSERT(row < cUnitsPerColumn);
    RIO_ASSERT(col < cUnitsPerRow);

    vtx_tr.tex.x = (col + 1) * cUnitSizePadXNorm - cPadXNorm;
    vtx_tr.tex.y = row * cUnitSizePadYNorm + cPadYNorm;

    vtx_br.tex.x = (col + 1) * cUnitSizePadXNorm - cPadXNorm;
    vtx_br.tex.y = (row + 1) * cUnitSizePadYNorm - cPadYNorm;

    vtx_bl.tex.x = col * cUnitSizePadXNorm + cPadXNorm;
    vtx_bl.tex.y = (row + 1) * cUnitSizePadYNorm - cPadYNorm;

    vtx_tl.tex.x = col * cUnitSizePadXNorm + cPadXNorm;
    vtx_tl.tex.y = row * cUnitSizePadYNorm + cPadYNorm;

    vtx_tr.item_id = item_id;
    vtx_br.item_id = item_id;
    vtx_bl.item_id = item_id;
    vtx_tl.item_id = item_id;
}

void BgRenderer::createVertexBuffer(u8 layer)
{
    f32 z;
    switch (layer)
    {
    case LAYER_0:
        z = 3600.0f;
        break;
    case LAYER_1:
    default:
        z = 0.0f;
        break;
    case LAYER_2:
        z = -3500.0f;
        break;
    }

    const Bg::UnitMtx& bg_unit_mtx = Bg::instance()->getUnitMtx();

    Vertex* const base_vtx_data = mVtxData.data();

    u32 block_count = BG_MAX_UNIT_X * BG_MAX_UNIT_Y * u32(layer);

    for (s32 env = 0; env < CD_FILE_ENV_MAX_NUM; env++)
    {
        u32 block_start = block_count;

        for (s32 y = 0; y < BG_MAX_UNIT_Y; y++)
        {
            for (s32 x = 0; x < BG_MAX_UNIT_X; x++)
            {
                const Bg::Unit& unit = bg_unit_mtx[layer][y][x];
                if (!unit.value || env != unit.value >> 8)
                    continue;

                u8 unit_idx = unit.value & 0xff;

                setUnitVertexBuffer_(
                    base_vtx_data + cVtxPerBlock * block_count,
                    rio::BaseVec3f { f32(x * 16), f32(-y * 16), z },
                    unit_idx,
                    ItemID(ITEM_TYPE_BG_UNIT_OBJ, u32(layer) << 22 | unit.obj_index)
                );

                block_count++;
            }
        }

        u32 draw_num = block_count - block_start;
        mDrawNum[layer][env] = draw_num;
        if (draw_num == 0)
            continue;

        u32 vtx_start = cVtxPerBlock * block_start;
        u32 vtx_count = cVtxPerBlock * draw_num;

        mVertexBuffer.setSubDataInvalidate(base_vtx_data + vtx_start, sizeof(Vertex) * vtx_start, sizeof(Vertex) * vtx_count);
    }
}

void BgRenderer::drawUnit(ItemID item_id, const rio::BaseVec3f& tl_pos, UnitID unit, u8 layer)
{
    s32 env = unit >> 8;
    u8 unit_idx = unit & 0xFF;
    RIO_ASSERT(env < CD_FILE_ENV_MAX_NUM);

    RIO_ASSERT(layer < CD_FILE_LAYER_MAX_NUM);

    if (mDynamicDrawNum[layer][env] == cDynamicMaxNum)
        return;

    Vertex* const base_vtx_data = mVtxData.data();

    u32 block_start = BG_MAX_UNIT_X * BG_MAX_UNIT_Y * CD_FILE_LAYER_MAX_NUM
                    + cDynamicMaxNum * env * layer;

    u32 index = block_start + mDynamicDrawNum[layer][env];

    setUnitVertexBuffer_(base_vtx_data + cVtxPerBlock * index, tl_pos, unit_idx, item_id);

    mDynamicDrawNum[layer][env]++;

    u32 vtx_start = cVtxPerBlock * index;
    u32 vtx_count = cVtxPerBlock;

    mVertexBuffer.setSubDataInvalidate(base_vtx_data + vtx_start, sizeof(Vertex) * vtx_start, sizeof(Vertex) * vtx_count);
}

void BgRenderer::calcSelectionVertexBuffer(const std::vector<ItemID>& selected_items)
{
    if (selected_items.empty())
    {
        rio::MemUtil::set(mSelData.data(), 0, mSelData.size());
        mSelectionVertexBuffer.setSubDataInvalidate(mSelData.data(), 0, mSelData.size());
        return;
    }

    const Vertex* const base_vtx_data = mVtxData.data();
    s32* const base_sel_data = mSelData.data();

    for (u8 layer = 0; layer < CD_FILE_LAYER_MAX_NUM; layer++)
    {
        u32 index = BG_MAX_UNIT_X * BG_MAX_UNIT_Y * u32(layer);
        u32 start = index;

        for (s32 env = 0; env < CD_FILE_ENV_MAX_NUM; env++)
        {
            u32 draw_num = mDrawNum[layer][env];
            if (draw_num)
            {
                for (u32 j = 0; j < draw_num; j++)
                {
                    const Vertex* const vtx_data = base_vtx_data + cVtxPerBlock * index;
                    s32* const sel_data = base_sel_data + cVtxPerBlock * index;

                    const ItemID& item_id = vtx_data->item_id;
                    RIO_ASSERT(item_id.isValid());

                    bool is_selected = std::find(selected_items.begin(), selected_items.end(), item_id) != selected_items.end();

                    sel_data[0] = is_selected;
                    sel_data[1] = is_selected;
                    sel_data[2] = is_selected;
                    sel_data[3] = is_selected;

                    index++;
                }
            }

            u32 dynamic_start = BG_MAX_UNIT_X * BG_MAX_UNIT_Y * CD_FILE_LAYER_MAX_NUM
                              + cDynamicMaxNum * env * layer;

            u32 dynamic_draw_num = mDynamicDrawNum[layer][env];
            if (dynamic_draw_num)
            {
                for (u32 j = 0; j < dynamic_draw_num; j++)
                {
                    u32 dynamic_index = dynamic_start + j;

                    const Vertex* const vtx_data = base_vtx_data + cVtxPerBlock * dynamic_index;
                    s32* const sel_data = base_sel_data + cVtxPerBlock * dynamic_index;

                    const ItemID& item_id = vtx_data->item_id;
                    RIO_ASSERT(item_id.isValid());

                    bool is_selected = std::find(selected_items.begin(), selected_items.end(), item_id) != selected_items.end();

                    sel_data[0] = is_selected;
                    sel_data[1] = is_selected;
                    sel_data[2] = is_selected;
                    sel_data[3] = is_selected;
                }

                u32 vtx_start = cVtxPerBlock * dynamic_start;
                u32 vtx_count = cVtxPerBlock * dynamic_draw_num;

                mSelectionVertexBuffer.setSubDataInvalidate(base_sel_data + vtx_start, sizeof(s32) * vtx_start, sizeof(s32) * vtx_count);
            }
        }

        u32 num = index - start;
        if (num == 0)
            continue;

        u32 vtx_start = cVtxPerBlock * start;
        u32 vtx_count = cVtxPerBlock * num;

        mSelectionVertexBuffer.setSubDataInvalidate(base_sel_data + vtx_start, sizeof(s32) * vtx_start, sizeof(s32) * vtx_count);
    }
}

void BgRenderer::render(u8 layer, const CourseDataFile& cd_file, bool render_static, bool render_dynamic, bool render_normal)
{
    if (!render_static && !render_dynamic)
    {
        rio::MemUtil::set(mDynamicDrawNum[layer], 0, sizeof(mDynamicDrawNum[layer]));
        return;
    }

    RIO_ASSERT(mpCamera != nullptr);
    RIO_ASSERT(mpProjection != nullptr);

    rio::Matrix34f view;
    mpCamera->getMatrix(&view);

    const rio::Matrix44f& proj =
        static_cast<const rio::Matrix44f&>(mpProjection->getMatrix());

    rio::Matrix44f view_proj;
    view_proj.setMul(proj, view);

    mShader.bind();
    mVertexArray.bind();

    mShader.setUniformArray(4, &view_proj.v[0], mMVPLocation, u32(-1));

    const BgUnitFile* bg_unit_file[CD_FILE_ENV_MAX_NUM] = {
        Bg::instance()->getUnitFile(cd_file.getEnvironment(0)),
        Bg::instance()->getUnitFile(cd_file.getEnvironment(1)),
        Bg::instance()->getUnitFile(cd_file.getEnvironment(2)),
        Bg::instance()->getUnitFile(cd_file.getEnvironment(3))
    };

    const u32* const base_idx_data = mIdxData.data();

    u32 block_count = BG_MAX_UNIT_X * BG_MAX_UNIT_Y * u32(layer);

    for (s32 env = 0; env < CD_FILE_ENV_MAX_NUM; env++)
    {
        u32 draw_num = mDrawNum[layer][env];
        u32 dynamic_draw_num = mDynamicDrawNum[layer][env];

        if ((draw_num && render_static) || (dynamic_draw_num && render_dynamic))
        {
            RIO_ASSERT(bg_unit_file[env] != nullptr);

            const rio::Texture2D* p_texture = env == 0 ? &BgTexMgr::instance()->getTexColor() : bg_unit_file[env]->getTexture();
            const rio::Texture2D* p_nml_texture = bg_unit_file[env]->getNormalTexture();

            RIO_ASSERT(p_texture && p_nml_texture);

            mTextureSampler.linkTexture2D(
                render_normal
                    ? p_nml_texture
                    : p_texture
            );
            mTextureSampler.bindFS(mTexLocation, 0);
        }

        if (draw_num && render_static)
        {
            u32 block_start = block_count;

            u32 idx_start = cIdxPerBlock * block_start;
            u32 idx_count = cIdxPerBlock * draw_num;

            rio::Drawer::DrawElements(rio::Drawer::TRIANGLES, idx_count, base_idx_data + idx_start);

            block_count += draw_num;
        }

        if (dynamic_draw_num && render_dynamic)
        {
            u32 block_start = BG_MAX_UNIT_X * BG_MAX_UNIT_Y * CD_FILE_LAYER_MAX_NUM
                            + cDynamicMaxNum * env * layer;

            u32 idx_start = cIdxPerBlock * block_start;
            u32 idx_count = cIdxPerBlock * dynamic_draw_num;

            rio::Drawer::DrawElements(rio::Drawer::TRIANGLES, idx_count, base_idx_data + idx_start);
        }
    }

    rio::MemUtil::set(mDynamicDrawNum[layer], 0, sizeof(mDynamicDrawNum[layer]));
}
