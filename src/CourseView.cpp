#include <CourseView.h>
#include <MainWindow.h>
#include <actor/ActorCreateMgr.h>
#include <course/Bg.h>
#include <course/BgRenderer.h>
#include <distant_view/DistantViewMgr.h>
#include <graphics/LayerID.h>
#include <graphics/Renderer.h>
#include <item/AreaItem.h>
#include <item/LocationItem.h>
#include <item/MapActorItem.h>
#include <item/NextGotoItem.h>

#include <container/SafeArray.h>
#include <controller/rio_ControllerMgr.h>
#include <gfx/rio_PrimitiveRenderer.h>
#include <gfx/rio_Window.h>
#include <gfx/lyr/rio_Renderer.h>
#include <gpu/rio_RenderState.h>
#include <gpu/rio_RenderStateMRT.h>

#if RIO_IS_CAFE
#include <gx2/event.h>
#endif // RIO_IS_CAFE

#include <imgui.h>

#include <unordered_set>

CourseView::CourseView(s32 width, s32 height, const rio::BaseVec2f& window_pos)
    : mDrawCallback3D(*this)
    , mDrawCallbackDV(*this)
    , mpLayer3D(nullptr)
    , mpLayerDV(nullptr)
    , mpDVControlArea(nullptr)
    , mIsCursorPress(false)
    , mIsCursorRelease(false)
    , mSelectionBox(false)
    , mSelectionChange(false)
    , mpItemIDReadBuffer(nullptr)
#if RIO_IS_WIN
    , mpItemIDClearBuffer(nullptr)
#endif // RIO_IS_WIN
    , mpColorTexture(nullptr)
    , mpItemIDTexture(nullptr)
    , mpDepthTexture(nullptr)
{
    mLayerItrDV = rio::lyr::Renderer::instance()->addLayer<RenderObjLayer>("DistantView", LAYER_ID_DISTANT_VIEW);
    mpLayerDV = rio::lyr::Layer::peelIterator(mLayerItrDV);
    getDistantViewLayer()->initialize();
    getDistantViewLayer()->addDrawMethod(RenderObjLayer::cRenderStep_PostFx, rio::lyr::DrawMethod(this, &CourseView::dv_PostFx_));
    getDistantViewLayer()->setRenderMgr(&mRenderMgrDV);
    mRenderMgrDV.setDrawCallback(&mDrawCallbackDV);

    mLayerItr3D = rio::lyr::Renderer::instance()->addLayer<RenderObjLayer>("3D", LAYER_ID_3D);
    mpLayer3D = rio::lyr::Layer::peelIterator(mLayerItr3D);
    get3DLayer()->initialize();
    get3DLayer()->setCamera(&mCamera);
    get3DLayer()->setProjection(&mProjection);
    get3DLayer()->setRenderMgr(&mRenderMgr3D);
    mRenderMgr3D.setDrawCallback(&mDrawCallback3D);

    mSize.x = width;
    mSize.y = height;
    mAspect = mSize.x / mSize.y;

    mProjection.set(
         1.0f,      // Near
         20000.0f,  // Far
         0.0f,      // Top
        -mSize.y,   // Bottom
         0.0f,      // Left
         mSize.x    // Right
    );

    setZoomTileSize(24);
    mRealBgZoom = mBgZoom;

    mRenderBuffer.setRenderTargetColor(&mColorTarget, TARGET_TYPE_COLOR);
    mRenderBufferDV.setRenderTargetColor(&mColorTargetDV);
    mRenderBuffer.setRenderTargetDepth(&mDepthTarget);
    mRenderBufferDV.setRenderTargetDepth(&mDepthTargetDV);

    createRenderBuffer_(width, height);

    DistantViewMgr::createSingleton(mRenderBufferDV);
    DistantViewMgr::instance()->setFlickerEnable(false);

    BgRenderer::createSingleton();
    BgRenderer::instance()->setCamera(&mCamera);
    BgRenderer::instance()->setProjection(&mProjection);

    mDrawDV = true;
    mLayerShown[LAYER_0] = true;
    mLayerShown[LAYER_1] = true;
    mLayerShown[LAYER_2] = true;

    updateCursorPos(window_pos);

    ActorCreateMgr::createSingleton();
}

CourseView::~CourseView()
{
    mSelectedItems.clear(); mSelectionChange = true;
    mMapActorItemPtr.clear();
    mNextGotoItem.clear();
    mLocationItem.clear();
    mAreaItem.clear();

    ActorCreateMgr::destroySingleton();
    BgRenderer::destroySingleton();
    DistantViewMgr::destroySingleton();

    if (mpColorTexture)
    {
        delete mpColorTexture;
        mpColorTexture = nullptr;
    }

    if (mpItemIDTexture)
    {
        delete mpItemIDTexture;
        mpItemIDTexture = nullptr;
    }

    if (mpItemIDReadBuffer)
    {
        delete[] mpItemIDReadBuffer;
        mpItemIDReadBuffer = nullptr;
    }

#if RIO_IS_WIN
    if (mpItemIDClearBuffer)
    {
        delete[] mpItemIDClearBuffer;
        mpItemIDClearBuffer = nullptr;
    }
#endif // RIO_IS_WIN

    if (mpDepthTexture)
    {
        delete mpDepthTexture;
        mpDepthTexture = nullptr;
    }

    if (mpLayer3D != nullptr)
    {
        rio::lyr::Renderer::instance()->removeLayer(mLayerItr3D);
        mpLayer3D = nullptr;
    }

    if (mpLayerDV != nullptr)
    {
        rio::lyr::Renderer::instance()->removeLayer(mLayerItrDV);
        mpLayerDV = nullptr;
    }
}

