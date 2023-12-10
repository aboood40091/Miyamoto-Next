#include <CourseView.h>
#include <Globals.h>
#include <MainWindow.h>
#include <action/ActionMgr.h>
#include <actor/ActorCreateMgr.h>
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

#include <format>

static const char* level_fname = "1-1.szs";
static const std::string nsmbu_content_path = "game/nsmbu";

const std::string& Globals::getContentPath()
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
    , mPaintType(ITEM_TYPE_MAX_NUM)
    , mEnvPaintLayer(LAYER_1)
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
    setupUiStyle_();

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
    ShaderHolder::instance()->initialize(Globals::getContentPath() + "/Common/shader/shaderfb");

  //RIO_LOG("Initialized ShaderHolder\n");

    ResMgr::createSingleton();

  //RIO_LOG("Created ResMgr\n");

    {
        rio::FileDevice::LoadArg arg;
        arg.path = Globals::getContentPath() + "/Common/actor/jyotyuActorPack.szs";
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
        arg.path = Globals::getContentPath() + "/Common/actor/cobPack.szs";
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

    CourseView::createSingleton(mCourseViewSize.x, mCourseViewSize.y, mCourseViewPos);
    mpCourseView = CourseView::instance();

  //RIO_LOG("Created CourseView\n");

    CoinOrigin::createSingleton();
    CoinOrigin::instance()->initialize();

    ActionMgr::instance()->discard(false);

    const std::string& level_path = Globals::getContentPath() + "/Common/course_res_pack/" + level_fname;
    CourseData::instance()->loadFromPack(level_path);
    setCurrentCourseDataFile(0);
}

