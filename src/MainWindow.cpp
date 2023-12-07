#include <CourseView.h>
#include <MainWindow.h>
#include <action/ActionMgr.h>
#include <course/BgTexMgr.h>
#include <course/CoinOrigin.h>
#include <course/CourseData.h>
#include <course/CourseDataFile.h>
#include <item/BgUnitItem.h>
#include <item/LocationItem.h>
#include <item/MapActorItem.h>
#include <item/NextGotoItem.h>
#include <graphics/LayerID.h>
#include <graphics/ModelResMgr.h>
#include <graphics/QuadRenderer.h>
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

#include <imgui_internal.h>

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
    , mCourseViewCameraMoved(false)
    , mMetricsLocation(0)
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

    ActionMgr::createSingleton();

    QuadRenderer::createSingleton();

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

    ActionMgr::instance()->discard(false);

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

    QuadRenderer::destroySingleton();

    ActionMgr::destroySingleton();

    ImGuiUtil::shutdown();

#if RIO_IS_WIN
    rio::Window::instance()->setOnResizeCallback(nullptr);
#endif // RIO_IS_WIN
}

void MainWindow::setCurrentCourseDataFile(u32 id)
{
    BgTexMgr::instance()->destroy(getBgPrepareLayer());
    mEnvSelectedObj = u16(-1);

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

    mpCourseView->initialize(p_cd_file, useRealZoom());
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

    // If hovered, any mouse click action should restore focus
    if (mCourseViewHovered && !mCourseViewFocused &&
        (ImGui::IsMouseClicked(ImGuiMouseButton_Left) ||
         ImGui::IsMouseClicked(ImGuiMouseButton_Right) ||
         ImGui::IsMouseClicked(ImGuiMouseButton_Middle)))
    {
        ImGuiWindow* window = ImGui::FindWindowByName("CourseView");
        if (window)
        {
            ImGui::FocusWindow(window, ImGuiFocusRequestFlags_UnlessBelowModal);
            ImGuiContext* context = ImGui::GetCurrentContext();
            mCourseViewFocused = context && context->NavWindow == window;
        }
    }

    mCourseViewCameraMoved = mpCourseView->processMouseInput(mCourseViewFocused, mCourseViewHovered);
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

    if (!mCourseViewFocused || mCourseViewCameraMoved)
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
            {
                ActionMgr::instance()->discard(true);
                setCurrentCourseDataFile(mCurrentFile);
            }
        }
    }
}

void MainWindow::calc_()
{
    ImGuiUtil::newFrame();

    BgTexMgr::instance()->update();
    CoinOrigin::instance()->update();

    drawCourseViewUI_();
    drawPaletteUI_();
    drawSelectionUI_();
    drawMainMenuBarUI_();

    if (mCourseViewResized)
    {
        mpCourseView->resize(mCourseViewSize.x, mCourseViewSize.y, preserveUnitSize() && !useRealZoom());
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

    ImGuiUtil::render();
}

void MainWindow::drawMetricsUI_()
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
    if (mMetricsLocation >= 0)
    {
        const float PAD = 10.0f;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
        ImVec2 work_size = viewport->WorkSize;
        ImVec2 window_pos, window_pos_pivot;
        window_pos.x = (mMetricsLocation & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
        window_pos.y = (mMetricsLocation & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
        window_pos_pivot.x = (mMetricsLocation & 1) ? 1.0f : 0.0f;
        window_pos_pivot.y = (mMetricsLocation & 2) ? 1.0f : 0.0f;
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
        ImGui::SetNextWindowViewport(viewport->ID);
        window_flags |= ImGuiWindowFlags_NoMove;
    }
    else if (mMetricsLocation == -2)
    {
        // Center window
        ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        window_flags |= ImGuiWindowFlags_NoMove;
    }
    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
    if (ImGui::Begin("Metrics", nullptr, window_flags))
    {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)\n"
                    "(right-click to change position)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::MenuItem("Custom",       nullptr, mMetricsLocation == -1)) mMetricsLocation = -1;
            if (ImGui::MenuItem("Center",       nullptr, mMetricsLocation == -2)) mMetricsLocation = -2;
            if (ImGui::MenuItem("Top-left",     nullptr, mMetricsLocation ==  0)) mMetricsLocation = 0;
            if (ImGui::MenuItem("Top-right",    nullptr, mMetricsLocation ==  1)) mMetricsLocation = 1;
            if (ImGui::MenuItem("Bottom-left",  nullptr, mMetricsLocation ==  2)) mMetricsLocation = 2;
            if (ImGui::MenuItem("Bottom-right", nullptr, mMetricsLocation ==  3)) mMetricsLocation = 3;
            ImGui::EndPopup();
        }
    }
    ImGui::End();
}