void CourseView::resize(s32 width, s32 height, bool preserve_tile_size)
{
#if RIO_IS_CAFE
    GX2DrawDone();
#elif RIO_IS_WIN
    RIO_GL_CALL(glFinish());
#endif

    const f32 screen_world_h_half_prev = /* mSize.x / (2 * mCamera.getZoomScale()) */ (224 / 2) * mBgZoom;
    const f32 screen_world_w_half_prev = /* mSize.y / (2 * mCamera.getZoomScale()) */ screen_world_h_half_prev * mAspect;

    const rio::Vector2f center_pos {
        mCamera.pos().x + screen_world_w_half_prev,
        mCamera.pos().y - screen_world_h_half_prev
    };

    mSize.x = width;
    mSize.y = height;
    mAspect = mSize.x / mSize.y;

    mProjection.setTBLR(
         0.0f,      // Top
        -mSize.y,   // Bottom
         0.0f,      // Left
         mSize.x     // Right
    );

    if (preserve_tile_size)
        setZoomTileSize(getZoomTileSize());
    else
        setZoom(mBgZoom);

    const f32 screen_world_h_half_now = /* mSize.x / (2 * mCamera.getZoomScale()) */ (224 / 2) * mBgZoom;
    const f32 screen_world_w_half_now = /* mSize.y / (2 * mCamera.getZoomScale()) */ screen_world_h_half_now * mAspect;

    mCamera.pos().x = center_pos.x - screen_world_w_half_now;
    mCamera.pos().y = center_pos.y + screen_world_h_half_now;

    createRenderBuffer_(width, height);

    DistantViewMgr::instance()->onResizeRenderBuffer();
}

void CourseView::createRenderBuffer_(s32 width, s32 height)
{
    if (mpColorTexture)
    {
        delete mpColorTexture;
        mpColorTexture = nullptr;
    }

    if (mpItemIDTexture)
    {
        delete mpItemIDTexture;
        mpItemIDTexture = nullptr;
    }

    if (mpItemIDReadBuffer)
    {
        delete[] mpItemIDReadBuffer;
        mpItemIDReadBuffer = nullptr;
    }

#if RIO_IS_WIN
    if (mpItemIDClearBuffer)
    {
        delete[] mpItemIDClearBuffer;
        mpItemIDClearBuffer = nullptr;
    }
#endif // RIO_IS_WIN

    if (mpDepthTexture)
    {
        delete mpDepthTexture;
        mpDepthTexture = nullptr;
    }

    mpColorTexture = new rio::Texture2D(rio::TEXTURE_FORMAT_R8_G8_B8_A8_UNORM, width, height, 1);
    mpItemIDTexture = new rio::Texture2D(rio::TEXTURE_FORMAT_R32_UINT, width, height, 1);
    mpDepthTexture = new rio::Texture2D(rio::DEPTH_TEXTURE_FORMAT_R32_FLOAT, width, height, 1);

    {
        u32 size = width * height * sizeof(u32);
        mpItemIDReadBuffer = new u8[size];
        rio::MemUtil::set(mpItemIDReadBuffer, 0xFF, size);
#if RIO_IS_WIN
        RIO_ASSERT(size == mpItemIDTexture->getNativeTexture().surface.imageSize);
        mpItemIDClearBuffer = new u8[size];
        rio::MemUtil::set(mpItemIDClearBuffer, 0xFF, size);
#endif // RIO_IS_WIN
    }

    agl::TextureData color_texture_data(*mpColorTexture, true, false);
    agl::TextureData depth_texture_data(*mpDepthTexture, false, true);

    mRenderBuffer.setSize(width, height);
    mRenderBufferDV.setSize(width, height);

    mColorTarget.linkTexture2D(*mpColorTexture);
    mColorTargetDV.applyTextureData(color_texture_data);

    mDepthTarget.linkTexture2D(*mpDepthTexture);
    mDepthTargetDV.applyTextureData(depth_texture_data);

    mItemIDTarget.linkTexture2D(*mpItemIDTexture);

    mRenderBuffer.clear(rio::RenderBuffer::CLEAR_FLAG_DEPTH);
}

void CourseView::bindRenderBuffer_(bool with_item_id)
{
    if (with_item_id)
        mRenderBuffer.setRenderTargetColor(&mItemIDTarget, TARGET_TYPE_ITEM_ID);
    else
        mRenderBuffer.setRenderTargetColorNull(TARGET_TYPE_ITEM_ID);

    mRenderBuffer.bind();
}

