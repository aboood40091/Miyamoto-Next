#include <CourseView.h>
#include <MainWindow.h>
#include <course/BgTexMgr.h>
#include <course/CoinOrigin.h>
#include <course/CourseData.h>
#include <graphics/LayerID.h>
#include <graphics/ModelResMgr.h>
#include <graphics/Renderer.h>
#include <resource/ResMgr.h>
#include <graphics/ShaderHolder.h>
#include <resource/SZSDecompressor.h>
#include <ui/ImGuiUtil.h>

#include <controller/rio_ControllerMgr.h>
#include <filedevice/rio_FileDeviceMgr.h>
#include <gfx/rio_Window.h>
#include <gfx/lyr/rio_Renderer.h>

#include <detail/aglShaderHolder.h>
#include <utility/aglPrimitiveShape.h>
#include <utility/aglPrimitiveTexture.h>
#include <utility/aglVertexAttributeHolder.h>

#if RIO_IS_CAFE
#include <detail/aglGX2.h>
#endif // RIO_IS_CAFE

#if RIO_IS_WIN
#include <graphics/win/ShaderUtil.h>
#endif // RIO_IS_WIN

#include <rio.h>

#include <imgui.h>

static const char* level_fname = "1-1.szs";
static const std::string nsmbu_content_path = "game/nsmbu";

const std::string& MainWindow::getContentPath()
{
    return nsmbu_content_path;
}

MainWindow::MainWindow()
    : rio::ITask("Miyamoto! Next")
    , mpCourseView(nullptr)
    , mCourseViewResized(false)
    , mCourseViewHovered(false)
    , mCourseViewFocused(false)
{
}

#if RIO_IS_WIN

void MainWindow::resize_(s32 width, s32 height)
{
    ImGuiUtil::setDisplaySize(width, height);
}

void MainWindow::onResizeCallback_(s32 width, s32 height)
{
    static_cast<MainWindow*>(rio::sRootTask)->resize_(width, height);
}

#endif // RIO_IS_WIN

