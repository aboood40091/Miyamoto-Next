#include <CourseView.h>
#include <Globals.h>
#include <MainWindow.h>
#include <action/ActionMgr.h>
#include <actor/ActorCreateMgr.h>
#include <course/BgTexMgr.h>
#include <course/CoinOrigin.h>
#include <course/CourseData.h>
#include <course/CourseDataFile.h>
#include <item/AreaItem.h>
#include <item/BgUnitItem.h>
#include <item/LocationItem.h>
#include <item/MapActorItem.h>
#include <item/NextGotoItem.h>
#include <graphics/LayerID.h>
#include <graphics/ModelResMgr.h>
#include <graphics/QuadRenderer.h>
#include <graphics/Renderer.h>
#include <graphics/ShaderHolder.h>
#include <resource/SZSCompressor.h>
#include <resource/SZSDecompressor.h>
#include <system/ResMgr.h>
#include <ui/ImGuiUtil.h>
#include <ui/ThemeMgr.h>

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

#include <misc/win/rio_Windows.h>
#include <commdlg.h>

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#endif // RIO_IS_WIN

#include <rio.h>

#include <imgui_internal.h>

#include <format>
#include <functional>

static const char* level_fname = "1-1.szs";

MainWindow::MainWindow()
    : rio::ITask("Miyamoto! Next")
    , mpCourseView(nullptr)
    , mCourseViewResized(false)
    , mCourseViewHovered(false)
    , mCourseViewFocused(false)
    , mCourseViewCameraMoved(false)
    , mPaintType(ITEM_TYPE_MAX_NUM)
    , mEnvSelectedObj(u16(-1))
    , mEnvPaintLayer(LAYER_1)
    , mMapActorSelectedType(u16(-1))
    , mPopupOpen(false)
    , mPopupType(POPUP_TYPE_NONE)
    , mPopupCallbackType(POPUP_CALLBACK_TYPE_NONE)
    , mNextFile(0)
    , mItemSelectFlag(0)
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

    // Load imgui font
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF(rio::FileDeviceMgr::instance()->getDefaultFileDevice()->getNativePath("fonts/Noto_Sans_JP/NotoSansJP-Medium.ttf").c_str(), 20, nullptr, io.Fonts->GetGlyphRangesJapanese());

#if RIO_IS_CAFE
    GX2InitSampler(&mGX2Sampler, GX2_TEX_CLAMP_MODE_CLAMP, GX2_TEX_XY_FILTER_MODE_POINT);
    mImGuiGX2Texture.Sampler = &mGX2Sampler;