void CourseView::unbindRenderBuffer_()
{
    mRenderBuffer.getRenderTargetColor()->invalidateGPUCache();
    mpColorTexture->setCompMap(0x00010205);

    rio::Window::instance()->makeContextCurrent();

    u32 width = rio::Window::instance()->getWidth();
    u32 height = rio::Window::instance()->getHeight();

    rio::Graphics::setViewport(0, 0, width, height);
    rio::Graphics::setScissor(0, 0, width, height);
}

void CourseView::clearItemIDTexture_()
{
#if RIO_IS_CAFE
    const GX2Surface& surface = mpItemIDTexture->getNativeTexture().surface;
    rio::MemUtil::set(surface.image, 0xFF, surface.imageSize);
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_TEXTURE, surface.image, surface.imageSize);
#elif RIO_IS_WIN
    rio::Texture2DUtil::uploadTexture(
        mpItemIDTexture->getNativeTextureHandle(),
        mpItemIDTexture->getNativeTexture().surface.format,
        mpItemIDTexture->getNativeTexture().surface.nativeFormat,
        mpItemIDTexture->getNativeTexture().surface.width,
        mpItemIDTexture->getNativeTexture().surface.height,
        mpItemIDTexture->getNativeTexture().surface.imageSize,
        mpItemIDClearBuffer
    );
#endif // RIO_IS_WIN
}

rio::BaseVec2f CourseView::viewToWorldPos(const rio::BaseVec2f& pos) const
{
    const rio::Vector2f& pos_view = static_cast<const rio::Vector2f&>(pos);
    const rio::Vector2f& camera_pos = static_cast<const rio::Vector2f&>(mCamera.pos());

    const f32 screen_world_h = 224 * mBgZoom;
    const f32 screen_world_w = screen_world_h * mAspect;

    return pos_view * (rio::Vector2f{ screen_world_w, -screen_world_h } / mSize) + camera_pos;
}

rio::BaseVec2f CourseView::worldToViewPos(const rio::BaseVec2f& pos) const
{
    const rio::Vector2f& pos_world = static_cast<const rio::Vector2f&>(pos);
    const rio::Vector2f& camera_pos = static_cast<const rio::Vector2f&>(mCamera.pos());

    const f32 screen_world_h = 224 * mBgZoom;
    const f32 screen_world_w = screen_world_h * mAspect;

    return (pos_world - camera_pos) * (mSize / rio::Vector2f{ screen_world_w, -screen_world_h });
}

void CourseView::updateCursorPos(const rio::BaseVec2f& window_pos)
{
    const ImVec2& cursor_pos = ImGui::GetMousePos();
    if (!ImGui::IsMousePosValid(&cursor_pos))
        return;

    mCursorPos = reinterpret_cast<const rio::Vector2f&>(cursor_pos.x)
                - static_cast<const rio::Vector2f&>(window_pos);

    const f32 min_x = 0.0f;
    const f32 max_x = mSize.x;

    const f32 min_y = 0.0f;
    const f32 max_y = mSize.y;

    if (mCursorPos.x < min_x)
        mCursorPos.x = min_x;
    else if (mCursorPos.x > max_x)
        mCursorPos.x = max_x;

    if (mCursorPos.y < min_y)
        mCursorPos.y = min_y;
    else if (mCursorPos.y > max_y)
        mCursorPos.y = max_y;
}

namespace {

static f32 GetZoomMult(u32 zoom_type, u8 zoom_id)
{
    static const SafeArray<f32, 12> FLOAT_ARRAY_1022ced0 = {
        1.0000000f,
        1.0000000f,
        1.0000000f,
        1.4285715f,
        1.3571428f,
        1.2142857f,
        1.2142857f,
        1.2142857f,
        0.5000000f,
        1.2142857f,
        1.2142857f,
        1.4285715f
    };

    static const SafeArray<f32, 9> FLOAT_ARRAY_1022d020 = {
        1.0f,
        1.0f,
        1.0f,
        1.3571428f,
        1.3571428f,
        1.3571428f,
        1.2142857f,
        1.2142857f,
        1.2142857f
    };

    static const SafeArray<f32, 10> FLOAT_ARRAY_1022cea8 = {
        1.0000000f,
        1.3571428f,
        1.7142857f,
        2.0000000f,
        1.2142857f,
        1.4285715f,
        1.1428572f,
        2.0000000f,
        0.5000000f,
        0.7500000f
    };

    switch (zoom_type)
    {
    case 0:
    case 1:
    case 6:
    case 7:
        return FLOAT_ARRAY_1022ced0[zoom_id];
    case 2:
        return FLOAT_ARRAY_1022d020[zoom_id];
    case 3:
    case 4:
    case 5:
    default:
        return FLOAT_ARRAY_1022cea8[zoom_id];
    }
}

}