void MainWindow::prepare_()
{
  //RIO_LOG("MainWindow::prepare_(): start\n");

#if RIO_IS_WIN
    rio::Window::instance()->setOnResizeCallback(&MainWindow::onResizeCallback_);
#endif // RIO_IS_WIN

    s32 width = rio::Window::instance()->getWidth();
    s32 height = rio::Window::instance()->getHeight();

    ImGuiUtil::initialize(width, height);

#if RIO_IS_CAFE
    GX2InitSampler(&mGX2Sampler, GX2_TEX_CLAMP_MODE_CLAMP, GX2_TEX_XY_FILTER_MODE_POINT);
    mImGuiGX2Texture.Sampler = &mGX2Sampler;
#endif // RIO_IS_CAFE

    mLayerGather.it = rio::lyr::Renderer::instance()->addLayer("Gather", LAYER_ID_GATHER);
    mLayerGather.ptr = rio::lyr::Layer::peelIterator(mLayerGather.it);
    mLayerGather.ptr->addRenderStep("Gather");
    mLayerGather.ptr->addDrawMethod(0, rio::lyr::DrawMethod(this, &MainWindow::gather_));
    mLayerGather.ptr->setClearColor({
        119 / 255.f,
        136 / 255.f,
        153 / 255.f
    });
    mLayerGather.ptr->setClearDepthStencil();

    mLayerDispose.it = rio::lyr::Renderer::instance()->addLayer("Dispose", LAYER_ID_DISPOSE);
    mLayerDispose.ptr = rio::lyr::Layer::peelIterator(mLayerDispose.it);
    mLayerDispose.ptr->addRenderStep("Dispose");
    mLayerDispose.ptr->addDrawMethod(0, rio::lyr::DrawMethod(this, &MainWindow::dispose_));

    mLayerBgPrepare.it = rio::lyr::Renderer::instance()->addLayer<RenderObjLayer>("BgPrepare", LAYER_ID_BG_PREPARE);
    mLayerBgPrepare.ptr = rio::lyr::Layer::peelIterator(mLayerBgPrepare.it);
    getBgPrepareLayer()->setRenderMgr(&mRenderMgrBgPrepare);

    BgTexMgr::createSingleton();

  //RIO_LOG("MainWindow::prepare_(): layer initialized\n");

#if RIO_IS_WIN
    ShaderUtil::sTempPath                   = rio::FileDeviceMgr::instance()->getNativeFileDevice()->getCWD() + "/fs/content/shaders/cache";
    ShaderUtil::sGx2ShaderDecompilerPath    = rio::FileDeviceMgr::instance()->getNativeFileDevice()->getCWD() + "/fs/content/gx2shader-decompiler.exe";
    ShaderUtil::sSpirvCrossPath             = rio::FileDeviceMgr::instance()->getNativeFileDevice()->getCWD() + "/fs/content/spirv-cross.exe";

  //RIO_LOG("MainWindow::prepare_(): ShaderUtil parameters set\n");
#endif // RIO_IS_WIN

#if RIO_IS_CAFE
    agl::driver::GX2Resource::createSingleton();
  //RIO_LOG("MainWindow::prepare_(): agl::driver::GX2Resource::createSingleton() done\n");
    agl::driver::GX2Resource::instance()->initialize();
  //RIO_LOG("MainWindow::prepare_(): agl::driver::GX2Resource::instance()->initialize() done\n");
#endif // RIO_IS_CAFE

    agl::detail::ShaderHolder::createSingleton();
  //RIO_LOG("MainWindow::prepare_(): agl::detail::ShaderHolder::createSingleton() done\n");
#if RIO_IS_CAFE
    agl::detail::ShaderHolder::instance()->setCreateDisplayLists(true);
#endif // RIO_IS_CAFE

    agl::utl::PrimitiveShape::createSingleton();
  //RIO_LOG("MainWindow::prepare_(): agl::utl::PrimitiveShape::createSingleton() done\n");
    agl::utl::PrimitiveShape::instance()->initialize();
  //RIO_LOG("MainWindow::prepare_(): agl::utl::PrimitiveShape::instance()->initialize() done\n");

    agl::utl::PrimitiveTexture::createSingleton();
    agl::utl::PrimitiveTexture::instance()->initialize();
  //agl::utl::PrimitiveVertex::createSingleton();
  //agl::utl::PrimitiveVertex::instance()->initialize();

    {
        rio::FileDevice::LoadArg arg;
        arg.path =
#if RIO_IS_CAFE
            getContentPath() + "/CAFE/agl_resource_cafe.sarc";
#else
            "agl_resource_cafe_dev.sarc";
#endif
        arg.alignment = 0x2000;

        mAglRes.p_archive = rio::FileDeviceMgr::instance()->load(arg);
    }
    RIO_ASSERT(mAglRes.p_archive);

    mAglRes.archive_res.prepareArchive(mAglRes.p_archive);
  //RIO_LOG("MainWindow::prepare_(): mAglRes.archive_res.prepareArchive() done\n");

    agl::detail::ShaderHolder::instance()->initialize(&mAglRes.archive_res);

  //RIO_LOG("Initialized shader holder\n");

    agl::utl::VertexAttributeHolder::createSingleton();
    agl::utl::VertexAttributeHolder::instance()->initialize();

  //RIO_LOG("Initialized agl!\n");

    ShaderHolder::createSingleton();
    ShaderHolder::instance()->initialize(getContentPath() + "/Common/shader/shaderfb");

  //RIO_LOG("Initialized ShaderHolder\n");

    ResMgr::createSingleton();

  //RIO_LOG("Created ResMgr\n");

    {
        rio::FileDevice::LoadArg arg;
        arg.path = getContentPath() + "/Common/actor/jyotyuActorPack.szs";
        arg.alignment = 0x2000;

        mJyotyuActorPack.p_archive = SZSDecompressor::tryDecomp(arg);
    }
    RIO_ASSERT(mJyotyuActorPack.p_archive);

    mJyotyuActorPack.archive_res.prepareArchive(mJyotyuActorPack.p_archive);
  //RIO_LOG("MainWindow::prepare_(): mJyotyuActorPack.archive_res.prepareArchive() done\n");

    for (const SharcArchiveRes::Entry& entry : mJyotyuActorPack.archive_res.readEntry())
        ResMgr::instance()->loadArchiveRes(entry.name, mJyotyuActorPack.archive_res.getFile(entry.name), true);

  //RIO_LOG("Initialized jyotyuActorPack\n");

    {
        rio::FileDevice::LoadArg arg;
        arg.path = getContentPath() + "/Common/actor/cobPack.szs";
        arg.alignment = 0x2000;

        mCobPack.p_archive = SZSDecompressor::tryDecomp(arg);
    }
    RIO_ASSERT(mCobPack.p_archive);

    mCobPack.archive_res.prepareArchive(mCobPack.p_archive);
  //RIO_LOG("MainWindow::prepare_(): mCobPack.archive_res.prepareArchive() done\n");

    for (const SharcArchiveRes::Entry& entry : mCobPack.archive_res.readEntry())
        ResMgr::instance()->loadArchiveRes(entry.name, mCobPack.archive_res.getFile(entry.name), true);

  //RIO_LOG("Initialized cobPack\n");

    ModelResMgr::createSingleton();

  //RIO_LOG("Initialized ModelResMgr\n");

    CourseData::createSingleton();

  //RIO_LOG("Created CourseData\n");

    Renderer::createSingleton();

  //RIO_LOG("Initialized Renderer\n");

    mCourseViewSize.x = width;
    mCourseViewSize.y = height;

    mCourseViewPos.x = 0.0f;
    mCourseViewPos.y = 0.0f;

    mpCourseView = new CourseView(mCourseViewSize.x, mCourseViewSize.y, mCourseViewPos);

  //RIO_LOG("Created CourseView\n");

    CoinOrigin::createSingleton();
    CoinOrigin::instance()->initialize();

    const std::string& level_path = getContentPath() + "/Common/course_res_pack/" + level_fname;
    CourseData::instance()->loadFromPack(level_path);
    setCurrentCourseDataFile(0);
}

