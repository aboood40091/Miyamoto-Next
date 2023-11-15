#include <course/BgTexMgr.h>
#include <course/CoinOrigin.h>
#include <course/UnitID.h>
#include <graphics/ModelG3d.h>
#include <graphics/RenderMgr.h>
#include <graphics/RenderObjLayer.h>
#include <resource/SZSDecompressor.h>

#include <gfx/rio_PrimitiveRenderer.h>
#include <gfx/rio_Window.h>
#include <gpu/rio_RenderState.h>
#include <misc/rio_MemUtil.h>

static const f32 cTexWidth = 2048;
static const f32 cTexHeight = 512;
static const f32 cUnitSize = 64;
static const f32 cUnitSizeNoPad = 60;
static const s32 cUnitPerRow = 2048 / 64;
//static const s32 cUnitPerColumn = 512 / 64;

static const u32 cCoinAngleStep = 0x3fd27d2;

CoinOrigin* CoinOrigin::sInstance = nullptr;

bool CoinOrigin::createSingleton()
{
    if (sInstance)
        return false;

    sInstance = new CoinOrigin();
    return true;
}

void CoinOrigin::destroySingleton()
{
    if (!sInstance)
        return;

    delete sInstance;
    sInstance = nullptr;
}

CoinOrigin::CoinOrigin()
    : mIsInitialized(false)
{
}

CoinOrigin::~CoinOrigin()
{
    if (mIsInitialized)
    {
        delete mpModelBlueCoin;
        delete mpModelCoin;
        mModelResource.destroy();
        mArchiveRes.destroy();
        rio::MemUtil::free(mpArchive);
        mIsInitialized = false;
    }
}

bool CoinOrigin::initialize(const std::string& pack_arc_path)
{
    RIO_ASSERT(mIsInitialized == false);

    rio::FileDevice::LoadArg arg;
    arg.path = pack_arc_path;

    u8* pack_arc_dat = SZSDecompressor::tryDecomp(arg);
    if (!pack_arc_dat)
        return false;

    SharcArchiveRes pack_arc;
    if (!pack_arc.prepareArchive(pack_arc_dat))
    {
        RIO_LOG("Could not load Sharc file...\n");
        rio::MemUtil::free(pack_arc_dat);
        return false;
    }

    u32 size = 0;
    void* ptr = pack_arc.getFile("obj_coin", &size);
    if (ptr == nullptr)
    {
        RIO_LOG("Could not locate obj_coin file...\n");
        rio::MemUtil::free(pack_arc_dat);
        return false;
    }

    mpArchive = rio::MemUtil::alloc(size, 0x2000);
    rio::MemUtil::copy(mpArchive, ptr, size);
    rio::MemUtil::free(pack_arc_dat);

    if (!mArchiveRes.prepareArchive(mpArchive))
    {
        RIO_LOG("Could not load Sharc file...\n");
        rio::MemUtil::free(mpArchive);
        return false;
    }

    mModelResource.load(&mArchiveRes, "obj_coin");
    mpModelCoin = Model::createG3d(
        mModelResource,
        "obj_coin",
        1, 1, 1, 1, 0,
        Model::cBoundingMode_Disable
    );
    mpModelBlueCoin = Model::createG3d(
        mModelResource,
        "obj_coin_blue",
        1, 1, 1, 1, 0,
        Model::cBoundingMode_Disable
    );

    mIsInitialized = true;
    return true;
}

void CoinOrigin::pushBackDrawMethod(RenderObjLayer* p_bg_prepare_layer)
{
    mProjection.setNear(0.0f);
    mProjection.setFar(1000.0f);
    mProjection.setTBLR(cTexHeight, 0.0f, 0.0f, cTexWidth);

    calcMdl_();

    p_bg_prepare_layer->addDrawMethod(RenderObjLayer::cRenderStep_UpdateGPUBuffer, rio::lyr::DrawMethod(this, &CoinOrigin::apply_));
    p_bg_prepare_layer->setProjection(&mProjection);
    p_bg_prepare_layer->setCamera(&rio::lyr::Layer::defaultCamera());
}

void CoinOrigin::update()
{
    mCoinAngle += cCoinAngleStep;

    calcMdl_();
}

