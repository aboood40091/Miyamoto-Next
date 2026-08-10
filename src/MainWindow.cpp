#include <ConfigMgr.h>
#include <CourseView.h>
#include <MainWindow.h>
#include <Preferences.h>
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
#include <graphics/GridRenderer.h>
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

#if RIO_IS_DESKTOP
#include <graphics/win/ShaderUtil.h>
#include <GLFW/glfw3.h>
#include <nfd.h>
#include <tracy/Tracy.hpp>
#include <tracy/TracyOpenGL.hpp>
#endif // RIO_IS_DESKTOP

#include <rio.h>

#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <format>

static constexpr f32 cDefaultZoomUnitSize = 32;

static constexpr f32 cUnitSize = 60;
static constexpr f32 cMinZoomUnitSize = cUnitSize / 4;
static constexpr f32 cMaxZoomUnitSize = cUnitSize * 2;
static constexpr f32 cZoomUnitSizeStep = cUnitSize / 4;

// Distance at which the smooth-zoom interpolation snaps to its target.
static constexpr f32 cZoomUnitSizeEpsilon = 0.01f;

// Display format shared by the zoom slider and the zoom readout.
#define ZOOM_FORMAT "%.2f"

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
    , mZoomUnitSize(cDefaultZoomUnitSize)
    , mTargetZoomUnitSize(cDefaultZoomUnitSize)
    , mContentLoadFailed(false)
{
}

#if RIO_IS_DESKTOP

void MainWindow::resize_(s32 width, s32 height)
{
    ImGuiUtil::setDisplaySize(width, height);
}

void MainWindow::onResizeCallback_(s32 width, s32 height)
{
    static_cast<MainWindow*>(rio::sRootTask)->resize_(width, height);
}

#endif // RIO_IS_DESKTOP

void MainWindow::failContentLoad_(const std::string& message)
{
    mContentLoadFailed = true;
    mContentLoadError = message;

    RIO_LOG("%s\n", message.c_str());

    // Clear all RenderObj stuff to avoid crashes caused by callbacks trying to access non-initialized resources.
    for (rio::lyr::Layer* p_layer_base : *rio::lyr::Renderer::instance())
    {
        RenderObjLayer* p_layer = dynamic_cast<RenderObjLayer*>(p_layer_base);
        if (p_layer == nullptr)
            continue;

        RenderMgr* p_render_mgr = p_layer->getRenderMgr();
        if (p_render_mgr != nullptr)
        {
            p_render_mgr->clear();
            p_render_mgr->clearView();
            p_render_mgr->setDrawCallback(nullptr);
        }
        p_layer->clearDrawMethodsAll();
        p_layer->clearRenderSteps();
    }
}

std::string MainWindow::buildContentPathError_(const std::string& what, const std::string& path) const
{
    return
        "Could not load " + what + ":\n\n    " + path + "\n\n"
        "Either file is corrupted, or the content path is probably wrong. It must point\n"
        "at a folder that contains a \"Common\" directory, i.e. the game's content root.\n\n"
        "Current content path:\n    " + Preferences::instance()->getContentPathRaw() + "\n\n"
        "Set \"ContentPath\" in preferences.ini (next to the executable), and restart.\n"
        "A relative path is resolved against fs/content; an absolute path\n"
        "such as C:\\Games\\NSMBU\\content also works as-is.";
}

bool MainWindow::loadRequiredArchive_(Sharc& out, const std::string& path, bool decompress)
{
    {
        rio::FileDevice::LoadArg arg;
        arg.path = path;
        arg.alignment = 0x2000;

        out.p_archive = decompress
            ? SZSDecompressor::tryDecomp(arg)
            : rio::FileDeviceMgr::instance()->load(arg);
    }

    if (out.p_archive == nullptr || !out.archive_res.prepareArchive(out.p_archive))
    {
        failContentLoad_(buildContentPathError_("a required game file", path));
        return false;
    }

    return true;
}

void MainWindow::drawContentLoadErrorUI_()
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetCenter(), ImGuiCond_Always, { 0.5f, 0.5f });

    ImGui::Begin(
        "Unable to start",
        nullptr,
        ImGuiWindowFlags_NoResize     | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse   | ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_AlwaysAutoResize
    );
    {
        ImGui::TextUnformatted(mContentLoadError.c_str());

        ImGui::Separator();

        if (ImGui::Button("Copy details"))
            ImGui::SetClipboardText(mContentLoadError.c_str());

        ImGui::SameLine();

#if RIO_IS_DESKTOP
        if (ImGui::Button("Quit"))
            rio::Window::instance()->requestClose();
#endif // RIO_IS_DESKTOP
    }
    ImGui::End();
}