void MainWindow::drawCourseViewUI_()
{
    ImGuiID id = ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_NoDockingInCentralNode | ImGuiDockNodeFlags_PassthruCentralNode, nullptr);
    ImGuiDockNode* node = ImGui::DockBuilderGetCentralNode(id);

    ImGuiWindowClass centralAlways = {};
    centralAlways.DockNodeFlagsOverrideSet |= ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_NoDockingOverMe;
    ImGui::SetNextWindowClass(&centralAlways);
    ImGui::SetNextWindowDockID(node->ID, ImGuiCond_Always);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
    bool ret = ImGui::Begin("CourseView", nullptr, ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
    ImGui::PopStyleVar();
    if (ret)
    {
        ImVec2 pos = ImGui::GetCursorScreenPos();
        const ImVec2& size = ImGui::GetContentRegionAvail();

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

        drawMetricsUI_();
    }
    ImGui::End();

    processMouseInput_();
    processKeyboardInput_();
}

static void DrawBgUnitObj(u8 env, const BgTexMgr::UnitObjTexVector& obj_textures, u16& selected)
{
    const ImVec2& spacing = ImGui::GetStyle().ItemSpacing;
    const f32 window_max_x = ImGui::GetWindowContentRegionMax().x;

    ImVec2 cursor_pos = ImGui::GetCursorPos();
    cursor_pos.x += spacing.x;
    cursor_pos.y += spacing.y;

    const f32 line_start_x = cursor_pos.x;
    f32 line_max_y = 0.0f;

    const int num_objects = obj_textures.size();
    for (int n = 0; n < num_objects; n++)
    {
        char buf[32];
        sprintf(buf, "Object %d", n);

        const ImVec2& label_size = ImGui::CalcTextSize(buf, NULL, true);
        ImVec2 self_box_size = label_size;

        ImVec2 icon_size { 0.0f, 0.0f };
        const rio::Texture2D* obj_tex = obj_textures[n].get();
        if (obj_tex)
        {
            icon_size.x = obj_tex->getWidth()  * 32 / 60.0f;
            icon_size.y = obj_tex->getHeight() * 32 / 60.0f;

            if (icon_size.x >= icon_size.y)
            {
                if (icon_size.x > 256)
                {
                    icon_size.y *= 256 / icon_size.x;
                    icon_size.x = 256;
                }
            }
            else
            {
                if (icon_size.y > 256)
                {
                    icon_size.x *= 256 / icon_size.y;
                    icon_size.y = 256;
                }
            }

            self_box_size.x = std::max<f32>(self_box_size.x, icon_size.x),
            self_box_size.y += spacing.y + icon_size.y;
        }

        if (cursor_pos.x != line_start_x && cursor_pos.x + self_box_size.x + spacing.x > window_max_x)
        {
            cursor_pos.x = line_start_x;
            cursor_pos.y += line_max_y + spacing.y;
            line_max_y = 0.0f;
        }

        ImGui::SetCursorPos(cursor_pos);

        u16 type = env << 12 | n;
        if (ImGui::Selectable(buf, selected == type, 0, self_box_size))
            selected = type;

        if (obj_tex)
        {
            ImGui::SetCursorPos({ cursor_pos.x + std::max<f32>(0.0f, (label_size.x - icon_size.x) * 0.5f), cursor_pos.y + label_size.y + spacing.y });
            ImGui::Image((void*)obj_tex->getNativeTextureHandle(), icon_size);
        }

        cursor_pos.x += self_box_size.x + spacing.x;
        line_max_y = std::max<f32>(line_max_y, self_box_size.y);
    }
}