void CourseView::initialize(CourseDataFile* p_cd_file, bool real_zoom)
{
#if RIO_IS_CAFE
    GX2DrawDone();
#elif RIO_IS_WIN
    RIO_GL_CALL(glFinish());
#endif

    // Clear items
    mSelectedItems.clear(); mSelectionChange = true;
    mMapActorItemPtr.clear();
    mNextGotoItem.clear();
    mLocationItem.clear();
    mAreaItem.clear();

    mpCourseDataFile = p_cd_file;
    mpDVControlArea = nullptr;

    mSelectionBox = false;

    setZoomTileSize(24);
    mRealBgZoom = mBgZoom;

    if (mpCourseDataFile == nullptr)
    {
        // Clear BG
        Bg::instance()->clearBgCourseData();
        BgRenderer::instance()->createVertexBuffer();

        // Load default distant view
        const char* dv_name = "Nohara";
        const std::string& dv_path = MainWindow::getContentPath() + "/Common/distant_view";
        RIO_LOG("DV Path: \"%s\", DV Name: \"%s\"\n", dv_path.c_str(), dv_name);
        DistantViewMgr::instance()->initialize(dv_name, dv_path, MainWindow::forceSharcfb());

        return;
    }

    Bg::instance()->processBgCourseData(*mpCourseDataFile);
    BgRenderer::instance()->createVertexBuffer();

    {
        std::vector<MapActorData>& map_actors = mpCourseDataFile->getMapActorData();
        size_t map_actor_num = map_actors.size();
        for (u32 i = 0; i < map_actor_num; i++)
            mMapActorItemPtr.emplace_back(ActorCreateMgr::instance()->create(map_actors[i], i));
    }

    for (NextGoto& next_goto : mpCourseDataFile->getNextGoto())
        mNextGotoItem.emplace_back(next_goto);

    for (Location& location : mpCourseDataFile->getLocation())
        mLocationItem.emplace_back(location);

    for (AreaData& area : mpCourseDataFile->getAreaData())
        mAreaItem.emplace_back(area);

    const NextGoto* start_next_goto = nullptr;
  //if (!start_next_goto)
    {
        u8 start = mpCourseDataFile->getOptions().start_next_goto;
        for (const NextGoto& next_goto : mpCourseDataFile->getNextGoto())
        {
            if (next_goto.id == start)
            {
                start_next_goto = &next_goto;
                break;
            }
        }
    }

    if (!start_next_goto)
    {
        u8 start = mpCourseDataFile->getOptions().start_next_goto_coin_boost;
        for (const NextGoto& next_goto : mpCourseDataFile->getNextGoto())
        {
            if (next_goto.id == start)
            {
                start_next_goto = &next_goto;
                break;
            }
        }
    }

    rio::BaseVec2f& camera_pos = mCamera.pos();

    const char* dv_name = nullptr;

    u8 area;

    if (mpCourseDataFile->getAreaData().size() > 0)
    {
        if (start_next_goto)
        {
          //RIO_ASSERT(start_next_goto->area >= 0 && start_next_goto->area < mpCourseDataFile->getAreaData().size());
            area =
                (start_next_goto->area >= 0 && start_next_goto->area < mpCourseDataFile->getAreaData().size())
                    ? start_next_goto->area
                    : 0;
        }
        else
        {
            area = 0;
        }

        const AreaData& area_data = mpCourseDataFile->getAreaData()[area];

      //RIO_ASSERT(area_data.bg2 >= 0 && area_data.bg2 < mpCourseDataFile->getDistantViewData().size());
        if (area_data.bg2 >= 0 && area_data.bg2 < mpCourseDataFile->getDistantViewData().size())
        {
            const DistantViewData& dv_data = mpCourseDataFile->getDistantViewData()[area_data.bg2];
            dv_name = dv_data.name;
            mpDVControlArea = &area_data;

            const f32 w = s32(area_data.size.x);
            const f32 h = s32(area_data.size.y);

            mRealBgZoom =
                std::min<f32>(
                    std::min<f32>(
                        std::min<f32>(
                            w / 398.22222222222222f,
                            h / 224.0f
                        ),
                        2.0f
                    ),
                    GetZoomMult(area_data.zoom_type, area_data.zoom_id)
                );

            if (real_zoom)
                setZoom(mRealBgZoom);
        }
        else
        {
            dv_name = "Nohara";
        }
    }
    else
    {
        dv_name = "Nohara";
    }

    if (start_next_goto)
    {
        camera_pos.x =   f32(start_next_goto->offset.x + 8 + start_next_goto->camera_offset.x) ;
        camera_pos.y = -(f32(start_next_goto->offset.y + 8 + start_next_goto->camera_offset.y));
    }
    else
    {
        camera_pos.x = 0.0f;
        camera_pos.y = 0.0f;
    }

    RIO_ASSERT(dv_name != nullptr);

    const std::string& dv_path = MainWindow::getContentPath() + "/Common/distant_view";
    RIO_LOG("DV Path: \"%s\", DV Name: \"%s\"\n", dv_path.c_str(), dv_name);

    const f32 screen_world_h_half = /* mSize.x / (2 * mCamera.getZoomScale()) */ (224 / 2) * mBgZoom;
    const f32 screen_world_w_half = /* mSize.y / (2 * mCamera.getZoomScale()) */ screen_world_h_half * mAspect;

    const rio::BaseVec2f center_pos = camera_pos;
    camera_pos.x = center_pos.x - screen_world_w_half;
    camera_pos.y = center_pos.y + screen_world_h_half;

    rio::BaseVec2f bg_screen_center = center_pos;

    rio::BaseVec2f bg_pos { 0.0f, 0.0f };
    f32 bg_offset_area_bottom_to_screen_bottom = 0.0f;
    if (mpDVControlArea != nullptr)
    {
        const AreaData& area_data = *mpDVControlArea;

        const f32 x =  s32(area_data.offset.x);
        const f32 y = -s32(area_data.offset.y);
        const f32 w =  s32(area_data.  size.x);
        const f32 h =  s32(area_data.  size.y);

        bg_pos.x = x + w * 0.5f;
        bg_pos.y = (y - h) + 0.5f * mRealBgZoom * 224.0f;

        bg_screen_center.x = std::clamp<f32>(center_pos.x, x, x + w);
        bg_screen_center.y = std::clamp<f32>(center_pos.y, y - h, y);
        const f32 screen_world_bottom = std::clamp<f32>(center_pos.y - screen_world_h_half, y - h, y);

        bg_offset_area_bottom_to_screen_bottom = std::clamp<f32>(
            screen_world_bottom - (y - h),
            0.0f, h
        );
    }

    DistantViewMgr::instance()->initialize(
        dv_name, dv_path,
        MainWindow::forceSharcfb(),
        bg_pos,
        bg_screen_center,
        bg_offset_area_bottom_to_screen_bottom,
        mBgZoom
    );

  //RIO_LOG("Initialized DistantViewMgr\n");
}

