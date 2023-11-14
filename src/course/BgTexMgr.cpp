#include <course/Bg.h>
#include <course/BgUnitFile.h>
#include <course/CourseDataFile.h>
#include <course/BgTexMgr.h>
#include <graphics/RenderObjLayer.h>

#include <MainWindow.h>

#include <gfx/rio_PrimitiveRenderer.h>
#include <gfx/rio_Window.h>
#include <gpu/rio_RenderState.h>
#include <misc/rio_MemUtil.h>
#include <utility/aglDevTools.h>

#include <rio.h>

static const s32 cTexWidthI = 2048;
static const f32 cTexWidth = cTexWidthI;
static const s32 cTexHeightI = 512;
static const f32 cTexHeight = cTexHeightI;
static const s32 cUnitSizeI = 64;
static const f32 cUnitSize = cUnitSizeI;
//static const s32 cUnitSizeNoPadI = 60;
//static const f32 cUnitSizeNoPad = cUnitSizeNoPadI;
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
    , mTexDepth(rio::DEPTH_TEXTURE_FORMAT_R32_FLOAT, cTexWidthI, cTexHeightI, 1)
{
    mTexDepthTarget.linkTexture2D(mTexDepth);
    mTexRenderBuffer.setRenderTargetDepth(&mTexDepthTarget);

    rio::MemUtil::set(mDelayTimer, 0, sizeof(mDelayTimer));
    rio::MemUtil::set(mFrame, 0, sizeof(mFrame));
}

BgTexMgr::~BgTexMgr()
{
}

void BgTexMgr::initialize(const Bg& bg, const CourseDataFile& cd_file, RenderObjLayer* p_bg_prepare_layer)
{
    rio::MemUtil::set(mDelayTimer, 0, sizeof(mDelayTimer));
    rio::MemUtil::set(mFrame, 0, sizeof(mFrame));

    const BgUnitFile* bg_unit_file = bg.getUnitFile(cd_file.getEnvironment(0));
    RIO_ASSERT(bg_unit_file != nullptr);

    const rio::Texture2D* texture = bg_unit_file->getTexture();
    RIO_ASSERT(texture != nullptr);

    mTexColorTarget.linkTexture2D(*texture);
    mTexRenderBuffer.setRenderTargetColor(&mTexColorTarget);

    p_bg_prepare_layer->getRenderMgr()->setDrawCallback(&mDrawCallback);
    p_bg_prepare_layer->addDrawMethod(RenderObjLayer::cRenderStep_Xlu, rio::lyr::DrawMethod(this, &BgTexMgr::drawXlu_));
}

void BgTexMgr::destroy(RenderObjLayer* p_bg_prepare_layer)
{
    mTexRenderBuffer.setRenderTargetColorNull();

    p_bg_prepare_layer->getRenderMgr()->setDrawCallback(nullptr);
    p_bg_prepare_layer->clearDrawMethodsAll();
}

void BgTexMgr::bindTexRenderBuffer_() const
{
    RIO_ASSERT(mTexRenderBuffer.getRenderTargetColor() != nullptr);
    mTexRenderBuffer.bind();
}

void BgTexMgr::restoreFramebuffer_() const
{
    RIO_ASSERT(mTexRenderBuffer.getRenderTargetColor() != nullptr);
    mTexRenderBuffer.getRenderTargetColor()->invalidateGPUCache();

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

static inline void clearRow(u16 tile, f32 width)
{
    rio::PrimitiveRenderer::QuadArg arg;
    rio::Vector3f p { tile % cUnitPerRow * cUnitSize, cTexHeight - (tile / cUnitPerRow + 1) * cUnitSize, 0.0f };
    rio::Vector2f size { width, cUnitSize };
    arg.setCornerAndSize(p, size);
    rio::Color4f color { 1.0f, 0.0f, 0.0f, 0.0f };
    arg.setColor(color, color);
    rio::PrimitiveRenderer::instance()->drawQuad(arg);
}

void BgTexMgr::drawAnime_(UnitID unit, s32 frame, AnimeType type, bool square, const rio::BaseMtx44f& proj_mtx)
{
    RIO_ASSERT(unit < cUnitID_Pa0_Unit_Num);
    u16 tile = unit & 0xFF;

    const MainWindow* window = static_cast<const MainWindow*>(rio::sRootTask);

    const CourseDataFile* p_cd_file = window->getCurrentCourseDataFile();
    if (p_cd_file == nullptr)
        return;

    const Bg& bg = window->getCourseData().getBg();
    const CourseDataFile& cd_file = *p_cd_file;

    const BgUnitFile* bg_unit_file = bg.getUnitFile(cd_file.getEnvironment(0));
    RIO_ASSERT(bg_unit_file != nullptr);

    const rio::Texture2D* texture = bg_unit_file->getAnimeTexture(type);
    RIO_ASSERT(texture != nullptr);

    u32 tex_width = texture->getWidth();
    u32 tex_height = texture->getHeight();

    agl::TextureSampler sampler(*texture);

    s32 size =
        square
            ? tex_width / cUnitSizeI
            : 1;

    rio::RenderState render_state;
    render_state.setBlendEnable(false);
    render_state.applyBlendAndFastZ();

    rio::PrimitiveRenderer* primitive_renderer = rio::PrimitiveRenderer::instance();
    primitive_renderer->begin();
    {
        for (s32 i = 0; i < size; i++)
            clearRow(tile + i * cUnitPerRowReal, f32(tex_width));
    }
    primitive_renderer->end();

    render_state.setBlendEnable(true);
    render_state.applyBlendAndFastZ();

    for (s32 i = 0; i < size; i++)
    {
        rio::Matrix34f mtx;
        mtx.makeST(
            { f32(tex_width), cUnitSize, 1.0f },
            { ((tile + i * cUnitPerRowReal) % cUnitPerRow) * cUnitSize + tex_width * 0.5f, cTexHeight + cUnitSize * 0.5f - ((tile + i * cUnitPerRowReal) / cUnitPerRow + 1) * cUnitSize, 0.0f }
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

void BgTexMgr::drawXlu_(const rio::lyr::DrawInfo& draw_info)
{
    bindTexRenderBuffer_();

    rio::RenderState render_state;
    render_state.setDepthEnable(false, false);
    render_state.setCullingMode(rio::Graphics::CULLING_MODE_NONE);
    render_state.apply();

    const rio::BaseMtx44f& proj_mtx = draw_info.parent_layer.projection()->getMatrix();

    rio::PrimitiveRenderer* primitive_renderer = rio::PrimitiveRenderer::instance();
    primitive_renderer->setProjMtx(proj_mtx);
    primitive_renderer->setCamera(rio::lyr::Layer::defaultCamera());
    primitive_renderer->setModelMatrix(rio::Matrix34f::ident);

    for (s32 i = 0; i < ANIME_INFO_TYPE_MAX; i++)
    {
        const AnimeInfo& anime_info = cAnimeInfo[i];
        drawAnime_(cAnimeInfoUnitID[i], mFrame[i], anime_info.anim_type, anime_info.square, proj_mtx);
    }

    {
        const AnimeInfo& anime_info = cAnimeInfo[ANIME_INFO_TYPE_TUKA_COIN];
        drawAnime_(cUnitID_CoinDashMultiplayer, mFrame[ANIME_INFO_TYPE_TUKA_COIN], anime_info.anim_type, anime_info.square, proj_mtx);
    }

    restoreFramebuffer_();
}

void BgTexMgr::DrawCallback::preDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
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
    mBgTexMgr.restoreFramebuffer_();
}