void MainWindow::drawPaletteUI_()
{
    /*
    if (ImGui::Begin("Comments"))
    {
        ImGui::Text("Placeholder...");
    }
    ImGui::End();

    if (ImGui::Begin("Stamps"))
    {
        ImGui::Text("Placeholder...");
    }
    ImGui::End();

    if (ImGui::Begin("Events"))
    {
        if (ImGui::BeginListBox("##PathList", ImVec2(-1, -1)))
        {
            static bool events[64] = { false };

            for (int n = 0; n < IM_ARRAYSIZE(events); n++)
            {
                char buf[32];
                sprintf(buf, "Event %d", n + 1);
                ImGui::Checkbox(buf, &events[n]);
            }
            ImGui::EndListBox();
        }
    }
    ImGui::End();

    if (ImGui::Begin("Nabbit Path"))
    {
        if (ImGui::BeginListBox("##PathList", ImVec2(-1, -1)))
        {
            static const char* items[] = { "Nabbit Path, Node 0", "Nabbit Path, Node 1", "Nabbit Path, Node 2" };
            static int selected = -1;

            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                if (ImGui::Selectable(items[n], selected == n))
                    selected = n;
            }
            ImGui::EndListBox();
        }
    }
    ImGui::End();

    if (ImGui::Begin("Paths"))
    {
        if (ImGui::BeginListBox("##PathList", ImVec2(-1, -1)))
        {
            static const char* items[] = { "Path 1, Node 0", "Path 1, Node 1", "Path 1, Node 2" };
            static int selected = -1;

            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                if (ImGui::Selectable(items[n], selected == n))
                    selected = n;
            }
            ImGui::EndListBox();
        }
    }
    ImGui::End();
    */

    if (ImGui::Begin("Locations"))
    {
        if (ImGui::BeginListBox("##LocationList", ImVec2(-1, -1)))
        {
            static const char* items[] = { "0: Location 0 (at 234, 2384)", "1: Location 9 (at 84, 865)" };
            static int selected = -1;

            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                if (ImGui::Selectable(items[n], selected == n))
                    selected = n;
            }
            ImGui::EndListBox();
        }
    }
    ImGui::End();

    if (ImGui::Begin("Entrances"))
    {
        if (ImGui::BeginListBox("##EntranceList", ImVec2(-1, -1)))
        {
            static const char* items[] = { "0: (0) Normal (enterable)", "1: (1) Pipe Facing Up (enterable)", "2: (2) Pipe Facing Up (cannot be entered)", "3: (3) Checkpoint", "4: (4) Normal (enterable)", "5: (5) Falling (Fast) (enterable)" };
            static int selected = -1;

            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                if (ImGui::Selectable(items[n], selected == n))
                    selected = n;
            }
            ImGui::EndListBox();
        }
    }
    ImGui::End();

    if (ImGui::Begin("Actors"))
    {
        if (ImGui::BeginTabBar("ActorTabBar"))
        {
            if (ImGui::BeginTabItem("Add"))
            {
                static ImGuiTextFilter filter;
                filter.Draw("##ActorSearch", -1);

                if (ImGui::BeginListBox("##ActorSearchList", ImVec2(-1, -1)))
                {
                    static const char* items[] = { "0: Goomba", "1: Koopa", "2: Flag Pole", "3: Checkpoint", "4: Koopa Paratroopa", "5: Bowser" };
                    static int selected = -1;

                    for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                    {
                        if (filter.PassFilter(items[n]) && ImGui::Selectable(items[n], selected == n))
                            selected = n;
                    }
                    ImGui::EndListBox();
                }
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Current"))
            {
                if (ImGui::BeginListBox("##ActorList", ImVec2(-1, -1)))
                {
                    static const char* items[] = { "0: Goomba (at 3654, 365)", "1: Koopa Troopa (at 247,234)" };
                    static int selected = -1;

                    for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                    {
                        if (ImGui::Selectable(items[n], selected == n))
                            selected = n;
                    }
                    ImGui::EndListBox();
                }
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
    }
    ImGui::End();

    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyleColorVec4(ImGuiCol_DockingEmptyBg));
    if (ImGui::Begin("Environment"))
    {
        if (ImGui::BeginTabBar("EnvironmentTabBar"))
        {
            if (ImGui::BeginTabItem("Embedded"))
            {
                const BgTexMgr::UnitObjTexArray& obj_tex_array = BgTexMgr::instance()->getUnitObjTexArray();

                if (ImGui::CollapsingHeader("Slot 0", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    if (ImGui::BeginChild("Env0", ImVec2(0, 0), ImGuiChildFlags_AutoResizeY))
                    {
                        DrawBgUnitObj(0, obj_tex_array[0], mEnvSelectedObj);
                    }
                    ImGui::EndChild();
                }

                if (ImGui::CollapsingHeader("Slot 1", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    if (ImGui::BeginChild("Env1", ImVec2(0, 0), ImGuiChildFlags_AutoResizeY))
                    {
                        DrawBgUnitObj(1, obj_tex_array[1], mEnvSelectedObj);
                    }
                    ImGui::EndChild();
                }

                if (ImGui::CollapsingHeader("Slot 2", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    if (ImGui::BeginChild("Env2", ImVec2(0, 0), ImGuiChildFlags_AutoResizeY))
                    {
                        DrawBgUnitObj(2, obj_tex_array[2], mEnvSelectedObj);
                    }
                    ImGui::EndChild();
                }

                if (ImGui::CollapsingHeader("Slot 3", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    if (ImGui::BeginChild("Env3", ImVec2(0, 0), ImGuiChildFlags_AutoResizeY))
                    {
                        DrawBgUnitObj(3, obj_tex_array[3], mEnvSelectedObj);
                    }
                    ImGui::EndChild();
                }

                ImGui::EndTabItem();
            }
            /*
            if (ImGui::BeginTabItem("All"))
            {
                if (ImGui::BeginChild("AllObjects"))
                {
                    static int selected = -1;
                    static const int num_objects = 120;
                    static const ImVec2 box_size(120, 120);

                    ImGuiStyle& style = ImGui::GetStyle();
                    float window_visible_x = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

                    for (int n = 0; n < num_objects; n++)
                    {
                        char buf[32];
                        sprintf(buf, "Object %d", n);
                        if (ImGui::Selectable(buf, selected == n, 0, box_size))
                            selected = n;

                        float last_box_x = ImGui::GetItemRectMax().x;
                        float next_box_x = last_box_x + style.ItemSpacing.x + box_size.x;
                        if (n + 1 < num_objects && next_box_x < window_visible_x)
                            ImGui::SameLine();
                    }
                }
                ImGui::EndChild();
                ImGui::EndTabItem();
            }
            */
            ImGui::EndTabBar();
        }
    }
    ImGui::End();
    ImGui::PopStyleColor();
}

void MainWindow::drawSelectionUI_()
{
    if (!mpCourseView)
        return;

    mpCourseView->drawSelectionUI();
}

void MainWindow::drawMainMenuBarUI_()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", nullptr, false, ActionMgr::instance()->canUndo()))
            {
                mpCourseView->clearSelection();
                ActionMgr::instance()->undo();
            }

            if (ImGui::MenuItem("Redo", nullptr, false, ActionMgr::instance()->canRedo()))
            {
                mpCourseView->clearSelection();
                ActionMgr::instance()->redo();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}