bool CourseView::processMouseInput(bool focused, bool hovered)
{
    static const rio::BaseVec2f zero { 0.0f, 0.0f };

    mIsCursorRelease = !ImGui::IsMouseDown(ImGuiMouseButton_Left);

    if (hovered)
    {
        mIsCursorPress = ImGui::IsMouseClicked(ImGuiMouseButton_Left);
    }

    if (
        focused &&
#if RIO_IS_CAFE
        rio::ControllerMgr::instance()->getMainController()->isHold(
            (1 << rio::Controller::PAD_IDX_ZL) |
            (1 << rio::Controller::PAD_IDX_ZR)
        ) &&
        ImGui::IsMouseDown(ImGuiMouseButton_Left)
#else
        ImGui::IsMouseDown(ImGuiMouseButton_Middle)
#endif // RIO_IS_CAFE
    )
    {
        if (mIsCursorPress)
        {
            mIsCursorPress = false;
            return false;
        }
        mSelectionBox = false;

        const rio::BaseVec2f& mouse_delta = reinterpret_cast<const rio::BaseVec2f&>(ImGui::GetIO().MouseDelta.x);
        if (mouse_delta.x != 0.0f || mouse_delta.y != 0.0f)
        {
            const rio::BaseVec2f& last_cursor_pos_world = viewToWorldPos(zero);
            const rio::BaseVec2f& cursor_pos_world = viewToWorldPos(mouse_delta);

            static_cast<rio::Vector2f&>(mCamera.pos()) +=
                static_cast<const rio::Vector2f&>(last_cursor_pos_world)
                - static_cast<const rio::Vector2f&>(cursor_pos_world);
        }

        return true;
    }

    return false;
}

void CourseView::processKeyboardInput()
{
    if (rio::ControllerMgr::instance()->getMainController()->isTrig(1 << rio::Controller::PAD_IDX_X))
        mLayerShown[LAYER_0] = !mLayerShown[LAYER_0];

    if (rio::ControllerMgr::instance()->getMainController()->isTrig(1 << rio::Controller::PAD_IDX_Y))
        mLayerShown[LAYER_1] = !mLayerShown[LAYER_1];

    if (rio::ControllerMgr::instance()->getMainController()->isTrig(1 << rio::Controller::PAD_IDX_B))
        mLayerShown[LAYER_2] = !mLayerShown[LAYER_2];
}