void CoinOrigin::draw(RenderObjLayer* p_bg_prepare_layer)
{
    if (!mIsInitialized || !BgTexMgr::instance()->isReady())
        return;

    static const rio::Vector3f zero { 0.0f, 0.0f, 0.0f };
    p_bg_prepare_layer->getRenderMgr()->pushBackRenderObj(mpModelCoin, true, false, zero);
    p_bg_prepare_layer->getRenderMgr()->pushBackRenderObj(mpModelBlueCoin, true, false, zero);
}

void CoinOrigin::calcMdl_()
{
    if (!mIsInitialized)
        return;

    f32 x = cUnitSize * 0.5f;
    f32 y = (cUnitSize + cUnitSizeNoPad) * 0.5f;

    rio::Matrix34f mtx;
    {
        const rio::Vector3f r { 0.0f, getCoinAngle(), 0.0f };
        const rio::Vector3f t { (cUnitID_Coin     % cUnitPerRow) * cUnitSize + x, cTexHeight - (cUnitID_Coin     / cUnitPerRow + 1.5f) * cUnitSize + y, -500.0f };
        mtx.makeRT(r, t);
        mpModelCoin->setMtxRT(mtx);
    }
    {
        const rio::Vector3f r { 0.0f, getCoinAngle(), 0.0f };
        const rio::Vector3f t { (cUnitID_BlueCoin % cUnitPerRow) * cUnitSize + x, cTexHeight - (cUnitID_BlueCoin / cUnitPerRow + 1.5f) * cUnitSize + y, -500.0f };
        mtx.makeRT(r, t);
        mpModelBlueCoin->setMtxRT(mtx);
    }

    f32 scale = 1.5f * cUnitSizeNoPad / 24;
    const rio::Vector3f s { scale, scale, scale };

    mpModelCoin->setScale(s);
    mpModelBlueCoin->setScale(s);

    mpModelCoin->updateModel();
    mpModelBlueCoin->updateModel();
}

void CoinOrigin::apply_(const rio::lyr::DrawInfo& draw_info)
{
    if (!mIsInitialized || !BgTexMgr::instance()->isReady())
        return;

    BgTexMgr::instance()->getTexRenderBuffer().bind();

    rio::RenderState render_state;
    render_state.setDepthEnable(true, true);
    render_state.setDepthFunc(rio::Graphics::COMPARE_FUNC_ALWAYS);
    render_state.setBlendEnable(false);
    render_state.setCullingMode(rio::Graphics::CULLING_MODE_NONE);
    render_state.apply();

    rio::PrimitiveRenderer* primitive_renderer = rio::PrimitiveRenderer::instance();
    primitive_renderer->setProjection(mProjection);
    primitive_renderer->setCamera(rio::lyr::Layer::defaultCamera());
    primitive_renderer->setModelMatrix(rio::Matrix34f::ident);

    primitive_renderer->begin();
    {
        {
            rio::PrimitiveRenderer::QuadArg arg;
            rio::Vector3f p { cUnitID_Coin     % cUnitPerRow * cUnitSize, cTexHeight - (cUnitID_Coin     / cUnitPerRow + 1) * cUnitSize, -999.0f };
            rio::Vector2f size { cUnitSize, cUnitSize };
            arg.setCornerAndSize(p, size);
            rio::Color4f color { 1.0f, 0.0f, 0.0f, 0.0f };
            arg.setColor(color, color);
            primitive_renderer->drawQuad(arg);
        }
        {
            rio::PrimitiveRenderer::QuadArg arg;
            rio::Vector3f p { cUnitID_BlueCoin % cUnitPerRow * cUnitSize, cTexHeight - (cUnitID_BlueCoin / cUnitPerRow + 1) * cUnitSize, -999.0f };
            rio::Vector2f size { cUnitSize, cUnitSize };
            arg.setCornerAndSize(p, size);
            rio::Color4f color { 1.0f, 0.0f, 0.0f, 0.0f };
            arg.setColor(color, color);
            primitive_renderer->drawQuad(arg);
        }
    }
    primitive_renderer->end();

    rio::Window::instance()->makeContextCurrent();

    u32 width = rio::Window::instance()->getWidth();
    u32 height = rio::Window::instance()->getHeight();

    rio::Graphics::setViewport(0, 0, width, height);
    rio::Graphics::setScissor(0, 0, width, height);
}
