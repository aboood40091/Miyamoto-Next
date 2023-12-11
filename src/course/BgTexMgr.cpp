#include <course/Bg.h>
#include <course/BgUnitFile.h>
#include <course/CourseDataFile.h>
#include <course/BgTexMgr.h>
#include <graphics/RenderObjLayer.h>

#include <gfx/rio_Window.h>
#include <gpu/rio_RenderState.h>
#include <misc/rio_MemUtil.h>
#include <utility/aglDevTools.h>

static const s32 cTexWidthI = 2048;
static const f32 cTexWidth = cTexWidthI;
static const s32 cTexHeightI = 512;
static const f32 cTexHeight = cTexHeightI;
static const s32 cUnitSizeI = 64;
static const f32 cUnitSize = cUnitSizeI;
static const s32 cUnitSizeNoPadI = 60;
static const f32 cUnitSizeNoPad = cUnitSizeNoPadI;
static const s32 cUnitPerRow = cTexWidthI / cUnitSizeI;
static const s32 cUnitPerRowReal = 16;  // sqrt(cTexWidthI * cTexHeightI) / cUnitSizeI
//static const s32 cUnitPerColumn = cTexHeightI / cUnitSizeI;

BgTexMgr* BgTexMgr::sInstance = nullptr;

bool BgTexMgr::createSingleton()
{
    if (sInstance)
        return false;

    sInstance = new BgTexMgr();
    return true;
}

void BgTexMgr::destroySingleton()
{
    if (!sInstance)
        return;

    delete sInstance;
    sInstance = nullptr;
}

BgTexMgr::BgTexMgr()
    : mDrawCallback(*this)
    , mTexRenderBuffer(cTexWidthI, cTexHeightI)
    , mTexColor(rio::TEXTURE_FORMAT_R8_G8_B8_A8_UNORM, cTexWidthI, cTexHeightI, 1)
    , mTexDepth(rio::DEPTH_TEXTURE_FORMAT_R32_FLOAT, cTexWidthI, cTexHeightI, 1)
    , mOverridesType(OVERRIDES_NORMAL)
    , mOverridesDrawn(false)
    , mItemsTexture("Items")
{
    rio::MemUtil::set(mBgUnitFile, 0, sizeof(mBgUnitFile));

    mTexColorTarget.linkTexture2D(mTexColor);
    mTexRenderBuffer.setRenderTargetColor(&mTexColorTarget);

    mTexDepthTarget.linkTexture2D(mTexDepth);
    mTexRenderBuffer.setRenderTargetDepth(&mTexDepthTarget);

    rio::MemUtil::set(mDelayTimer, 0, sizeof(mDelayTimer));
    rio::MemUtil::set(mFrame, 0, sizeof(mFrame));

    static const char* const cOverridesFilenames[OVERRIDES_MAX] = {
        "Overrides/Normal",
        "Overrides/Forest",
        "Overrides/Sky",
        "Overrides/Underground"
    };

    for (s32 i = 0; i < OVERRIDES_MAX; i++)
        mOverrides[i] = new rio::Texture2D(cOverridesFilenames[i]);
}

BgTexMgr::~BgTexMgr()
{
    for (s32 i = 0; i < OVERRIDES_MAX; i++)
        delete mOverrides[i];
}

void BgTexMgr::initialize(const CourseDataFile& cd_file, RenderObjLayer* p_bg_prepare_layer)
{
    rio::MemUtil::set(mDelayTimer, 0, sizeof(mDelayTimer));
    rio::MemUtil::set(mFrame, 0, sizeof(mFrame));

    mOverridesDrawn = false;

    for (s32 env = 0; env < CD_FILE_ENV_MAX_NUM; env++)
        mBgUnitFile[env] = Bg::instance()->getUnitFile(cd_file.getEnvironment(env));

    RIO_ASSERT(mBgUnitFile[0] != nullptr);

    createUnitDefaultRender_();

    p_bg_prepare_layer->initialize();
    p_bg_prepare_layer->addDrawMethod(RenderObjLayer::cRenderStep_UpdateGPUBuffer, rio::lyr::DrawMethod(this, &BgTexMgr::drawXlu_));
    p_bg_prepare_layer->getRenderMgr()->setDrawCallback(&mDrawCallback);
}

