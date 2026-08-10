#include <graphics/GridRenderer.h>

#include <gpu/rio_Drawer.h>
#include <misc/rio_MemUtil.h>

GridRenderer* GridRenderer::sInstance = nullptr;

bool GridRenderer::createSingleton()
{
    if (sInstance)
        return false;

    sInstance = new GridRenderer();
    return true;
}

void GridRenderer::destroySingleton()
{
    if (!sInstance)
        return;

    delete sInstance;
    sInstance = nullptr;
}

GridRenderer::GridRenderer()
    : mShader()
    , mVertexBuffer(0)
    , mPosStream()
    , mVertexArray()
    , mVertexBuf(nullptr)
    , mIndexBuf(nullptr)
    , mMVPUniformLoc(0xFFFFFFFF)
    , mColorUniformLoc(0xFFFFFFFF)
    , mPixelsPerUnitUniformLoc(0xFFFFFFFF)
    , mModeUniformLoc(0xFFFFFFFF)
{
    initialize_();
}

GridRenderer::~GridRenderer()
{
    rio::MemUtil::free(mVertexBuf);
    rio::MemUtil::free(mIndexBuf);
}

void GridRenderer::initialize_()
{
    mShader.load("grid_renderer", rio::Shader::MODE_UNIFORM_REGISTER);

    mMVPUniformLoc = mShader.getVertexUniformLocation("uMVP");
    RIO_ASSERT(mMVPUniformLoc != 0xFFFFFFFF);

    mColorUniformLoc = mShader.getFragmentUniformLocation("uColor");
    RIO_ASSERT(mColorUniformLoc != 0xFFFFFFFF);

    mPixelsPerUnitUniformLoc = mShader.getFragmentUniformLocation("uPixelsPerUnit");
    RIO_ASSERT(mPixelsPerUnitUniformLoc != 0xFFFFFFFF);

    mModeUniformLoc = mShader.getFragmentUniformLocation("uMode");
    RIO_ASSERT(mModeUniformLoc != 0xFFFFFFFF);

    mPosStream.setLayout(0, rio::VertexStream::FORMAT_32_32_32_FLOAT, offsetof(Vertex, pos));

    mVertexBuffer.setStride(sizeof(Vertex));

    mVertexArray.initialize();
    mVertexArray.addAttribute(mPosStream, mVertexBuffer);
    mVertexArray.process();

    mVertexBuf = static_cast<Vertex*>(rio::MemUtil::alloc(4 * sizeof(Vertex), rio::Drawer::cVtxAlignment));
    mIndexBuf  = static_cast<   u16*>(rio::MemUtil::alloc(6 * sizeof(   u16), rio::Drawer::cIdxAlignment));

    RIO_ASSERT(mVertexBuf != nullptr);
    RIO_ASSERT(mIndexBuf  != nullptr);

    static const u16 idx[6] = { 0, 1, 2, 2, 1, 3 };
    rio::MemUtil::copy(mIndexBuf, idx, sizeof(idx));

    rio::VertexBuffer::invalidateCache(mIndexBuf, 6 * sizeof(u16));
}

void GridRenderer::draw(
    const rio::BaseMtx44f&  view_proj_mtx,
    const rio::BaseVec2f&   world_min,
    const rio::BaseVec2f&   world_max,
    f32                     pixels_per_unit,
    GridType                type
)
{
    if (type == GRID_TYPE_NONE || type >= GRID_TYPE_MAX_NUM)
        return;

    if (world_max.x <= world_min.x || world_max.y <= world_min.y)
        return;

    if (pixels_per_unit <= 0.0f)
        return;

    mVertexBuf[0].pos = { world_min.x, world_max.y, 0.0f };
    mVertexBuf[1].pos = { world_max.x, world_max.y, 0.0f };
    mVertexBuf[2].pos = { world_min.x, world_min.y, 0.0f };
    mVertexBuf[3].pos = { world_max.x, world_min.y, 0.0f };

    rio::VertexBuffer::invalidateCache(mVertexBuf, 4 * sizeof(Vertex));

    mShader.bind();

    mShader.setUniformArray(4, view_proj_mtx.v, mMVPUniformLoc, 0xFFFFFFFF);

    static const rio::Color4f cGridColor { 1.0f, 1.0f, 1.0f, 100 / 255.f };
    mShader.setUniform(cGridColor.v, 0xFFFFFFFF, mColorUniformLoc);
    mShader.setUniform(pixels_per_unit, 0xFFFFFFFF, mPixelsPerUnitUniformLoc);
    mShader.setUniform(s32(type == GRID_TYPE_CHECKER), 0xFFFFFFFF, mModeUniformLoc);

    mVertexBuffer.setData(mVertexBuf, 4 * sizeof(Vertex));
    mVertexArray.bind();

    rio::Drawer::DrawElements(rio::Drawer::TRIANGLES, 6, mIndexBuf);
}