void CourseView::update()
{
    mRenderBuffer.setRenderTargetColor(&mItemIDTarget, TARGET_TYPE_ITEM_ID);
    {
        mRenderBuffer.read(
            TARGET_TYPE_ITEM_ID, mpItemIDReadBuffer
#if RIO_IS_WIN
            , mpItemIDTexture->getNativeTexture().surface.width
            , mpItemIDTexture->getNativeTexture().surface.height
            , mpItemIDTexture->getNativeTexture().surface.nativeFormat
#endif // RIO_IS_WIN
        );
    }
    mRenderBuffer.setRenderTargetColorNull(TARGET_TYPE_ITEM_ID);

    if (mIsCursorPress)
    {
        s32 width = mpItemIDTexture->getWidth();
        s32 height = mpItemIDTexture->getHeight();

        s32 x = std::clamp<s32>(mCursorPos.x, 0, width - 1);
        s32 y = std::clamp<s32>(mCursorPos.y, 0, height - 1);

        u32 under_mouse = ((u32*)mpItemIDReadBuffer)[y * width + x];
#if RIO_IS_CAFE
        under_mouse = __builtin_bswap32(under_mouse);
#endif // RIO_IS_CAFE

        ItemID id_under_mouse = under_mouse;
        if (id_under_mouse.isValid())
        {
            if (std::find(mSelectedItems.begin(), mSelectedItems.end(), id_under_mouse) == mSelectedItems.end())
            {
                clearSelection_();
                mSelectedItems.push_back(id_under_mouse);
                setItemSelection_(id_under_mouse, true);
            }
        }
        else
        {
            if (!mSelectedItems.empty())
                clearSelection_();

            mSelectionBox = true;
            mSelectionBoxP1 = mCursorPos;
        }
    }
    else if (mIsCursorRelease && mSelectionBox)
    {
        RIO_ASSERT(mSelectedItems.empty());

        mSelectionBoxP2 = mCursorPos;
        mSelectionBox = false;

        s32 width = mpItemIDTexture->getWidth();
        s32 height = mpItemIDTexture->getHeight();

        s32 x1 = std::clamp<s32>(std::min(mSelectionBoxP1.x, mSelectionBoxP2.x), 0, width - 1);
        s32 x2 = std::clamp<s32>(std::max(mSelectionBoxP1.x, mSelectionBoxP2.x), 0, width - 1);
        s32 y1 = std::clamp<s32>(std::min(mSelectionBoxP1.y, mSelectionBoxP2.y), 0, height - 1);
        s32 y2 = std::clamp<s32>(std::max(mSelectionBoxP1.y, mSelectionBoxP2.y), 0, height - 1);

        std::unordered_set<u32> selected_items;
        for (s32 y = y1; y <= y2; y++)
        {
            for (s32 x = x1; x <= x2; x++)
            {
                u32 under_mouse = ((u32*)mpItemIDReadBuffer)[y * width + x];
#if RIO_IS_CAFE
                under_mouse = __builtin_bswap32(under_mouse);
#endif // RIO_IS_CAFE

                ItemID id_under_mouse = under_mouse;
                if (id_under_mouse.isValid())
                {
                    const auto& it = selected_items.insert(id_under_mouse);
                    if (it.second)
                        setItemSelection_(id_under_mouse, true);
                }
            }
        }

        mSelectedItems.insert(mSelectedItems.end(), selected_items.begin(), selected_items.end());
        mSelectionChange = !mSelectedItems.empty();
    }

    const rio::BaseVec2f& camera_pos = mCamera.pos();

    const f32 screen_world_h_half = /* mSize.x / (2 * mCamera.getZoomScale()) */ (224 / 2) * mBgZoom;
    const f32 screen_world_w_half = /* mSize.y / (2 * mCamera.getZoomScale()) */ screen_world_h_half * mAspect;

    const rio::BaseVec2f center_pos {
        camera_pos.x + screen_world_w_half,
        camera_pos.y - screen_world_h_half
    };

    rio::BaseVec2f bg_screen_center = center_pos;

    f32 bg_offset_area_bottom_to_screen_bottom = 0.0f;
    if (mpDVControlArea != nullptr)
    {
        const AreaData& area_data = *mpDVControlArea;

        const f32 x =  s32(area_data.offset.x);
        const f32 y = -s32(area_data.offset.y);
        const f32 w =  s32(area_data.  size.x);
        const f32 h =  s32(area_data.  size.y);

        bg_screen_center.x = std::clamp<f32>(center_pos.x, x, x + w);
        bg_screen_center.y = std::clamp<f32>(center_pos.y, y - h, y);
        const f32 screen_world_bottom = std::clamp<f32>(center_pos.y - screen_world_h_half, y - h, y);

        bg_offset_area_bottom_to_screen_bottom = std::clamp<f32>(
            screen_world_bottom - (y - h),
            0.0f, h
        );
    }

    DistantViewMgr::instance()->update(
        getDistantViewLayer(),
        bg_screen_center,
        bg_offset_area_bottom_to_screen_bottom,
        mBgZoom
    );

    if (mpCourseDataFile != nullptr)
        for (std::unique_ptr<MapActorItem>& p_item : mMapActorItemPtr)
            p_item->onSceneUpdate();
}