void MainWindow::exit_()
{
    CoinOrigin::destroySingleton();

    mpCourseView = nullptr;
    CourseView::destroySingleton();

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

    mpCourseView->initialize(p_cd_file, Globals::useRealZoom());
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
        mpCourseView->resize(mCourseViewSize.x, mCourseViewSize.y, Globals::preserveUnitSize() && !Globals::useRealZoom());
        mCourseViewResized = false;
    }

    switch (mPaintType)
    {
    default:
        mpCourseView->setPaintType_None();
        break;
    case ITEM_TYPE_BG_UNIT_OBJ:
        if (mEnvSelectedObj == u16(-1))
            mpCourseView->setPaintType_None();
        else
            mpCourseView->setPaintType_BgUnitObj(mEnvPaintLayer, mEnvSelectedObj);
        break;
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
        const std::string& label = std::format("##Env {0:d} Object {1:d}", s32(env), n);

        ImVec2 self_box_size;
        ImVec2 icon_size;
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
        if (ImGui::Selectable(label.c_str(), selected == type, 0, self_box_size))
            selected = type;

        if (obj_tex)
        {
            ImGui::SetCursorPos({ cursor_pos.x + std::max<f32>(0.0f, (self_box_size.x - icon_size.x) * 0.5f), cursor_pos.y + std::max<f32>(0.0f, (self_box_size.y - icon_size.y) * 0.5f) });
#if RIO_IS_WIN
            ImGui::Image((void*)obj_tex->getNativeTextureHandle(), icon_size);
#endif // RIO_IS_WIN
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
                const std::string& label = std::format("Event {0:d}", n + 1);
                ImGui::Checkbox(label.c_str(), &events[n]);
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
        if (ImGui::IsWindowFocused())
            mPaintType = ITEM_TYPE_LOCATION;

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
        if (ImGui::IsWindowFocused())
            mPaintType = ITEM_TYPE_NEXT_GOTO;

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
        bool focused = ImGui::IsWindowFocused();

        if (ImGui::BeginTabBar("ActorTabBar"))
        {
            if (ImGui::BeginTabItem("Add"))
            {
                if (focused)
                    mPaintType = ITEM_TYPE_MAP_ACTOR;

                static ImGuiTextFilter filter;
                filter.Draw("##ActorAddSearch", -1);

                if (ImGui::BeginListBox("##ActorAddList", ImVec2(-1, -1)))
                {
                    static int selected = -1;

                    for (int n = 0; n < ActorCreateMgr::instance()->getMaxID(); n++)
                    {
                        const std::u8string& name = ActorCreateMgr::instance()->getName(n);
                        const std::string& str =
                            name.empty()
                                ? std::to_string(n)
                                : std::format("{0:d}: {1:s}", n, (const char*)name.c_str());

                        if (filter.PassFilter(str.c_str()) && ImGui::Selectable(str.c_str(), selected == n))
                            selected = n;
                    }
                    ImGui::EndListBox();
                }
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Current"))
            {
                if (focused)
                    mPaintType = ITEM_TYPE_MAX_NUM;

                static ImGuiTextFilter filter;
                filter.Draw("##ActorCurrentSearch", -1);

                if (ImGui::BeginListBox("##ActorCurrentList", ImVec2(-1, -1)))
                {
                    const std::vector< std::unique_ptr<MapActorItem> >& item_vec = mpCourseView->getMapActorItem();
                    const std::vector<MapActorData>& data_vec = mpCourseView->getCourseDataFile()->getMapActorData();
                    for (u32 i = 0; i < item_vec.size(); i++)
                    {
                        const MapActorItem& map_actor_item = *(item_vec[i]);
                        const MapActorData& map_actor_data = data_vec[i];
                        const std::u8string& name = ActorCreateMgr::instance()->getName(map_actor_data.id);
                        const std::string& str =
                            name.empty()
                                ? std::format("{0:d}: ({1:d}, {2:d})", map_actor_data.id, map_actor_data.offset.x, map_actor_data.offset.y)
                                : std::format("{0:d}: {1:s} ({2:d}, {3:d})", map_actor_data.id, (const char*)name.c_str(), map_actor_data.offset.x, map_actor_data.offset.y);

                        if (filter.PassFilter(str.c_str()) && ImGui::Selectable(str.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick) && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                        {
                            mpCourseView->setCameraCenterWorldPos({ f32(map_actor_data.offset.x + 8), -f32(map_actor_data.offset.y + 8) });
                            mpCourseView->selectItem(map_actor_item.getItemID());
                        }
                    }
                    ImGui::EndListBox();
                }
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
    }
    ImGui::End();

    if (ImGui::Begin("Environment"))
    {
        if (ImGui::IsWindowFocused())
            mPaintType = ITEM_TYPE_BG_UNIT_OBJ;

        ImGui::RadioButton("Layer 0", &mEnvPaintLayer, LAYER_0); ImGui::SameLine();
        ImGui::RadioButton("Layer 1", &mEnvPaintLayer, LAYER_1); ImGui::SameLine();
        ImGui::RadioButton("Layer 2", &mEnvPaintLayer, LAYER_2);

        if (ImGui::BeginTabBar("EnvironmentTabBar"))
        {
            if (ImGui::BeginTabItem("Embedded"))
            {
                if (ImGui::BeginChild("EmbeddedScrollable"))
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
                }
                ImGui::EndChild();

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
                        const std::string& label = std::format("Object {0:d}", n);
                        if (ImGui::Selectable(label.c_str(), selected == n, 0, box_size))
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

void MainWindow::setupUiStyle_()
{
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();

    //Fonts
    io.Fonts->AddFontFromFileTTF(rio::FileDeviceMgr::instance()->getDefaultFileDevice()->getNativePath("fonts/Noto_Sans_JP/NotoSansJP-Medium.ttf").c_str(), 20, nullptr, io.Fonts->GetGlyphRangesJapanese());

    // Colors
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.07f, 0.12f, 0.15f, 1.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4(0.43f, 0.48f, 0.50f, 0.50f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.16f, 0.39f, 0.48f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.26f, 0.77f, 0.98f, 0.40f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.26f, 0.77f, 0.98f, 0.67f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.16f, 0.38f, 0.48f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.26f, 0.77f, 0.98f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.24f, 0.69f, 0.88f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.26f, 0.77f, 0.98f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.26f, 0.77f, 0.98f, 0.40f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.26f, 0.77f, 0.98f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.06f, 0.71f, 0.98f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.26f, 0.77f, 0.98f, 0.31f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.26f, 0.77f, 0.98f, 0.80f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.26f, 0.77f, 0.98f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.48f, 0.50f, 0.50f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.10f, 0.56f, 0.75f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.10f, 0.56f, 0.75f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.26f, 0.77f, 0.98f, 0.20f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.77f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.77f, 0.98f, 0.95f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.18f, 0.46f, 0.58f, 0.86f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.26f, 0.77f, 0.98f, 0.80f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.20f, 0.54f, 0.68f, 1.00f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.07f, 0.13f, 0.15f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.34f, 0.42f, 1.00f);
    colors[ImGuiCol_DockingPreview]         = ImVec4(0.26f, 0.77f, 0.98f, 0.70f);
    colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(0.35f, 0.81f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.00f, 0.63f, 0.90f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(0.00f, 0.71f, 1.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.34f, 0.35f, 1.00f);
    colors[ImGuiCol_TableBorderLight]       = ImVec4(0.25f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.77f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(0.00f, 0.71f, 1.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.77f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    // Rounding
    style.ChildRounding = 4.0f;
    style.FrameRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.PopupRounding = 4.0f;
    style.ScrollbarRounding = 4.0f;
    style.TabRounding = 4.0f;
    style.WindowRounding = 4.0f;
}