void BgTexMgr::destroy(RenderObjLayer* p_bg_prepare_layer)
{
    rio::MemUtil::set(mBgUnitFile, 0, sizeof(mBgUnitFile));

    clearUnitDefaultRender_();

    p_bg_prepare_layer->getRenderMgr()->setDrawCallback(nullptr);
    p_bg_prepare_layer->clearDrawMethodsAll();
    p_bg_prepare_layer->clearRenderSteps();
}

void BgTexMgr::bindTexRenderBuffer_() const
{
    mTexRenderBuffer.bind();
}

void BgTexMgr::restoreFramebuffer_()
{
    rio::Window::instance()->makeContextCurrent();

    u32 width = rio::Window::instance()->getWidth();
    u32 height = rio::Window::instance()->getHeight();

    rio::Graphics::setViewport(0, 0, width, height);
    rio::Graphics::setScissor(0, 0, width, height);
}

static const s32 cFrameDelayHatena          [16] = {  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
static const s32 cFrameDelayBlock           [16] = { 78, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
static const s32 cFrameDelayTukaCoin        [ 8] = {  8, 8, 8, 8, 8, 8, 8, 8 };
static const s32 cFrameDelayBeltConveyor    [ 8] = {  2, 2, 2, 2, 2, 2, 2, 2 };
static const s32 cFrameDelayBeltConveyorF   [ 8] = {  1, 1, 1, 1, 1, 1, 1, 1 };

const BgTexMgr::AnimeInfo BgTexMgr::cAnimeInfo[ANIME_INFO_TYPE_MAX] = {
    { false,  true, cFrameDelayHatena,          sizeof(cFrameDelayHatena)           / sizeof(s32), ANIME_TYPE_HATENA },
    { false,  true, cFrameDelayBlock,           sizeof(cFrameDelayBlock)            / sizeof(s32), ANIME_TYPE_BLOCK },
    { false,  true, cFrameDelayTukaCoin,        sizeof(cFrameDelayTukaCoin)         / sizeof(s32), ANIME_TYPE_TUKA_COIN },
    { false, false, cFrameDelayBeltConveyor,    sizeof(cFrameDelayBeltConveyor)     / sizeof(s32), ANIME_TYPE_BELT_CONVEYOR },
    {  true, false, cFrameDelayBeltConveyor,    sizeof(cFrameDelayBeltConveyor)     / sizeof(s32), ANIME_TYPE_BELT_CONVEYOR },
    { false, false, cFrameDelayBeltConveyorF,   sizeof(cFrameDelayBeltConveyorF)    / sizeof(s32), ANIME_TYPE_BELT_CONVEYOR },
    {  true, false, cFrameDelayBeltConveyorF,   sizeof(cFrameDelayBeltConveyorF)    / sizeof(s32), ANIME_TYPE_BELT_CONVEYOR },
    { false,  true, cFrameDelayHatena,          sizeof(cFrameDelayHatena)           / sizeof(s32), ANIME_TYPE_HATENA_L },
    { false,  true, cFrameDelayBlock,           sizeof(cFrameDelayBlock)            / sizeof(s32), ANIME_TYPE_BLOCK_L }
};

const UnitID BgTexMgr::cAnimeInfoUnitID[ANIME_INFO_TYPE_MAX] = {
    cUnitID_QBlock,
    cUnitID_BrickBlock,
    cUnitID_CoinDash,
    cUnitID_ConveyorLeft_0,
    cUnitID_ConveyorRight_0,
    cUnitID_ConveyorLeftFast_0,
    cUnitID_ConveyorRightFast_0,
    UnitID(114),
    UnitID(112)
};

void BgTexMgr::update()
{
    for (s32 i = 0; i < ANIME_INFO_TYPE_MAX; i++)
    {
        const AnimeInfo& anime_info = cAnimeInfo[i];

        if (mDelayTimer[i] < anime_info.frame_delay[mFrame[i]] - 1)
            mDelayTimer[i]++;

        else
        {
            mDelayTimer[i] = 0;
            if (!anime_info.reverse)
            {
                if (mFrame[i] >= anime_info.frame_num - 1)
                    mFrame[i] = 0;

                else
                    mFrame[i]++;
            }
            else
            {
                if (mFrame[i] > 0)
                    mFrame[i]--;

                else
                    mFrame[i] = anime_info.frame_num - 1;
            }
        }
    }
}

static inline void drawAnime(UnitID unit, s32 frame, const rio::Texture2D* texture, bool square, const rio::BaseMtx44f& proj_mtx)
{
    RIO_ASSERT(unit < cUnitID_Pa0_Unit_Num);
    RIO_ASSERT(texture != nullptr);

    u8 unit_idx = unit & 0xFF;

    u32 tex_width = texture->getWidth();
    u32 tex_height = texture->getHeight();

    agl::TextureSampler sampler(*texture);

    s32 size =
        square
            ? tex_width / cUnitSizeI
            : 1;

    for (s32 i = 0; i < size; i++)
    {
        rio::Matrix34f mtx;
        mtx.makeST(
            { f32(tex_width), cUnitSize, 1.0f },
            { ((unit_idx + i * cUnitPerRowReal) % cUnitPerRow) * cUnitSize + tex_width * 0.5f, cTexHeight + cUnitSize * 0.5f - ((unit_idx + i * cUnitPerRowReal) / cUnitPerRow + 1) * cUnitSize, 0.0f }
        );

        agl::utl::DevTools::drawTextureTexCoord(
            sampler, mtx, proj_mtx,
            { 1.0f, cUnitSize / f32(tex_height) },
            0.0f,
            { 0.0f, frame * size + i - tex_height / cUnitSize * 0.5f + 0.5f },
            agl::cShaderMode_Invalid
        );
    }
}

static inline void drawTexture(const rio::Texture2D* texture, const rio::BaseMtx44f& proj_mtx)
{
    RIO_ASSERT(texture != nullptr);

    agl::TextureSampler sampler(*texture);

    rio::Matrix34f mtx;
    mtx.makeST(
        { cTexWidth, cTexHeight, 1.0f },
        { cTexWidth * 0.5f, cTexHeight * 0.5f, 0.0f }
    );

    agl::utl::DevTools::drawTextureTexCoord(
        sampler, mtx, proj_mtx,
        { 1.0f, 1.0f },
        0.0f,
        { 0.0f, 0.0f },
        agl::cShaderMode_Invalid
    );
}

static inline void drawItem(UnitID unit, BgTexMgr::ItemType type, const rio::Texture2D& texture, const rio::BaseMtx44f& proj_mtx)
{
    RIO_ASSERT(unit < cUnitID_Pa0_Unit_Num);
    RIO_ASSERT(type < BgTexMgr::ITEM_MAX);

    u8 unit_idx = unit & 0xFF;

    agl::TextureSampler sampler(texture);

    rio::Matrix34f mtx;
    mtx.makeST(
        { cUnitSizeNoPad, cUnitSizeNoPad, 1.0f },
        { (unit_idx % cUnitPerRow) * cUnitSize + cUnitSize * 0.5f, cTexHeight - (unit_idx / cUnitPerRow + 1) * cUnitSize + cUnitSize * 0.5f, 0.0f }
    );

    agl::utl::DevTools::drawTextureTexCoord(
        sampler, mtx, proj_mtx,
        { 1.0f / s32(BgTexMgr::ITEM_MAX), 1.0f },
        0.0f,
        { s32(type) - s32(BgTexMgr::ITEM_MAX) * 0.5f + 0.5f, 0.0f },
        agl::cShaderMode_Invalid
    );
}

const BgTexMgr::ItemOverrideInfo BgTexMgr::cItemOverrideInfo[cItemOverrideNum] = {
    { BgTexMgr::ANIME_INFO_TYPE_BLOCK,  cUnitID_BrickBlockFireFlower,   BgTexMgr::ITEM_FIRE_FLOWER },
    { BgTexMgr::ANIME_INFO_TYPE_BLOCK,  cUnitID_BrickBlockStar,         BgTexMgr::ITEM_STAR },
    { BgTexMgr::ANIME_INFO_TYPE_BLOCK,  cUnitID_BrickBlock1UP,          BgTexMgr::ITEM_1UP },
    { BgTexMgr::ANIME_INFO_TYPE_BLOCK,  cUnitID_BrickBlockVine,         BgTexMgr::ITEM_VINE },
    { BgTexMgr::ANIME_INFO_TYPE_BLOCK,  cUnitID_BrickBlockMiniMushroom, BgTexMgr::ITEM_MINI_MUSHROOM },
    { BgTexMgr::ANIME_INFO_TYPE_BLOCK,  cUnitID_BrickBlockPropeller,    BgTexMgr::ITEM_PROPELLER },
    { BgTexMgr::ANIME_INFO_TYPE_BLOCK,  cUnitID_BrickBlockPenguin,      BgTexMgr::ITEM_PENGUIN },
    { BgTexMgr::ANIME_INFO_TYPE_BLOCK,  cUnitID_BrickBlockIceFlower,    BgTexMgr::ITEM_ICE_FLOWER },
    { BgTexMgr::ANIME_INFO_TYPE_BLOCK,  cUnitID_BrickBlockAcorn,        BgTexMgr::ITEM_ACORN },
    { BgTexMgr::ANIME_INFO_TYPE_BLOCK,  cUnitID_BrickBlockYoshiEgg,     BgTexMgr::ITEM_YOSHI_EGG },
    { BgTexMgr::ANIME_INFO_TYPE_BLOCK,  cUnitID_BrickBlockCoin,         BgTexMgr::ITEM_COIN },
    { BgTexMgr::ANIME_INFO_TYPE_BLOCK,  cUnitID_BrickBlockCoin10,       BgTexMgr::ITEM_COIN_10 },
    { BgTexMgr::ANIME_INFO_TYPE_HATENA, cUnitID_QBlockFireFlower,       BgTexMgr::ITEM_FIRE_FLOWER },
    { BgTexMgr::ANIME_INFO_TYPE_HATENA, cUnitID_QBlockStar,             BgTexMgr::ITEM_STAR },
    { BgTexMgr::ANIME_INFO_TYPE_HATENA, cUnitID_QBlockCoinStar,         BgTexMgr::ITEM_COIN_STAR },
    { BgTexMgr::ANIME_INFO_TYPE_HATENA, cUnitID_QBlockVine,             BgTexMgr::ITEM_VINE },
    { BgTexMgr::ANIME_INFO_TYPE_HATENA, cUnitID_QBlockMiniMushroom,     BgTexMgr::ITEM_MINI_MUSHROOM },
    { BgTexMgr::ANIME_INFO_TYPE_HATENA, cUnitID_QBlockPropeller,        BgTexMgr::ITEM_PROPELLER },
    { BgTexMgr::ANIME_INFO_TYPE_HATENA, cUnitID_QBlockPenguin,          BgTexMgr::ITEM_PENGUIN },
    { BgTexMgr::ANIME_INFO_TYPE_HATENA, cUnitID_QBlockIceFlower,        BgTexMgr::ITEM_ICE_FLOWER },
    { BgTexMgr::ANIME_INFO_TYPE_HATENA, cUnitID_QBlockAcorn,            BgTexMgr::ITEM_ACORN },
    { BgTexMgr::ANIME_INFO_TYPE_HATENA, cUnitID_QBlockYoshiEgg,         BgTexMgr::ITEM_YOSHI_EGG },
    { BgTexMgr::ANIME_INFO_TYPE_HATENA, cUnitID_QBlockSpring,           BgTexMgr::ITEM_SPRING }
};

void BgTexMgr::drawXlu_(const rio::lyr::DrawInfo& draw_info)
{
    if (!isReady())
        return;

    bindTexRenderBuffer_();

    rio::RenderState render_state;
    render_state.setDepthEnable(false, false);
    render_state.setBlendFactorDst(rio::Graphics::BLEND_MODE_ZERO);
    render_state.setCullingMode(rio::Graphics::CULLING_MODE_NONE);
    render_state.apply();

    const rio::BaseMtx44f& proj_mtx = draw_info.parent_layer.projection()->getMatrix();

    bool need_redraw_default = false;
    if (!mOverridesDrawn)
    {
        drawTexture(mBgUnitFile[0]->getTexture(), proj_mtx);

        render_state.setBlendFactorDst(rio::Graphics::BLEND_MODE_ONE_MINUS_SRC_ALPHA);
        render_state.applyBlendAndFastZ();

        drawTexture(mOverrides[mOverridesType], proj_mtx);

        render_state.setBlendFactorDst(rio::Graphics::BLEND_MODE_ZERO);
        render_state.applyBlendAndFastZ();

        mOverridesDrawn = true;
        need_redraw_default = true;
    }

    for (s32 i = 0; i < ANIME_INFO_TYPE_MAX; i++)
    {
        const AnimeInfo& anime_info = cAnimeInfo[i];
        drawAnime(cAnimeInfoUnitID[i], mFrame[i], mBgUnitFile[0]->getAnimeTexture(anime_info.anim_type), anime_info.square, proj_mtx);
    }

    for (s32 i = 0; i < cItemOverrideNum; i++)
    {
        const ItemOverrideInfo& item_override_info = cItemOverrideInfo[i];
        const AnimeInfo& anime_info = cAnimeInfo[item_override_info.anime_info_type];
        drawAnime(item_override_info.unit, mFrame[item_override_info.anime_info_type], mBgUnitFile[0]->getAnimeTexture(anime_info.anim_type), anime_info.square, proj_mtx);

        render_state.setBlendFactorDst(rio::Graphics::BLEND_MODE_ONE_MINUS_SRC_ALPHA);
        render_state.applyBlendAndFastZ();

        drawItem(item_override_info.unit, item_override_info.item_type, mItemsTexture, proj_mtx);

        render_state.setBlendFactorDst(rio::Graphics::BLEND_MODE_ZERO);
        render_state.applyBlendAndFastZ();
    }

    mTexRenderBuffer.getRenderTargetColor()->invalidateGPUCache();

    if (need_redraw_default)
        doUnitDefaultRender_();

    restoreFramebuffer_();
}

void BgTexMgr::createUnitDefaultRender_()
{
    for (u8 env = 0; env < CD_FILE_ENV_MAX_NUM; env++)
    {
        const BgUnitFile* const file = mBgUnitFile[env];
        if (file == nullptr)
            continue;

        u32 size = file->getObjCount();
        for (u32 i = 0; i < size; i++)
        {
            const BgUnitObj& bg_unit_obj = file->getObj(i);
            const BgUnitObj::Unit* const* const unit_mtx = bg_unit_obj.getDefaultRender();
            if (unit_mtx == nullptr)
            {
                mUnitObjTexArray[env].emplace_back(nullptr);
                continue;
            }

            u32 w = bg_unit_obj.getWidth();
            u32 h = bg_unit_obj.getHeight();

            u32 tex_w = w * 60;
            u32 tex_h = h * 60;

            [[maybe_unused]] const rio::Texture2D& texture = *(mUnitObjTexArray[env].emplace_back(std::make_unique<rio::Texture2D>(rio::TEXTURE_FORMAT_R8_G8_B8_A8_UNORM, tex_w, tex_h, 1)));
#if RIO_IS_WIN
            RIO_GL_CALL(glBindTexture(GL_TEXTURE_2D, texture.getNativeTextureHandle()));
            RIO_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST));
            RIO_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
#endif // RIO_IS_WIN
        }
    }
}