void CourseView::calcDistantViewScissor_()
{
    mRenderBuffer.resetScissor();

    mDrawDV = true;

    if (mpDVControlArea != nullptr)
    {
        mDrawDV = false;

        const AreaData& area_data = *mpDVControlArea;

        const f32 x =  s32(area_data.offset.x);
        const f32 y = -s32(area_data.offset.y);
        const f32 w =  s32(area_data.  size.x);
        const f32 h =  s32(area_data.  size.y);

        const rio::BaseVec2f& camera_pos = mCamera.pos();

        const f32 screen_world_h = 224 * mBgZoom;
        const f32 screen_world_w = screen_world_h * mAspect;

        const rio::BaseVec2f screen_world_min {
            camera_pos.x,
            camera_pos.y - screen_world_h
        };

        const rio::BaseVec2f screen_world_max {
            camera_pos.x + screen_world_w,
            camera_pos.y
        };

        const rio::BaseVec2f area_world_min {
            x,
            y - h
        };

        const rio::BaseVec2f area_world_max {
            x + w,
            y
        };

        if (screen_world_min.x < area_world_max.x && area_world_min.x < screen_world_max.x &&
            screen_world_min.y < area_world_max.y && area_world_min.y < screen_world_max.y)
        {
            const rio::BaseVec2f visible_area_world_min {
                std::max<f32>(screen_world_min.x, area_world_min.x),
                std::max<f32>(screen_world_min.y, area_world_min.y)
            };

            const rio::BaseVec2f visible_area_world_max {
                std::min<f32>(screen_world_max.x, area_world_max.x),
                std::min<f32>(screen_world_max.y, area_world_max.y)
            };

            const rio::BaseVec2f& visible_area_min = worldToViewPos(visible_area_world_min);
            const rio::BaseVec2f& visible_area_max = worldToViewPos(visible_area_world_max);

            s32 scissor_min_x = std::max<s32>(visible_area_min.x, 0);
            s32 scissor_min_y = std::max<s32>(visible_area_max.y, 0);

            s32 scissor_max_x = std::min<s32>(visible_area_max.x, mRenderBuffer.getSize().x);
            s32 scissor_max_y = std::min<s32>(visible_area_min.y, mRenderBuffer.getSize().y);

            s32 scissor_w = scissor_max_x - scissor_min_x;
            s32 scissor_h = scissor_max_y - scissor_min_y;

            if (scissor_w > 0 && scissor_h > 0)
            {
                mRenderBuffer.setScissor(scissor_min_x, scissor_min_y, scissor_w, scissor_h);
                mDrawDV = true;
            }
        }
    }
}

void CourseView::gather()
{
    if (MainWindow::applyDistantViewScissor())
        calcDistantViewScissor_();

    if (mDrawDV)
        DistantViewMgr::instance()->draw(getDistantViewLayer());

    Renderer::instance()->setLayer(get3DLayer());
    {
        for (std::unique_ptr<MapActorItem>& p_item : mMapActorItemPtr)
            p_item->scheduleDraw();
    }
    Renderer::instance()->resetLayer();

    mRenderMgrDV.calc();
    mRenderMgr3D.calc();
}

void CourseView::dispose()
{
    mRenderMgrDV.clear();
    mRenderMgr3D.clear();
}

void CourseView::dv_PostFx_(const rio::lyr::DrawInfo&)
{
    if (mDrawDV)
        DistantViewMgr::instance()->applyDepthOfField();
}

void CourseView::setItemSelection_(const ItemID& item_id, bool is_selected)
{
    switch (item_id.getType())
    {
    case ITEM_TYPE_MAP_ACTOR:
        mMapActorItemPtr[item_id.getIndex()]->setSelection(is_selected);
        break;
    default:
        break;
    }
}

void CourseView::clearSelection_()
{
    for (const ItemID& item_id : mSelectedItems)
        setItemSelection_(item_id, false);

    mSelectedItems.clear();
    mSelectionChange = true;
}

void CourseView::onSelectionChange_()
{
    BgRenderer::instance()->calcSelectionVertexBuffer(mSelectedItems);
}

void CourseView::drawSelectionBox_()
{
    const rio::BaseVec2f& p1 = viewToWorldPos(mSelectionBoxP1);
    const rio::BaseVec2f& p2 = viewToWorldPos(mCursorPos);

    const rio::Vector2f min {
        std::min(p1.x, p2.x),
        std::min(p1.y, p2.y)
    };

    const rio::Vector2f max {
        std::max(p1.x, p2.x),
        std::max(p1.y, p2.y)
    };

    rio::PrimitiveRenderer::instance()->begin();
    {
        rio::PrimitiveRenderer::instance()->drawQuad(
            rio::PrimitiveRenderer::QuadArg()
                .setColor(rio::Color4f{ 0.25f, 0.25f, 1.0f, 0.375f })
                .setCornerAndSize({ min.x, min.y, -mProjection.getNear() + 10000.0f }, max - min)
        );
        rio::PrimitiveRenderer::instance()->drawBox(
            rio::PrimitiveRenderer::QuadArg()
                .setColor(rio::Color4f{ 0.25f, 0.25f, 1.0f, 1.0f })
                .setCornerAndSize({ min.x, min.y, -mProjection.getNear() + 10000.0f }, max - min)
        );
    }
    rio::PrimitiveRenderer::instance()->end();
}

void CourseView::DrawCallbackDV::preDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
    mCourseView.mpColorTexture->setCompMap(0x00010203);
    mCourseView.mRenderBuffer.clear(
        rio::RenderBuffer::CLEAR_FLAG_COLOR_DEPTH,
        {
            119 / 255.f,
            136 / 255.f,
            153 / 255.f,
            1.0f
        }
    );
    mCourseView.clearItemIDTexture_();
    mCourseView.bindRenderBuffer_();
}

