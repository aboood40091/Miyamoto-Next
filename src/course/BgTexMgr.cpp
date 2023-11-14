#include <course/Bg.h>
#include <course/BgUnitFile.h>
#include <course/CourseDataFile.h>
#include <course/BgTexMgr.h>
#include <graphics/RenderObjLayer.h>

#include <gfx/rio_Graphics.h>
#include <gfx/rio_Window.h>

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
    , mTexRenderBuffer(2048, 512)
    , mTexDepth(rio::DEPTH_TEXTURE_FORMAT_R32_FLOAT, 2048, 512, 1)
{
    mTexDepthTarget.linkTexture2D(mTexDepth);
    mTexRenderBuffer.setRenderTargetDepth(&mTexDepthTarget);
}

BgTexMgr::~BgTexMgr()
{
}

void BgTexMgr::initialize(const Bg& bg, const CourseDataFile& cd_file, RenderObjLayer* p_bg_prepare_layer)
{
    const BgUnitFile* bg_unit_file = bg.getUnitFile(cd_file.getEnvironment(0));
    RIO_ASSERT(bg_unit_file != nullptr);

    const rio::Texture2D* texture = bg_unit_file->getTexture();
    RIO_ASSERT(texture != nullptr);

    mTexColorTarget.linkTexture2D(*texture);
    mTexRenderBuffer.setRenderTargetColor(&mTexColorTarget);

    p_bg_prepare_layer->getRenderMgr()->setDrawCallback(&mDrawCallback);
}

void BgTexMgr::destroy(RenderObjLayer* p_bg_prepare_layer)
{
    mTexRenderBuffer.setRenderTargetColorNull();

    p_bg_prepare_layer->getRenderMgr()->setDrawCallback(nullptr);
}

void BgTexMgr::DrawCallback::preDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
    RIO_ASSERT(mBgTexMgr.mTexRenderBuffer.getRenderTargetColor() != nullptr);
    mBgTexMgr.mTexRenderBuffer.bind();
}

void BgTexMgr::DrawCallback::preDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
}

void BgTexMgr::DrawCallback::postDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
}

void BgTexMgr::DrawCallback::postDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
    RIO_ASSERT(mBgTexMgr.mTexRenderBuffer.getRenderTargetColor() != nullptr);
    mBgTexMgr.mTexRenderBuffer.getRenderTargetColor()->invalidateGPUCache();

    rio::Window::instance()->makeContextCurrent();

    u32 width = rio::Window::instance()->getWidth();
    u32 height = rio::Window::instance()->getHeight();

    rio::Graphics::setViewport(0, 0, width, height);
    rio::Graphics::setScissor(0, 0, width, height);
}