#endif // RIO_IS_CAFE

    ThemeMgr::createSingleton();
    ThemeMgr::instance()->applyTheme(ThemeMgr::sDefaultTheme);

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
            Globals::sContentPath + "/CAFE/agl_resource_cafe.sarc";
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
    ShaderHolder::instance()->initialize(Globals::sContentPath + "/Common/shader/shaderfb");

  //RIO_LOG("Initialized ShaderHolder\n");

    ResMgr::createSingleton();

  //RIO_LOG("Created ResMgr\n");

    {
        rio::FileDevice::LoadArg arg;
        arg.path = Globals::sContentPath + "/Common/actor/jyotyuActorPack.szs";
        arg.alignment = 0x2000;

        mJyotyuActorPack.p_archive = SZSDecompressor::tryDecomp(arg);
    }
    RIO_ASSERT(mJyotyuActorPack.p_archive);

    mJyotyuActorPack.archive_res.prepareArchive(mJyotyuActorPack.p_archive);
  //RIO_LOG("MainWindow::prepare_(): mJyotyuActorPack.archive_res.prepareArchive() done\n");

    for (const SharcArchiveRes::Entry& entry : mJyotyuActorPack.archive_res.readEntry())
        ResMgr::instance()->loadArchiveRes(entry.name, mJyotyuActorPack.archive_res.getFileConst(entry.name), true);

  //RIO_LOG("Initialized jyotyuActorPack\n");

    {
        rio::FileDevice::LoadArg arg;
        arg.path = Globals::sContentPath + "/Common/actor/cobPack.szs";
        arg.alignment = 0x2000;

        mCobPack.p_archive = SZSDecompressor::tryDecomp(arg);
    }
    RIO_ASSERT(mCobPack.p_archive);

    mCobPack.archive_res.prepareArchive(mCobPack.p_archive);
  //RIO_LOG("MainWindow::prepare_(): mCobPack.archive_res.prepareArchive() done\n");

    for (const SharcArchiveRes::Entry& entry : mCobPack.archive_res.readEntry())
        ResMgr::instance()->loadArchiveRes(entry.name, mCobPack.archive_res.getFileConst(entry.name), true);

  //RIO_LOG("Initialized cobPack\n");

    ModelResMgr::createSingleton();

  //RIO_LOG("Initialized ModelResMgr\n");

    CourseData::createSingleton();

  //RIO_LOG("Created CourseData\n");

    Renderer::createSingleton();

  //RIO_LOG("Initialized Renderer\n");

    CoinOrigin::createSingleton();
    CoinOrigin::instance()->initialize();

    mCourseViewSize.x = width;
    mCourseViewSize.y = height;

    mCourseViewPos.x = 0.0f;
    mCourseViewPos.y = 0.0f;

    CourseView::createSingleton(mCourseViewSize.x, mCourseViewSize.y, mCourseViewPos);
    mpCourseView = CourseView::instance();

  //RIO_LOG("Created CourseView\n");

    const std::string& level_path = Globals::sContentPath + "/Common/course_res_pack/" + level_fname;
    if (CourseData::instance()->loadFromPack(level_path))
    {
        mCoursePath = level_path;
        RIO_LOG("mCoursePath set to: %s\n", mCoursePath.c_str());
    }
    else
    {
        CourseData::instance()->createNew();
        mCoursePath.clear();
        RIO_LOG("mCoursePath cleared\n");
    }
    ActionMgr::instance()->discard(false);
    setCurrentCourseDataFile_(0);
}

void MainWindow::exit_()
{
    mpCourseView = nullptr;
    CourseView::destroySingleton();

    CoinOrigin::destroySingleton();

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

    ThemeMgr::destroySingleton();

    ImGuiUtil::shutdown();

#if RIO_IS_WIN
    rio::Window::instance()->setOnResizeCallback(nullptr);
#endif // RIO_IS_WIN
}

void MainWindow::setCurrentCourseDataFile_(u32 id)
{
    BgTexMgr::instance()->destroy(getBgPrepareLayer());

    mEnvSelectedObj = u16(-1);

    CourseDataFile& cd_file = CourseData::instance()->getCourseDataFile(id);
    RIO_ASSERT(cd_file.isValid());

    mCurrentFile = id;

    BgTexMgr::instance()->initialize(cd_file, getBgPrepareLayer());
    CoinOrigin::instance()->pushBackDrawMethod(getBgPrepareLayer());

    mpCourseView->initialize(cd_file, Globals::sUseRealZoom);
}

void MainWindow::courseNew_()
{
    CourseData::instance()->createNew();
    mCoursePath.clear();
    RIO_LOG("mCoursePath cleared\n");
    ActionMgr::instance()->discard(false);
    setCurrentCourseDataFile_(0);
}

void MainWindow::courseNew()
{
    if (ActionMgr::instance()->isDirty())
    {
        RIO_ASSERT(mPopupType == POPUP_TYPE_NONE);
        mPopupOpen = true;
        mPopupType = POPUP_TYPE_SAVE;
        mPopupCallbackType = POPUP_CALLBACK_TYPE_COURSE_NEW;
    }
    else
    {
        courseNew_();
    }
}