void MainWindow::prepare_()
{
  //RIO_LOG("MainWindow::prepare_(): start\n");

#if RIO_IS_DESKTOP
    TracyGpuContext;

    rio::Window::instance()->setOnResizeCallback(&MainWindow::onResizeCallback_);
    NFD_Init();
#endif // RIO_IS_DESKTOP

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

    Preferences::createSingleton();
    
    ThemeMgr::createSingleton();
    ThemeMgr::instance()->initialize();
    
    rio::Window::instance()->setSwapInterval(!Preferences::instance()->getUnlockedFPS());

    ActionMgr::createSingleton();

    QuadRenderer::createSingleton();
    GridRenderer::createSingleton();

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

#if RIO_IS_DESKTOP
    ShaderUtil::sTempPath                   = rio::FileDeviceMgr::instance()->getNativeFileDevice()->getCWD() + "/fs/content/shaders/cache";
    ShaderUtil::sGx2ShaderDecompilerPath    = rio::FileDeviceMgr::instance()->getNativeFileDevice()->getCWD() + "/fs/content/gx2shader-decompiler.exe";
    ShaderUtil::sSpirvCrossPath             = rio::FileDeviceMgr::instance()->getNativeFileDevice()->getCWD() + "/fs/content/spirv-cross.exe";

  //RIO_LOG("MainWindow::prepare_(): ShaderUtil parameters set\n");
#endif // RIO_IS_DESKTOP

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
            Preferences::instance()->getContentPath() + "/CAFE/agl_resource_cafe.sarc";
#else
            "agl_resource_cafe_dev.sarc";
#endif
        arg.alignment = 0x2000;

        mAglRes.p_archive = rio::FileDeviceMgr::instance()->load(arg);
    }
    if (mAglRes.p_archive == nullptr)
    {
        failContentLoad_(
            "Failed to load the AGL shader archive.\n\n"
            "Expected it next to the executable at:\n"
            "    fs/content/agl_resource_cafe_dev.sarc\n\n"
            "This file ships with the editor. If it is missing, reinstall or\n"
            "re-download the editor's data files."
        );
        return;
    }

    mAglRes.archive_res.prepareArchive(mAglRes.p_archive);
  //RIO_LOG("MainWindow::prepare_(): mAglRes.archive_res.prepareArchive() done\n");

    agl::detail::ShaderHolder::instance()->initialize(&mAglRes.archive_res);

  //RIO_LOG("Initialized shader holder\n");

    agl::utl::VertexAttributeHolder::createSingleton();
    agl::utl::VertexAttributeHolder::instance()->initialize();

  //RIO_LOG("Initialized agl!\n");

    ShaderHolder::createSingleton();
    {
        const std::string shaderfb_path =
            Preferences::instance()->getContentPath() + "/Common/shader/shaderfb";

        if (!ShaderHolder::instance()->initialize(shaderfb_path))
        {
            failContentLoad_(
                buildContentPathError_("the game's shader archive", shaderfb_path + ".szs")
            );
            return;
        }
    }

  //RIO_LOG("Initialized ShaderHolder\n");

    ResMgr::createSingleton();

  //RIO_LOG("Created ResMgr\n");

    if (!loadRequiredArchive_(
            mJyotyuActorPack,
            Preferences::instance()->getContentPath() + "/Common/actor/jyotyuActorPack.szs",
            true))
        return;

    for (const SharcArchiveRes::Entry& entry : mJyotyuActorPack.archive_res.readEntry())
        ResMgr::instance()->loadArchiveRes(entry.name, mJyotyuActorPack.archive_res.getFileConst(entry.name), true);

  //RIO_LOG("Initialized jyotyuActorPack\n");

    if (!loadRequiredArchive_(
            mCobPack,
            Preferences::instance()->getContentPath() + "/Common/actor/cobPack.szs",
            true))
        return;

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

    mZoomUnitSize = Preferences::instance()->getZoomUnitSize();
    mTargetZoomUnitSize = mZoomUnitSize;

    mCourseViewSize.x = width;
    mCourseViewSize.y = height;

    mCourseViewPos.x = 0.0f;
    mCourseViewPos.y = 0.0f;

    CourseView::createSingleton(mCourseViewSize.x, mCourseViewSize.y, mCourseViewPos);
    mpCourseView = CourseView::instance();

  //RIO_LOG("Created CourseView\n");

    const std::string& startup_level = Preferences::instance()->getStartupLevel();

    bool loaded = false;
    if (!startup_level.empty())
    {
        const std::string& level_path = Preferences::instance()->getContentPath() + "/Common/course_res_pack/" + startup_level;

        loaded = CourseData::instance()->loadFromPack(level_path);
        if (loaded)
        {
            mCoursePath = level_path;
            RIO_LOG("mCoursePath set to: %s\n", mCoursePath.c_str());
        }
        else
        {
            RIO_LOG("Startup level could not be loaded: %s\n", level_path.c_str());
        }
    }

    if (!loaded)
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

    if (mJyotyuActorPack.p_archive != nullptr)
    {
        for (const SharcArchiveRes::Entry& entry : mJyotyuActorPack.archive_res.readEntry())
            ResMgr::instance()->destroyArchiveRes(entry.name);

        mJyotyuActorPack.archive_res.destroy();

        rio::MemUtil::free(mJyotyuActorPack.p_archive);
        mJyotyuActorPack.p_archive = nullptr;
    }

    if (mCobPack.p_archive != nullptr)
    {
        for (const SharcArchiveRes::Entry& entry : mCobPack.archive_res.readEntry())
            ResMgr::instance()->destroyArchiveRes(entry.name);

        mCobPack.archive_res.destroy();

        rio::MemUtil::free(mCobPack.p_archive);
        mCobPack.p_archive = nullptr;
    }

    ResMgr::destroySingleton();

    ShaderHolder::destroySingleton();

    agl::utl::VertexAttributeHolder::destroySingleton();

    agl::utl::PrimitiveTexture::destroySingleton();
  //agl::utl::PrimitiveVertex::destroySingleton();

    agl::utl::PrimitiveShape::destroySingleton();

    agl::detail::ShaderHolder::destroySingleton();

    if (mAglRes.p_archive != nullptr)
    {
        mAglRes.archive_res.destroy();

        rio::MemUtil::free(mAglRes.p_archive);
        mAglRes.p_archive = nullptr;
    }

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
    
    Preferences::destroySingleton();

    ImGuiUtil::shutdown();