void BgTexMgr::doUnitDefaultRender_()
{
    rio::RenderState render_state;
    render_state.setDepthEnable(false, false);
    render_state.setBlendFactor(rio::Graphics::BLEND_MODE_ONE, rio::Graphics::BLEND_MODE_ZERO);
    render_state.setCullingMode(rio::Graphics::CULLING_MODE_NONE);
    render_state.apply();

    rio::RenderBuffer render_buffer;
    rio::RenderTargetColor color_target;
    render_buffer.setRenderTargetColor(&color_target);

    agl::TextureSampler sampler;

    for (u8 env = 0; env < CD_FILE_ENV_MAX_NUM; env++)
    {
        const BgUnitFile* const file = mBgUnitFile[env];
        if (file == nullptr)
            continue;

        u32 size = file->getObjCount();
        for (u32 i = 0; i < size; i++)
        {
            const BgUnitObj& bg_unit_obj = file->getObj(i);
            const BgUnitObj::Unit* const* const unit_mtx = bg_unit_obj.getDefaultRender();
            if (unit_mtx == nullptr)
                continue;

            u32 w = bg_unit_obj.getWidth();
            u32 h = bg_unit_obj.getHeight();

            u32 tex_w = w * 60;
            u32 tex_h = h * 60;

            rio::OrthoProjection projection(-1.0f, 1.0f, 0.0f, h, 0.0f, w);

            render_buffer.setSize(tex_w, tex_h);
            color_target.linkTexture2D(*(mUnitObjTexArray[env][i]));
            render_buffer.clear(rio::RenderBuffer::CLEAR_FLAG_COLOR, { 0.0f, 0.0f, 0.0f, 0.0f });
            render_buffer.bind();

            for (u32 y = 0; y < h; y++)
            {
                for (u32 x = 0; x < w; x++)
                {
                    const BgUnitObj::Unit& unit = *(unit_mtx[y * w + x]);
                    if (unit.env == 0 && unit.idx == 0)
                        continue;

                    const rio::Texture2D* env_texture = nullptr;
                    if (unit.env == 0)
                        env_texture = &mTexColor;

                    else
                    {
                        const BgUnitFile* const file_for_tex = mBgUnitFile[unit.env];
                        if (file_for_tex == nullptr)
                            continue;

                        env_texture = file_for_tex->getTexture();
                    }
                    RIO_ASSERT(env_texture);

                    sampler.applyTextureData(*env_texture);

                    u32 row = unit.idx / 32;
                    u32 col = unit.idx % 32;

                    rio::Matrix34f mtx;
                    mtx.makeT({ x + 0.5f, y + 0.5f, 0.0f });

                    const rio::Vector2f env_tex_size { 2048.0f, 512.0f };

                    const rio::Vector2f unit_size { 60, -60 };
                    const rio::Vector2f unit_center { -env_tex_size.x * 0.5f + (col + 0.5f) * 64, -env_tex_size.y * 0.5f + (row + 0.5f) * 64 };

                    agl::utl::DevTools::drawTextureTexCoord(
                        sampler,
                        mtx, projection.getMatrix(),
                        unit_size / env_tex_size,
                        0.0f,
                        unit_center / unit_size,
                        agl::cShaderMode_Invalid
                    );
                }
            }

            color_target.invalidateGPUCache();
        }
    }
}

void BgTexMgr::clearUnitDefaultRender_()
{
    for (u8 env = 0; env < CD_FILE_ENV_MAX_NUM; env++)
        mUnitObjTexArray[env].clear();
}

void BgTexMgr::DrawCallback::preDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
    if (!mBgTexMgr.isReady())
        return;

    mBgTexMgr.bindTexRenderBuffer_();
}

void BgTexMgr::DrawCallback::preDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
}

void BgTexMgr::DrawCallback::postDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
}

void BgTexMgr::DrawCallback::postDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
    if (!mBgTexMgr.isReady())
        return;

    mBgTexMgr.mTexRenderBuffer.getRenderTargetColor()->invalidateGPUCache();
    restoreFramebuffer_();
}