void MainWindow::courseOpen_()
{
#if RIO_IS_WIN
    const char* filter = "Course pack (*.sarc *.szs)\0*.sarc;*.szs\0"
                         "Compressed course pack (*.szs)\0*.szs\0"
                         "Uncompressed course pack (*.sarc)\0*.sarc\0";

    OPENFILENAMEA ofn;
    CHAR szFile[260] = { 0 };
    CHAR currentDir[256] = { 0 };
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = glfwGetWin32Window(rio::Window::instance()->getNativeWindow().getGLFWwindow());
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    if (GetCurrentDirectoryA(256, currentDir))
        ofn.lpstrInitialDir = currentDir;
    ofn.lpstrFilter = filter;
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    if (!GetOpenFileNameA(&ofn))
        return;

    RIO_LOG("Chose file: %s\n", ofn.lpstrFile);
    std::string level_path = "native://";
    level_path += ofn.lpstrFile;

    if (!CourseData::instance()->loadFromPack(level_path))
        return;

    mCoursePath = level_path;
    RIO_LOG("mCoursePath set to: %s\n", mCoursePath.c_str());
    ActionMgr::instance()->discard(false);
    setCurrentCourseDataFile_(0);
#endif // RIO_IS_WIN
}

void MainWindow::courseOpen()
{
    if (ActionMgr::instance()->isDirty())
    {
        RIO_ASSERT(mPopupType == POPUP_TYPE_NONE);
        mPopupOpen = true;
        mPopupType = POPUP_TYPE_SAVE;
        mPopupCallbackType = POPUP_CALLBACK_TYPE_COURSE_OPEN;
    }
    else
    {
        courseOpen_();
    }
}

void MainWindow::courseSave()
{
    if (mCoursePath.empty())
        return courseSaveAs();

    RIO_LOG("Save as file: %s\n", mCoursePath.c_str());

    bool to_compress = mCoursePath.ends_with(".szs");

    std::span<u8> out = CourseData::instance()->save();
    RIO_ASSERT(out.data() && out.size());

    if (to_compress)
    {
        const std::span<u8>& out_szs = SZSCompressor::compressFast(out);
        RIO_ASSERT(out_szs.data() && out_szs.size());
        rio::MemUtil::free(out.data());
        out = out_szs;
    }

    rio::FileHandle handle;
    if (rio::FileDeviceMgr::instance()->tryOpen(&handle, mCoursePath, rio::FileDevice::FILE_OPEN_FLAG_WRITE) &&
        handle.tryWrite(nullptr, out.data(), out.size()) &&
        handle.tryClose())
    {
        ActionMgr::instance()->onSave();
    }

    rio::MemUtil::free(out.data());
}

void MainWindow::courseSaveAs()
{
#if RIO_IS_WIN
    const char* filter = "Course pack (*.sarc *.szs)\0*.sarc;*.szs\0"
                         "Compressed course pack (*.szs)\0*.szs\0"
                         "Uncompressed course pack (*.sarc)\0*.sarc\0";

    OPENFILENAMEA ofn;
    CHAR szFile[260] = { 0 };
    CHAR currentDir[256] = { 0 };
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = glfwGetWin32Window(rio::Window::instance()->getNativeWindow().getGLFWwindow());
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    if (GetCurrentDirectoryA(256, currentDir))
        ofn.lpstrInitialDir = currentDir;
    ofn.lpstrFilter = filter;
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

    // Sets the default extension by extracting it from the filter
    ofn.lpstrDefExt = strchr(filter, '\0') + 1;

    if (!GetSaveFileNameA(&ofn))
        return;

    RIO_LOG("Save as file: %s\n", ofn.lpstrFile);
    std::string level_path = "native://";
    level_path += ofn.lpstrFile;

    bool to_compress = level_path.ends_with(".szs");

    std::span<u8> out = CourseData::instance()->save();
    RIO_ASSERT(out.data() && out.size());

    if (to_compress)
    {
        const std::span<u8>& out_szs = SZSCompressor::compressFast(out);
        RIO_ASSERT(out_szs.data() && out_szs.size());
        rio::MemUtil::free(out.data());
        out = out_szs;
    }

    rio::FileHandle handle;
    if (rio::FileDeviceMgr::instance()->tryOpen(&handle, level_path, rio::FileDevice::FILE_OPEN_FLAG_WRITE) &&
        handle.tryWrite(nullptr, out.data(), out.size()) &&
        handle.tryClose())
    {
        mCoursePath = level_path;
        RIO_LOG("mCoursePath set to: %s\n", mCoursePath.c_str());
        ActionMgr::instance()->onSave();
    }

    rio::MemUtil::free(out.data());
#endif // RIO_IS_WIN
}