void MainWindow::exit_()
{
    CoinOrigin::destroySingleton();

    delete mpCourseView;
    mpCourseView = nullptr;

    Renderer::destroySingleton();

    CourseData::destroySingleton();

    ModelResMgr::destroySingleton();

    for (const SharcArchiveRes::Entry& entry : mJyotyuActorPack.archive_res.readEntry())
        ResMgr::instance()->destroyArchiveRes(entry.name);

    mJyotyuActorPack.archive_res.destroy();

    rio::MemUtil::free(mJyotyuActorPack.p_archive);
    mJyotyuActorPack.p_archive = nullptr;

    for (const SharcArchiveRes::Entry& entry : mCobPack.archive_res.readEntry())
        ResMgr::instance()->destroyArchiveRes(entry.name);

    mCobPack.archive_res.destroy();

    rio::MemUtil::free(mCobPack.p_archive);
    mCobPack.p_archive = nullptr;

    ResMgr::destroySingleton();

    ShaderHolder::destroySingleton();

    agl::utl::VertexAttributeHolder::destroySingleton();

    agl::utl::PrimitiveTexture::destroySingleton();
  //agl::utl::PrimitiveVertex::destroySingleton();

    agl::utl::PrimitiveShape::destroySingleton();

    agl::detail::ShaderHolder::destroySingleton();

    mAglRes.archive_res.destroy();

    rio::MemUtil::free(mAglRes.p_archive);
    mAglRes.p_archive = nullptr;

#if RIO_IS_CAFE
    agl::driver::GX2Resource::destroySingleton();
#endif // RIO_IS_CAFE

    BgTexMgr::destroySingleton();

    if (mLayerGather.ptr != nullptr)
    {
        rio::lyr::Renderer::instance()->removeLayer(mLayerGather.it);
        mLayerGather.ptr = nullptr;
    }

    if (mLayerDispose.ptr != nullptr)
    {
        rio::lyr::Renderer::instance()->removeLayer(mLayerDispose.it);
        mLayerDispose.ptr = nullptr;
    }

    if (mLayerBgPrepare.ptr != nullptr)
    {
        rio::lyr::Renderer::instance()->removeLayer(mLayerBgPrepare.it);
        mLayerBgPrepare.ptr = nullptr;
    }

    ImGuiUtil::shutdown();

#if RIO_IS_WIN
    rio::Window::instance()->setOnResizeCallback(nullptr);
#endif // RIO_IS_WIN
}

void MainWindow::setCurrentCourseDataFile(u32 id)
{
    BgTexMgr::instance()->destroy(getBgPrepareLayer());

    CourseDataFile* p_cd_file = CourseData::instance()->getFile(id);
    if (!p_cd_file)
    {
        mCurrentFile = -1;
        mpCourseView->reset();
        return;
    }

    mCurrentFile = id;

    BgTexMgr::instance()->initialize(*p_cd_file, getBgPrepareLayer());
    CoinOrigin::instance()->pushBackDrawMethod(getBgPrepareLayer());

    mpCourseView->initialize(p_cd_file);
}