#if RIO_IS_DESKTOP
    rio::Window::instance()->setOnResizeCallback(nullptr);
    NFD_Quit();
#endif // RIO_IS_DESKTOP
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

    mpCourseView->initialize(cd_file, false);
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
#if RIO_IS_DESKTOP
    nfdu8filteritem_t filters[3] = {
        { "Course pack (*.sarc *.szs)", "sarc,szs" },
        { "Compressed course pack (*.szs)", "szs" },
        { "Uncompressed course pack (*.sarc)", "sarc" }
    };
    
    nfdopendialogu8args_t args = {0};
    args.filterList = filters;
    args.filterCount = 3;
    
    nfdu8char_t* chosen_file;
    nfdresult_t result = NFD_OpenDialogU8_With(&chosen_file, &args);
    if (result == NFD_CANCEL)
        return;
    
    if (result != NFD_OKAY)
    {
        RIO_LOG("File selection error: %s", NFD_GetError());
        return;
    }
    
    RIO_LOG("Chose file: %s\n", chosen_file);
    std::string level_path = "native://";
    level_path += chosen_file;

    if (!CourseData::instance()->loadFromPack(level_path))
        return;

    mCoursePath = level_path;
    RIO_LOG("mCoursePath set to: %s\n", mCoursePath.c_str());
    ActionMgr::instance()->discard(false);
    setCurrentCourseDataFile_(0);