void CourseView::DrawCallbackDV::preDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
}

void CourseView::DrawCallbackDV::postDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
}

void CourseView::DrawCallbackDV::postDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
    mCourseView.unbindRenderBuffer_();
}

void CourseView::DrawCallback3D::preDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
    if (MainWindow::applyDistantViewScissor())
        mCourseView.mRenderBuffer.resetScissor();

    mCourseView.mpColorTexture->setCompMap(0x00010203);
    mCourseView.bindRenderBuffer_(true);
}

void CourseView::DrawCallback3D::preDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
    mCourseView.bindRenderBuffer_(true);
}

void CourseView::DrawCallback3D::postDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
    mCourseView.bindRenderBuffer_(false);

    rio::PrimitiveRenderer::instance()->setCamera(mCourseView.mCamera);
    rio::PrimitiveRenderer::instance()->setProjection(mCourseView.mProjection);
    rio::PrimitiveRenderer::instance()->setModelMatrix(rio::Matrix34f::ident);

    rio::RenderState render_state;
    render_state.setBlendEnable(false);
    render_state.apply();

    if (mCourseView.mpCourseDataFile != nullptr)
    {
        for (std::unique_ptr<MapActorItem>& p_item : mCourseView.mMapActorItemPtr)
            if (p_item->getMapActorData().layer != LAYER_1)
                p_item->drawOpa(draw_info);

        for (std::unique_ptr<MapActorItem>& p_item : mCourseView.mMapActorItemPtr)
            if (p_item->getMapActorData().layer == LAYER_1)
                p_item->drawOpa(draw_info);

        for (NextGotoItem& item : mCourseView.mNextGotoItem)
            item.drawOpa();

        for (LocationItem& item : mCourseView.mLocationItem)
            item.drawOpa();

        for (AreaItem& item : mCourseView.mAreaItem)
            item.drawOpa();
    }
}

void CourseView::DrawCallback3D::postDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
    mCourseView.bindRenderBuffer_(false);

    rio::PrimitiveRenderer::instance()->setCamera(mCourseView.mCamera);
    rio::PrimitiveRenderer::instance()->setProjection(mCourseView.mProjection);
    rio::PrimitiveRenderer::instance()->setModelMatrix(rio::Matrix34f::ident);

    rio::RenderStateMRT render_state;
    render_state.setBlendEnable(TARGET_TYPE_ITEM_ID, false);
    render_state.apply();

    const CourseDataFile* p_cd_file = mCourseView.mpCourseDataFile;
    if (p_cd_file != nullptr)
    {
        const CourseDataFile& cd_file = *p_cd_file;

        BgRenderer& bg_renderer = *(BgRenderer::instance());
        const bool* layer_shown = mCourseView.mLayerShown;
        bool& selection_change = mCourseView.mSelectionChange;

        if (selection_change)
        {
            mCourseView.onSelectionChange_();
            selection_change = false;
        }

        mCourseView.bindRenderBuffer_(true);
        {
            bg_renderer.render(LAYER_2, cd_file, layer_shown[LAYER_2]);
        }
        mCourseView.bindRenderBuffer_(false);

        for (std::unique_ptr<MapActorItem>& p_item : mCourseView.mMapActorItemPtr)
            if (p_item->getMapActorData().layer != LAYER_1)
                p_item->drawXlu(draw_info);

        mCourseView.bindRenderBuffer_(true);
        {
            bg_renderer.render(LAYER_1, cd_file, layer_shown[LAYER_1]);
        }
        mCourseView.bindRenderBuffer_(false);

        for (std::unique_ptr<MapActorItem>& p_item : mCourseView.mMapActorItemPtr)
            if (p_item->getMapActorData().layer == LAYER_1)
                p_item->drawXlu(draw_info);

        for (NextGotoItem& item : mCourseView.mNextGotoItem)
            item.drawXlu();

        for (LocationItem& item : mCourseView.mLocationItem)
            item.drawXlu();

        mCourseView.bindRenderBuffer_(true);
        {
            bg_renderer.render(LAYER_0, cd_file, layer_shown[LAYER_0]);
        }
        mCourseView.bindRenderBuffer_(false);

        for (AreaItem& item : mCourseView.mAreaItem)
            item.drawXlu();
    }

    if (mCourseView.mSelectionBox)
        mCourseView.drawSelectionBox_();

    mCourseView.unbindRenderBuffer_();
}

const std::vector<ItemID>& CourseView::getSelectedItems() const
{
    return mSelectedItems;
}

std::unique_ptr<MapActorItem>& CourseView::getMapActorItem(int index)
{
    return mMapActorItemPtr[index];
}

BgCourseData& CourseView::getBgUnitObj(int index) const
{
    return mpCourseDataFile->getBgData((index >> 22) & 3)[index & 0x3FFFFF];
}