void MainWindow::courseFileSwitch_(u32 file_index)
{
    ActionMgr::instance()->discard(ActionMgr::instance()->isDirty());
    setCurrentCourseDataFile_(file_index);
}

void MainWindow::courseItemSelect()
{
    RIO_ASSERT(mPopupType == POPUP_TYPE_NONE);
    mPopupOpen = true;
    mPopupType = POPUP_TYPE_SELECT;
    mPopupCallbackType = POPUP_CALLBACK_TYPE_COURSE_ITEM_SELECT;
}

void MainWindow::handlePopupCallback_()
{
    switch (mPopupCallbackType)
    {
    default:
        break;
    case POPUP_CALLBACK_TYPE_COURSE_NEW:
        courseNew_();
        break;
    case POPUP_CALLBACK_TYPE_COURSE_OPEN:
        courseOpen_();
        break;
    case POPUP_CALLBACK_TYPE_COURSE_FILE_SWITCH:
        courseFileSwitch_(mNextFile);
        break;
    case POPUP_CALLBACK_TYPE_COURSE_ITEM_SELECT:
        mpCourseView->selectItems(mItemSelectFlag);
        break;
    }
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
}

void MainWindow::calc_()
{
    ImGuiUtil::newFrame();

    BgTexMgr::instance()->update();
    CoinOrigin::instance()->update();

    drawCourseViewUI_();
    drawPaletteUI_();
    drawSelectionUI_();
    drawFileOptionsUI_();
    drawMainMenuBarUI_();

    if (mCourseViewResized)
    {
        mpCourseView->resize(mCourseViewSize.x, mCourseViewSize.y, Globals::sPreserveUnitSize && !Globals::sUseRealZoom);
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
    case ITEM_TYPE_MAP_ACTOR:
        if (mMapActorSelectedType >= ActorCreateMgr::instance()->getTypeMaxNum())
            mpCourseView->setPaintType_None();
        else
            mpCourseView->setPaintType_MapActor(mMapActorSelectedType);
        break;
    case ITEM_TYPE_NEXT_GOTO:
        mpCourseView->setPaintType_NextGoto();
        break;
    case ITEM_TYPE_LOCATION:
        mpCourseView->setPaintType_Location();
        break;
    case ITEM_TYPE_AREA:
        mpCourseView->setPaintType_Area();
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

    if (ImGui::Begin("Areas"))
    {
        if (ImGui::IsWindowFocused())
            mPaintType = ITEM_TYPE_AREA;

        static ImGuiTextFilter filter;
        filter.Draw("##AreaSearch", -1);

        if (ImGui::BeginListBox("##AreaList", ImVec2(-1, -1)))
        {
            const std::vector< std::unique_ptr<AreaItem> >& item_vec = mpCourseView->getAreaItem();
            std::vector<AreaData>& data_vec = mpCourseView->getCourseDataFile().getAreaData();

            for (u32 i = 0; i < data_vec.size(); i++)
            {
                const AreaItem& area_item = *(item_vec[i]);
                const AreaData& area_data = data_vec[i];

                const std::string& str = std::format("{0:d}: ({1:d}, {2:d})", area_data.id, area_data.offset.x, area_data.offset.y);

                if (filter.PassFilter(str.c_str()) && ImGui::Selectable(str.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick) && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                {
                    mpCourseView->setCameraCenterWorldPos({ f32(area_data.offset.x + 8), -f32(area_data.offset.y + 8) });
                    mpCourseView->selectItem(area_item.getItemID());
                }
            }
            ImGui::EndListBox();
        }
    }
    ImGui::End();

    if (ImGui::Begin("Locations"))
    {
        if (ImGui::IsWindowFocused())
            mPaintType = ITEM_TYPE_LOCATION;

        static ImGuiTextFilter filter;
        filter.Draw("##LocationSearch", -1);

        if (ImGui::BeginListBox("##LocationList", ImVec2(-1, -1)))
        {
            const std::vector<LocationItem>& item_vec = mpCourseView->getLocationItem();
            const std::vector<Location>& data_vec = mpCourseView->getCourseDataFile().getLocation();

            for (u32 i = 0; i < item_vec.size(); i++)
            {
                const LocationItem& location_item = item_vec[i];
                const Location& location_data = data_vec[i];

                const std::string& str = std::format("{0:d}: ({1:d}, {2:d})", location_data.id, location_data.offset.x, location_data.offset.y);

                if (filter.PassFilter(str.c_str()) && ImGui::Selectable(str.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick) && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                {
                    mpCourseView->setCameraCenterWorldPos({ f32(location_data.offset.x + 8), -f32(location_data.offset.y + 8) });
                    mpCourseView->selectItem(location_item.getItemID());
                }
            }
            ImGui::EndListBox();
        }
    }
    ImGui::End();

    if (ImGui::Begin("NextGoto"))
    {
        if (ImGui::IsWindowFocused())
            mPaintType = ITEM_TYPE_NEXT_GOTO;

        static ImGuiTextFilter filter;
        filter.Draw("##NextGotoSearch", -1);

        if (ImGui::BeginListBox("##NextGotoList", ImVec2(-1, -1)))
        {
            const std::vector<NextGotoItem>& item_vec = mpCourseView->getNextGotoItem();
            const std::vector<NextGoto>& data_vec = mpCourseView->getCourseDataFile().getNextGoto();

            for (u32 i = 0; i < item_vec.size(); i++)
            {
                const NextGotoItem& next_goto_item = item_vec[i];
                const NextGoto& next_goto = data_vec[i];

                const std::string& str = std::format("{0:d}: ({1:d}, {2:d})", next_goto.id, next_goto.offset.x, next_goto.offset.y);

                if (filter.PassFilter(str.c_str()) && ImGui::Selectable(str.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick) && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                {
                    mpCourseView->setCameraCenterWorldPos({ f32(next_goto.offset.x + 8), -f32(next_goto.offset.y + 8) });
                    mpCourseView->selectItem(next_goto_item.getItemID());
                }
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
                    for (int n = 0; n < ActorCreateMgr::instance()->getTypeMaxNum(); n++)
                    {
                        const std::u8string& name = ActorCreateMgr::instance()->getName(n);
                        const std::string& str =
                            name.empty()
                                ? std::to_string(n)
                                : std::format("{0:d}: {1:s}", n, (const char*)name.c_str());

                        if (filter.PassFilter(str.c_str()) && ImGui::Selectable(str.c_str(), mMapActorSelectedType == n))
                            mMapActorSelectedType = n;
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
                    const std::vector<MapActorData>& data_vec = mpCourseView->getCourseDataFile().getMapActorData();
                    for (u32 i = 0; i < item_vec.size(); i++)
                    {
                        const MapActorItem& map_actor_item = *(item_vec[i]);
                        const MapActorData& map_actor_data = data_vec[i];
                        const std::u8string& name = ActorCreateMgr::instance()->getName(map_actor_data.type);
                        const std::string& str =
                            name.empty()
                                ? std::format("{0:d}: ({1:d}, {2:d})", map_actor_data.type, map_actor_data.offset.x, map_actor_data.offset.y)
                                : std::format("{0:d}: {1:s} ({2:d}, {3:d})", map_actor_data.type, (const char*)name.c_str(), map_actor_data.offset.x, map_actor_data.offset.y);

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

                    if (ImGui::CollapsingHeader("Main (Slot 0)", ImGuiTreeNodeFlags_DefaultOpen))
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

void MainWindow::drawFileOptionsUI_()
{
    if (!mpCourseView)
        return;

    mpCourseView->drawFileOptionsUI();
}

void MainWindow::drawFileOptionsMenuItemUI_()
{
    if (!mpCourseView)
        return;

    mpCourseView->drawFileOptionsMenuItemUI();
}

void MainWindow::drawMainMenuBarUI_()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New", "Ctrl+N"))
                courseNew();

            if (ImGui::MenuItem("Open...", "Ctrl+O"))
                courseOpen();

            if (ImGui::MenuItem("Save", "Ctrl+S"))
                courseSave();

            if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
                courseSaveAs();

            ImGui::Separator();

            if (ImGui::MenuItem("Settings"))
            {
                RIO_ASSERT(mPopupType == POPUP_TYPE_NONE);
                mPopupOpen = true;
                mPopupType = POPUP_TYPE_SETTINGS;
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "Ctrl+Z", false, ActionMgr::instance()->canUndo()))
                mpCourseView->undo();

            if (ImGui::MenuItem("Redo", "Ctrl+Shift+Z / Ctrl+Y", false, ActionMgr::instance()->canRedo()))
                mpCourseView->redo();

            ImGui::Separator();

            if (ImGui::MenuItem("Select All...", "Ctrl+A"))
                courseItemSelect();

            if (ImGui::MenuItem("Delete", "Delete / Backspace", false, mpCourseView->hasSelection()))
                mpCourseView->deleteSelection();

            if (ImGui::MenuItem("Copy", "Ctrl+C", false, mpCourseView->hasSelection()))
                mpCourseView->copySelection();

            if (ImGui::MenuItem("Cut", "Ctrl+X", false, mpCourseView->hasSelection()))
                mpCourseView->cutSelection();

            if (ImGui::MenuItem("Paste", "Ctrl+V", false, mpCourseView->hasClipboard()))
                mpCourseView->pasteClipboard();

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            ImGui::MenuItem("Toggle Layer 0 Visibility",    "Ctrl+1", mpCourseView->getLayerVisibility(LAYER_0));
            ImGui::MenuItem("Toggle Layer 1 Visibility",    "Ctrl+2", mpCourseView->getLayerVisibility(LAYER_1));
            ImGui::MenuItem("Toggle Layer 2 Visibility",    "Ctrl+3", mpCourseView->getLayerVisibility(LAYER_2));
            ImGui::Separator();
            ImGui::MenuItem("Toggle Actor Visibility",      "Ctrl+4", mpCourseView->getActorVisibility());
            ImGui::MenuItem("Toggle Actor Graphics",        "Ctrl+5", mpCourseView->getActorGraphicsEnable(), *mpCourseView->getActorVisibility());
            ImGui::Separator();
            ImGui::MenuItem("Toggle NextGoto Visibility",   "Ctrl+6", mpCourseView->getNextGotoVisibility());
            ImGui::Separator();
            ImGui::MenuItem("Toggle Location Visibility",   "Ctrl+7", mpCourseView->getLocationVisibility());
            // Ctrl+8 is reserved for paths and Ctrl+9 is reserved for comments

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Course"))
        {
            drawFileOptionsMenuItemUI_();

            if (ImGui::MenuItem("Create File", nullptr, false, false))
            {
                //TODO
            }

            if (ImGui::MenuItem("Delete File", nullptr, false, false))
            {
                //TODO
            }

            ImGui::Separator();

            for (u32 i = 0; i < CD_FILE_MAX_NUM; i++)
            {
                if (!CourseData::instance()->getCourseDataFile(i).isValid())
                    continue;

                const std::string& str = std::format("File {0:d}", i + 1);

                if (ImGui::MenuItem(str.c_str(), nullptr, false, mCurrentFile != i))
                {
                    if (ActionMgr::instance()->canUndo() || ActionMgr::instance()->canRedo())
                    {
                        RIO_ASSERT(mPopupType == POPUP_TYPE_NONE);
                        mPopupOpen = true;
                        mPopupType = POPUP_TYPE_ACTION_DISCARD;
                        mPopupCallbackType = POPUP_CALLBACK_TYPE_COURSE_FILE_SWITCH;
                        mNextFile = i;
                    }
                    else
                    {
                        courseFileSwitch_(i);
                    }
                }
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Environment", false))
        {
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    switch (mPopupType)
    {
    default:
        break;
    case POPUP_TYPE_SETTINGS:
        static char contentPath[260];
        static bool forceSharcfb;
        static float bigItemScale;
        static bool useRealZoom;
        static bool preserveUnitSize;
        static bool applyDistantViewScissor;
        static float scrollMovementSpeed;
        static float arrowMovementSpeed;
        static float fastArrowMovementSpeed;

        if (mPopupOpen)
        {
            ImGui::OpenPopup("Settings");
            RIO_ASSERT(Globals::sContentPath.length() < 260);
            rio::MemUtil::copy(contentPath, Globals::sContentPath.c_str(), Globals::sContentPath.length() + 1);
            forceSharcfb = Globals::sForceSharcfb;
            bigItemScale = Globals::sBigItemScale;
            useRealZoom = Globals::sUseRealZoom;
            preserveUnitSize = Globals::sPreserveUnitSize;
            applyDistantViewScissor = Globals::sApplyDistantViewScissor;
            scrollMovementSpeed = Globals::sScrollMovementSpeed;
            arrowMovementSpeed = Globals::sArrowMovementSpeed;
            fastArrowMovementSpeed = Globals::sFastArrowMovementSpeed;
            mPopupOpen = false;
        }

        if (ImGui::BeginPopupModal("Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            const std::string& current_theme = ThemeMgr::instance()->getCurrentTheme();

            if (ImGui::BeginCombo("Theme", current_theme.c_str()))
            {
                std::vector<std::string> theme_names = ThemeMgr::instance()->getThemes();
                u32 current_theme_index = std::find(theme_names.begin(), theme_names.end(), current_theme) - theme_names.begin();

                for (u32 i = 0; i < theme_names.size(); i++)
                {
                    const bool selected = i == current_theme_index;

                    if (ImGui::Selectable(theme_names[i].c_str(), selected))
                        ThemeMgr::instance()->applyTheme(theme_names[i]);

                    if (selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            ImGui::InputText("Content Path", contentPath, 260);
            ImGui::Checkbox("Decompile Shaders", &forceSharcfb);
            ImGui::InputFloat("Big Item Scale", &bigItemScale);
            ImGui::Checkbox("Use Area Zoom On Load", &useRealZoom);
            ImGui::Checkbox("Preserve Unit Size", &preserveUnitSize);
            ImGui::Checkbox("Clip DistantView To Area", &applyDistantViewScissor);
            ImGui::InputFloat("Scroll Movement Speed", &scrollMovementSpeed);
            ImGui::InputFloat("Arrow Movement Speed", &arrowMovementSpeed);
            ImGui::InputFloat("Fast Arrow Movement Speed", &fastArrowMovementSpeed);

            ImGui::Separator();

            if (ImGui::Button("Apply"))
            {
                ImGui::CloseCurrentPopup();
                mPopupType = POPUP_TYPE_NONE;

                Globals::sContentPath = contentPath;
                Globals::sForceSharcfb = forceSharcfb;
                Globals::sBigItemScale = bigItemScale;
                Globals::sUseRealZoom = useRealZoom;
                Globals::sPreserveUnitSize = preserveUnitSize;
                Globals::sApplyDistantViewScissor = applyDistantViewScissor;
                Globals::sScrollMovementSpeed = scrollMovementSpeed;
                Globals::sArrowMovementSpeed = arrowMovementSpeed;
                Globals::sFastArrowMovementSpeed = fastArrowMovementSpeed;

                mpCourseView->onApplyDistantViewScissorChange();
            }

            ImGui::SameLine();

            if (ImGui::Button("Discard"))
            {
                ImGui::CloseCurrentPopup();
                mPopupType = POPUP_TYPE_NONE;
            }

            ImGui::SetItemDefaultFocus();

            ImGui::EndPopup();
        }
        break;
    case POPUP_TYPE_ACTION_DISCARD:
        if (mPopupOpen)
        {
            ImGui::OpenPopup("Discard undo/redo stack?");
            mPopupOpen = false;
        }

        if (ImGui::BeginPopupModal("Discard undo/redo stack?", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("Completing this action discards your undo/redo stack.");
            ImGui::Text("Are you sure you want to proceed?");

            ImGui::Separator();

            if (ImGui::Button("Yes"))
            {
                ImGui::CloseCurrentPopup();
                mPopupType = POPUP_TYPE_NONE;
                handlePopupCallback_();
                mPopupCallbackType = POPUP_CALLBACK_TYPE_NONE;
            }

            ImGui::SameLine();

            if (ImGui::Button("No"))
            {
                ImGui::CloseCurrentPopup();
                mPopupType = POPUP_TYPE_NONE;
                mPopupCallbackType = POPUP_CALLBACK_TYPE_NONE;
            }

            ImGui::SetItemDefaultFocus();

            ImGui::EndPopup();
        }
        break;
    case POPUP_TYPE_SAVE:
        if (mPopupOpen)
        {
            ImGui::OpenPopup("Discard unsaved changes?");
            mPopupOpen = false;
        }

        if (ImGui::BeginPopupModal("Discard unsaved changes?", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("Completing this action discards all unsaved changes to your course.");
            ImGui::Text("Are you sure you want to proceed?");

            ImGui::Separator();

            if (ImGui::Button("Yes"))
            {
                ImGui::CloseCurrentPopup();
                mPopupType = POPUP_TYPE_NONE;
                handlePopupCallback_();
                mPopupCallbackType = POPUP_CALLBACK_TYPE_NONE;
            }

            ImGui::SameLine();

            if (ImGui::Button("No"))
            {
                ImGui::CloseCurrentPopup();
                mPopupType = POPUP_TYPE_NONE;
                mPopupCallbackType = POPUP_CALLBACK_TYPE_NONE;
            }

            ImGui::SetItemDefaultFocus();

            ImGui::EndPopup();
        }
        break;
    case POPUP_TYPE_SELECT:
        if (mPopupOpen)
        {
            ImGui::OpenPopup("Select All");
            mPopupOpen = false;
        }

        if (ImGui::BeginPopupModal("Select All", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("Choose object types you would like to select:");

            ImGui::Separator();

            ImGui::CheckboxFlags("Bg Unit Object",  &mItemSelectFlag, 1 << ITEM_TYPE_BG_UNIT_OBJ);
            ImGui::CheckboxFlags("Actor",           &mItemSelectFlag, 1 << ITEM_TYPE_MAP_ACTOR);
            ImGui::CheckboxFlags("NextGoto",        &mItemSelectFlag, 1 << ITEM_TYPE_NEXT_GOTO);
            ImGui::CheckboxFlags("Location",        &mItemSelectFlag, 1 << ITEM_TYPE_LOCATION);
            ImGui::CheckboxFlags("Area",            &mItemSelectFlag, 1 << ITEM_TYPE_AREA);

            ImGui::Separator();

            if (ImGui::Button("Select"))
            {
                ImGui::CloseCurrentPopup();
                mPopupType = POPUP_TYPE_NONE;
                handlePopupCallback_();
                mPopupCallbackType = POPUP_CALLBACK_TYPE_NONE;
            }

            ImGui::SameLine();

            if (ImGui::Button("Cancel"))
            {
                ImGui::CloseCurrentPopup();
                mPopupType = POPUP_TYPE_NONE;
                mPopupCallbackType = POPUP_CALLBACK_TYPE_NONE;
            }

            ImGui::SetItemDefaultFocus();

            ImGui::EndPopup();
        }
        break;
    }
}