#endif // RIO_IS_DESKTOP
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
#if RIO_IS_DESKTOP
    nfdu8filteritem_t filters[3] = {
        { "Course pack (*.sarc *.szs)", "sarc,szs" },
        { "Compressed course pack (*.szs)", "szs" },
        { "Uncompressed course pack (*.sarc)", "sarc" }
    };
    
    nfdsavedialogu8args_t args = {0};
    args.filterList = filters;
    args.filterCount = 3;
    
    nfdu8char_t* chosen_file;
    nfdresult_t result = NFD_SaveDialogU8_With(&chosen_file, &args);
    if (result == NFD_CANCEL)
        return;
    
    if (result != NFD_OKAY)
    {
        RIO_LOG("File selection error: %s", NFD_GetError());
        return;
    }

    RIO_LOG("Save as file: %s\n", chosen_file);
    std::string level_path = "native://";
    level_path += chosen_file;

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
#endif // RIO_IS_DESKTOP
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
#if RIO_IS_DESKTOP
    if (glfwGetWindowAttrib(rio::Window::instance()->getNativeWindow().getGLFWwindow(), GLFW_ICONIFIED))
        return;
#endif // RIO_IS_DESKTOP

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
#if RIO_IS_DESKTOP
    if (glfwGetWindowAttrib(rio::Window::instance()->getNativeWindow().getGLFWwindow(), GLFW_ICONIFIED))
        return;
#endif // RIO_IS_DESKTOP

    if (!mCourseViewFocused || mCourseViewCameraMoved)
        return;

    mpCourseView->processKeyboardInput();
}