void MainWindow::processMouseInput_()
{
#if RIO_IS_WIN
    if (glfwGetWindowAttrib(rio::Window::instance()->getNativeWindow().getGLFWwindow(), GLFW_ICONIFIED))
        return;
#endif // RIO_IS_WIN

    // Checking this is kinda useless
    /*
    ImGuiIO& io = ImGui::GetIO();
    if (!io.WantCaptureMouse)
        return;
    */

    mpCourseView->updateCursorPos(mCourseViewPos);

    if (!mCourseViewFocused)
        return;

    mpCourseView->processMouseInput();
}

void MainWindow::processKeyboardInput_()
{
#if RIO_IS_WIN
    if (glfwGetWindowAttrib(rio::Window::instance()->getNativeWindow().getGLFWwindow(), GLFW_ICONIFIED))
        return;
#endif // RIO_IS_WIN

    // Checking this is kinda useless
    /*
    ImGuiIO& io = ImGui::GetIO();
    if (!io.WantCaptureKeyboard)
        return;
    */

    if (!mCourseViewFocused)
        return;

    mpCourseView->processKeyboardInput();

    if (rio::ControllerMgr::instance()->getMainController()->isTrig(1 << rio::Controller::PAD_IDX_A))
    {
        if (mCurrentFile != -1)
        {
            s32 prev_file = mCurrentFile;

            while ((mCurrentFile = (mCurrentFile + 1) % CD_FILE_MAX_NUM), !CourseData::instance()->getFile(mCurrentFile))
                continue;

            if (mCurrentFile != prev_file)
                setCurrentCourseDataFile(mCurrentFile);
        }
    }
}

void MainWindow::calc_()
{
    BgTexMgr::instance()->update();
    CoinOrigin::instance()->update();

    if (mCourseViewResized)
    {
        mpCourseView->resize(mCourseViewSize.x, mCourseViewSize.y);
        mCourseViewResized = false;
    }

    mpCourseView->update();
}

void MainWindow::gather_(const rio::lyr::DrawInfo&)
{
    mpCourseView->gather();

    CoinOrigin::instance()->draw(getBgPrepareLayer());
    mRenderMgrBgPrepare.calc();
}

void MainWindow::dispose_(const rio::lyr::DrawInfo&)
{
    mRenderMgrBgPrepare.clear();

    mpCourseView->dispose();

    ImGuiUtil::newFrame();
    {
        drawUI_();
    }
    ImGuiUtil::render();
}

void MainWindow::drawUI_()
{
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    // Metrics
    {
        ImGui::Begin("Metrics");
        {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        ImGui::End();
    }
    // Viewport
    {
        ImGui::Begin("CourseView", NULL, ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
        {
            ImVec2 pos = ImGui::GetCursorScreenPos();
            const ImVec2& size = ImGui::GetContentRegionAvail();

#if RIO_IS_WIN
            s32 window_xpos;
            s32 window_ypos;

            glfwGetWindowPos(
                rio::Window::instance()->getNativeWindow().getGLFWwindow(),
                &window_xpos, &window_ypos
            );

            pos.x -= window_xpos;
            pos.y -= window_ypos;
#endif // RIO_IS_WIN

            s32 width = std::max<s32>(1, size.x);
            s32 height = std::max<s32>(1, size.y);
            if (mCourseViewSize.x != width || mCourseViewSize.y != height)
            {
                mCourseViewSize.x = width;
                mCourseViewSize.y = height;
                mCourseViewResized = true;
            }

            ImTextureID texture_id = nullptr;

#if RIO_IS_CAFE
            mImGuiGX2Texture.Texture = const_cast<GX2Texture*>(mpCourseView->getColorTexture()->getNativeTextureHandle());
            texture_id = &mImGuiGX2Texture;
#elif RIO_IS_WIN
            texture_id = (void*)(mpCourseView->getColorTexture()->getNativeTextureHandle());
#endif

            ImGui::Image(texture_id, size);

            bool moved = false;
            if (mCourseViewPos.x != pos.x || mCourseViewPos.y != pos.y)
            {
                mCourseViewPos.x = pos.x;
                mCourseViewPos.y = pos.y;
                moved = true;
            }

            mCourseViewHovered = ImGui::IsWindowHovered();
            mCourseViewFocused = ImGui::IsWindowFocused() && !(moved || mCourseViewResized);
        }
        ImGui::End();

        processMouseInput_();
        processKeyboardInput_();
    }
}