void MainWindow::calc_()
{
#if RIO_IS_DESKTOP
    FrameMark;
#endif // RIO_IS_DESKTOP

    ImGuiUtil::newFrame();

    if (mContentLoadFailed)
    {
        drawContentLoadErrorUI_();
        return;
    }

    BgTexMgr::instance()->update();
    CoinOrigin::instance()->update();

    drawCourseViewUI_();
    drawPaletteUI_();
    drawSelectionUI_();
    drawFileOptionsUI_();
    drawMainMenuBarUI_();
    drawStatusBar_();

    updateZoom_();

    if (mCourseViewResized)
    {
        mpCourseView->resize(mCourseViewSize.x, mCourseViewSize.y, false);
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
    if (mContentLoadFailed)
        return;

    mpCourseView->gather();

    CoinOrigin::instance()->draw(getBgPrepareLayer());
    mRenderMgrBgPrepare.calc();
}

void MainWindow::dispose_(const rio::lyr::DrawInfo&)
{
    if (!mContentLoadFailed)
    {
        mRenderMgrBgPrepare.clear();

        mpCourseView->dispose();
    }

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
#elif RIO_IS_DESKTOP
        texture_id = reinterpret_cast<void*>(mpCourseView->getColorTexture()->getNativeTextureHandle());
#endif

        ImGui::Image(texture_id, size);

        mpCourseView->drawItemLabels(rio::BaseVec2f{ pos.x, pos.y });

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
#if RIO_IS_DESKTOP
            ImGui::Image(reinterpret_cast<void*>(obj_tex->getNativeTextureHandle()), icon_size);
#endif // RIO_IS_DESKTOP
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

                if (!filter.PassFilter(str.c_str()))
                    continue;

                // Ids are user-editable and need not be unique, so the label alone is not a safe ImGui ID.
                ImGui::PushID(i);

                if (ImGui::Selectable(str.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick) && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                {
                    mpCourseView->setCameraCenterWorldPos({ f32(area_data.offset.x + 8), -f32(area_data.offset.y + 8) });
                    mpCourseView->selectItem(area_item.getItemID());
                }

                ImGui::PopID();
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

                if (!filter.PassFilter(str.c_str()))
                    continue;

                // Ids are user-editable and need not be unique, so the label alone is not a safe ImGui ID.
                ImGui::PushID(i);

                if (ImGui::Selectable(str.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick) && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                {
                    mpCourseView->setCameraCenterWorldPos({ f32(location_data.offset.x + 8), -f32(location_data.offset.y + 8) });
                    mpCourseView->selectItem(location_item.getItemID());
                }

                ImGui::PopID();
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

                if (!filter.PassFilter(str.c_str()))
                    continue;

                // Ids are user-editable and need not be unique, so the label alone is not a safe ImGui ID.
                ImGui::PushID(i);

                if (ImGui::Selectable(str.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick) && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                {
                    mpCourseView->setCameraCenterWorldPos({ f32(next_goto.offset.x + 8), -f32(next_goto.offset.y + 8) });
                    mpCourseView->selectItem(next_goto_item.getItemID());
                }

                ImGui::PopID();
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

                ActorCreateMgr* const actor_create_mgr = ActorCreateMgr::instance();

                static ImGuiTextFilter filter;
                filter.Draw("##ActorAddSearch", -1);

                bool hide_unused = Preferences::instance()->getActorHideUnused();
                if (ImGui::Checkbox("Hide unused", &hide_unused))
                    Preferences::instance()->setActorHideUnused(hide_unused);

                ImGui::SameLine();

                bool hide_nslu = Preferences::instance()->getActorHideNSLU();
                if (ImGui::Checkbox("Hide NSLU", &hide_nslu))
                    Preferences::instance()->setActorHideNSLU(hide_nslu);

                u32 hidden_flags = ActorCreateMgr::NAME_FLAG_NONE;
                if (hide_unused)
                    hidden_flags |= ActorCreateMgr::NAME_FLAG_UNUSED;
                if (hide_nslu)
                    hidden_flags |= ActorCreateMgr::NAME_FLAG_NSLU;

                const u32 type_max_num = actor_create_mgr->getTypeMaxNum();
                u32 shown_num = 0;

                // Reserve one line under the list for the count.
                if (ImGui::BeginListBox("##ActorAddList", ImVec2(-1, -ImGui::GetFrameHeightWithSpacing())))
                {
                    const ImVec4 dimmed_color = ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled);

                    for (u32 n = 0; n < type_max_num; n++)
                    {
                        const u32 flags = actor_create_mgr->getNameFlags(n);

                        // Selected type shall stay listed even when the flag filters would hide it, so the paint tool is never pointing at something the palette gives no sign of.
                        const bool is_selected = mMapActorSelectedType == n;
                        if ((flags & hidden_flags) != 0 && !is_selected)
                            continue;

                        if (!filter.PassFilter(actor_create_mgr->getSearchKey(n).c_str()))
                            continue;

                        shown_num++;

                        const bool dim = (flags & (ActorCreateMgr::NAME_FLAG_UNUSED | ActorCreateMgr::NAME_FLAG_CRASHES)) != 0;
                        if (dim)
                            ImGui::PushStyleColor(ImGuiCol_Text, dimmed_color);

                        if (ImGui::Selectable(actor_create_mgr->getLabel(n).c_str(), is_selected))
                            mMapActorSelectedType = n;

                        if (dim)
                            ImGui::PopStyleColor();
                    }
                    ImGui::EndListBox();
                }

                if (shown_num == type_max_num)
                    ImGui::TextDisabled("%u actors", type_max_num);
                else
                    ImGui::TextDisabled("%u of %u actors", shown_num, type_max_num);

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
                    ActorCreateMgr* const actor_create_mgr = ActorCreateMgr::instance();

                    const std::vector< std::unique_ptr<MapActorItem> >& item_vec = mpCourseView->getMapActorItem();
                    const std::vector<MapActorData>& data_vec = mpCourseView->getCourseDataFile().getMapActorData();
                    for (u32 i = 0; i < item_vec.size(); i++)
                    {
                        const MapActorItem& map_actor_item = *(item_vec[i]);
                        const MapActorData& map_actor_data = data_vec[i];

                        const std::string& position = std::format(" ({0:d}, {1:d})", map_actor_data.offset.x, map_actor_data.offset.y);

                        // Filter on both names; show only the selected one.
                        const std::string& key = actor_create_mgr->getSearchKey(map_actor_data.type) + position;
                        const std::string& str = actor_create_mgr->getLabel(map_actor_data.type) + position;

                        if (!filter.PassFilter(key.c_str()))
                            continue;

                        // Two actors of the same type may sit at the same offset, which would otherwise give them the same ImGui ID.
                        ImGui::PushID(i);

                        if (ImGui::Selectable(str.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick) && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                        {
                            mpCourseView->setCameraCenterWorldPos({ f32(map_actor_data.offset.x + 8), -f32(map_actor_data.offset.y + 8) });
                            mpCourseView->selectItem(map_actor_item.getItemID());
                        }

                        ImGui::PopID();
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

            ImGui::Separator();

            if (ImGui::MenuItem("Exit"))
                rio::Window::instance()->requestClose();

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            {
                ActionMgr* const action_mgr = ActionMgr::instance();

                const std::string& undo_description = action_mgr->getUndoDescription();
                const std::string& redo_description = action_mgr->getRedoDescription();

                const std::string& undo_label =
                    undo_description.empty()
                        ? std::string("Undo")
                        : std::format("Undo {0:s}", undo_description);

                const std::string& redo_label =
                    redo_description.empty()
                        ? std::string("Redo")
                        : std::format("Redo {0:s}", redo_description);

                if (ImGui::MenuItem(undo_label.c_str(), "Ctrl+Z", false, action_mgr->canUndo()))
                    mpCourseView->undo();

                if (ImGui::MenuItem(redo_label.c_str(), "Ctrl+Shift+Z / Ctrl+Y", false, action_mgr->canRedo()))
                    mpCourseView->redo();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Select All...", "Ctrl+A"))
                courseItemSelect();

            if (ImGui::MenuItem("Deselect", "Esc", false, mpCourseView->hasSelection()))
                mpCourseView->clearSelection();

            if (ImGui::MenuItem("Delete", "Delete / Backspace", false, mpCourseView->hasSelection()))
                mpCourseView->deleteSelection();

            if (ImGui::MenuItem("Copy", "Ctrl+C", false, mpCourseView->hasSelection()))
                mpCourseView->copySelection();

            if (ImGui::MenuItem("Cut", "Ctrl+X", false, mpCourseView->hasSelection()))
                mpCourseView->cutSelection();

            if (ImGui::MenuItem("Paste", "Ctrl+V", false, mpCourseView->hasClipboard()))
                mpCourseView->pasteClipboard();

            if (ImGui::MenuItem("Duplicate", "Ctrl+D", false, mpCourseView->hasSelection()))
                mpCourseView->duplicateSelection();

            ImGui::Separator();

            if (ImGui::BeginMenu("Set to Layer"))
            {
                for (u8 layer_index = 0; layer_index < CD_FILE_LAYER_MAX_NUM; layer_index++)
                {
                    const std::string& label = std::format("Layer {0:d}", layer_index);

                    u8 layer = GetLayerFromIndex(layer_index);
                    RIO_ASSERT(layer < CD_FILE_LAYER_MAX_NUM);

                    if (ImGui::MenuItem(label.c_str(), nullptr, false, mpCourseView->canSetSelectionToLayer(layer)))
                        mpCourseView->setSelectionToLayer(layer);
                }

                ImGui::EndMenu();
            }

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

            ImGui::Separator();

            if (ImGui::BeginMenu("Grid"))
            {
                static const char* const cGridTypeNames[GRID_TYPE_MAX_NUM] = {
                    "Off",
                    "Lines",
                    "Checkerboard"
                };

                const GridType current = mpCourseView->getGridType();

                for (s32 i = 0; i < GRID_TYPE_MAX_NUM; i++)
                {
                    const bool is_next = GridType(i) == GridType((current + 1) % GRID_TYPE_MAX_NUM);

                    if (ImGui::MenuItem(cGridTypeNames[i], is_next ? "Ctrl+G" : nullptr, GridType(i) == current))
                        setGridType(GridType(i));
                }

                ImGui::EndMenu();
            }

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
        static std::string contentPath;
        static bool forceSharcfb;
        static float bigItemScale;
        static bool applyDistantViewScissor;
        static float scrollMovementSpeed;
        static float arrowMovementSpeed;
        static float fastArrowMovementSpeed;
        static bool smoothZoom;
        static bool unlockedFPS;
        static ActorNameLanguage actorNameLanguage;
        static s32 maxUndoHistory;

        if (mPopupOpen)
        {
            ImGui::OpenPopup("Settings");
            contentPath = Preferences::instance()->getContentPathRaw();
            forceSharcfb = Preferences::instance()->getForceSharcfb();
            bigItemScale = Preferences::instance()->getBigItemScale();
            applyDistantViewScissor = Preferences::instance()->getApplyDistantViewScissor();
            scrollMovementSpeed = Preferences::instance()->getScrollMovementSpeed();
            arrowMovementSpeed = Preferences::instance()->getArrowMovementSpeed();
            fastArrowMovementSpeed = Preferences::instance()->getFastArrowMovementSpeed();
            smoothZoom = Preferences::instance()->getSmoothZoom();
            unlockedFPS = Preferences::instance()->getUnlockedFPS();
            actorNameLanguage = Preferences::instance()->getActorNameLanguage();
            maxUndoHistory = s32(Preferences::instance()->getMaxUndoHistory());
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
                    const std::string& theme_name = theme_names[i];

                    if (ImGui::Selectable(theme_name.c_str(), selected))
                    {
                        ThemeMgr::instance()->applyTheme(theme_name);
                    }

                    if (selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            static const char* const cActorNameLanguageNames[ACTOR_NAME_LANGUAGE_MAX_NUM] = {
                "English",
                "Japanese",
                "English (Japanese)"
            };

            if (ImGui::BeginCombo("Actor Names", cActorNameLanguageNames[actorNameLanguage]))
            {
                for (s32 i = 0; i < ACTOR_NAME_LANGUAGE_MAX_NUM; i++)
                {
                    const bool selected = i == actorNameLanguage;

                    if (ImGui::Selectable(cActorNameLanguageNames[i], selected))
                        actorNameLanguage = ActorNameLanguage(i);

                    if (selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            ImGui::InputText("Content Path", &contentPath);
            ImGui::Checkbox("Decompile Shaders", &forceSharcfb);
            ImGui::InputFloat("Big Item Scale", &bigItemScale);
            ImGui::Checkbox("Clip DistantView To Area", &applyDistantViewScissor);
            ImGui::InputFloat("Scroll Movement Speed", &scrollMovementSpeed);
            ImGui::InputFloat("Arrow Movement Speed", &arrowMovementSpeed);
            ImGui::InputFloat("Fast Arrow Movement Speed", &fastArrowMovementSpeed);

            if (ImGui::InputInt("Undo History", &maxUndoHistory))
                maxUndoHistory = std::clamp<s32>(maxUndoHistory, 0, ActionMgr::cMaxUserMaxHistory);
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Maximum number of undo steps kept.\n0 means unlimited.");

            ImGui::Checkbox("Smooth Zoom", &smoothZoom);
            ImGui::Checkbox("Unlocked FPS", &unlockedFPS);

            ImGui::Separator();

            if (ImGui::Button("Apply"))
            {
                ImGui::CloseCurrentPopup();
                mPopupType = POPUP_TYPE_NONE;

                Preferences::instance()->setContentPath(contentPath);
                Preferences::instance()->setForceSharcfb(forceSharcfb);
                Preferences::instance()->setBigItemScale(bigItemScale);
                Preferences::instance()->setApplyDistantViewScissor(applyDistantViewScissor);
                Preferences::instance()->setScrollMovementSpeed(scrollMovementSpeed);
                Preferences::instance()->setArrowMovementSpeed(arrowMovementSpeed);
                Preferences::instance()->setFastArrowMovementSpeed(fastArrowMovementSpeed);
                Preferences::instance()->setSmoothZoom(smoothZoom);
                Preferences::instance()->setUnlockedFPS(unlockedFPS);
                Preferences::instance()->setActorNameLanguage(actorNameLanguage);
                Preferences::instance()->setMaxUndoHistory(u32(maxUndoHistory));

                ActorCreateMgr::instance()->setNameLanguage(actorNameLanguage);

                ActionMgr::instance()->setMaxHistory(u32(maxUndoHistory));

                mpCourseView->onApplyDistantViewScissorChange();
                rio::Window::instance()->setSwapInterval(!unlockedFPS);
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

            ImGui::CheckboxFlags(ITEM_NAME_BG_UNIT_OBJ, &mItemSelectFlag, 1 << ITEM_TYPE_BG_UNIT_OBJ);
            ImGui::CheckboxFlags(ITEM_NAME_MAP_ACTOR,   &mItemSelectFlag, 1 << ITEM_TYPE_MAP_ACTOR);
            ImGui::CheckboxFlags(ITEM_NAME_NEXT_GOTO,   &mItemSelectFlag, 1 << ITEM_TYPE_NEXT_GOTO);
            ImGui::CheckboxFlags(ITEM_NAME_LOCATION,    &mItemSelectFlag, 1 << ITEM_TYPE_LOCATION);
            ImGui::CheckboxFlags(ITEM_NAME_AREA,        &mItemSelectFlag, 1 << ITEM_TYPE_AREA);

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

void MainWindow::drawStatusBar_()
{
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    if (ImGui::BeginViewportSideBar(
        "##MainStatusBar", viewport, ImGuiDir_Down, ImGui::GetFrameHeight(),
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar
    ))
    {
        if (ImGui::BeginMenuBar())
        {
            drawStatusBarFileInfo_();
            drawStatusBarControls_();

            ImGui::EndMenuBar();
        }
    }
    ImGui::End();
}

void MainWindow::drawStatusBarFileInfo_()
{
    if (mCoursePath.empty())
    {
        ImGui::TextDisabled("New Course");
    }
    else
    {
        ImGui::Text("%s", mCoursePath.c_str());
    }
    
    ImGui::Separator();
    
    ImGui::Text("%zu actors", mpCourseView->getMapActorItem().size());
}

void MainWindow::drawStatusBarControls_()
{
    const f32 width = 480.0f; 
    f32 cursorX = ImGui::GetWindowWidth() - width;
    
    if (cursorX > ImGui::GetCursorPos().x)
    {
        ImGui::SetCursorPosX(cursorX);
    }
    
    // Zoom controls
    {
        if (ImGui::Button("Default Zoom"))
            applyZoomUnitSize(cDefaultZoomUnitSize);

        if (ImGui::Button("Real Zoom"))
        {
            f32 real_zoom_unit_size;
            if (mpCourseView && mpCourseView->getRealZoomUnitSize(real_zoom_unit_size))
                applyZoomUnitSize(real_zoom_unit_size, true);
        }

        {
            ImGuiIO& io = ImGui::GetIO();
            {
                // Ctrl + mouse wheel is handled in CourseView::processCursorInput_()

                if (ImGui::Button("-") || (io.KeyCtrl && (ImGui::IsKeyPressed(ImGuiKey_Minus) || ImGui::IsKeyPressed(ImGuiKey_KeypadSubtract))))
                    applyZoomUnitSize(mTargetZoomUnitSize - cZoomUnitSizeStep);

                ImGui::PushItemWidth(120);
                f32 zoom_unit_size = mTargetZoomUnitSize;
                if (ImGui::SliderFloat("##ZoomSlider", &zoom_unit_size, cMinZoomUnitSize, cMaxZoomUnitSize, ZOOM_FORMAT))
                    applyZoomUnitSize(zoom_unit_size);
                ImGui::PopItemWidth();

                if (ImGui::Button("+") || (io.KeyCtrl && (ImGui::IsKeyPressed(ImGuiKey_Equal) || ImGui::IsKeyPressed(ImGuiKey_KeypadAdd))))
                    applyZoomUnitSize(mTargetZoomUnitSize + cZoomUnitSizeStep);
            }
        }

        ImGui::Text("Zoom " ZOOM_FORMAT "%%", (mTargetZoomUnitSize * 100) / cUnitSize);
    }
}

void MainWindow::applyZoomUnitSize(f32 zoom_unit_size, bool bypass_limits)
{
    if (!bypass_limits)
        zoom_unit_size = std::clamp(zoom_unit_size, cMinZoomUnitSize, cMaxZoomUnitSize);

    if (zoom_unit_size == mTargetZoomUnitSize)
        return;

    mTargetZoomUnitSize = zoom_unit_size;
    Preferences::instance()->setZoomUnitSize(mTargetZoomUnitSize);

    if (!Preferences::instance()->getSmoothZoom())
    {
        mZoomUnitSize = mTargetZoomUnitSize;
        if (mpCourseView)
            mpCourseView->setZoomUnitSizeCentered(mZoomUnitSize);
    }
}

void MainWindow::applyZoomStep(bool zoom_in)
{
    const s32 direction = zoom_in ? -1 : 1;
    applyZoomUnitSize(mTargetZoomUnitSize + direction * cZoomUnitSizeStep);
}

void MainWindow::updateZoom_()
{
    if (mZoomUnitSize == mTargetZoomUnitSize)
        return;

    const f32 t = std::clamp(15.0f * ImGui::GetIO().DeltaTime, 0.0f, 1.0f);

    mZoomUnitSize = std::lerp(mZoomUnitSize, mTargetZoomUnitSize, t);

    // Snap once the remaining delta is imperceptible, so the lerp terminates
    // instead of asymptotically approaching the target forever.
    if (std::abs(mTargetZoomUnitSize - mZoomUnitSize) < cZoomUnitSizeEpsilon)
        mZoomUnitSize = mTargetZoomUnitSize;

    if (mpCourseView)
        mpCourseView->setZoomUnitSizeCentered(mZoomUnitSize);
}

void MainWindow::setGridType(GridType type)
{
    mpCourseView->setGridType(type);
    Preferences::instance()->setGridType(type);
}

void MainWindow::cycleGridType()
{
    setGridType(GridType((mpCourseView->getGridType() + 1) % GRID_TYPE_MAX_NUM));
}
