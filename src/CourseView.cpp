#include <CourseView.h>
#include <Globals.h>
#include <action/ActionItemDelete.h>
#include <action/ActionItemPushBack.h>
#include <action/ActionItemSelectionMove.h>
#include <action/ActionMgr.h>
#include <actor/ActorCreateMgr.h>
#include <course/Bg.h>
#include <course/BgRenderer.h>
#include <distant_view/DistantViewMgr.h>
#include <graphics/LayerID.h>
#include <graphics/QuadRenderer.h>
#include <graphics/Renderer.h>
#include <item/AreaItem.h>
#include <item/BgUnitItem.h>
#include <item/LocationItem.h>
#include <item/MapActorItem.h>
#include <item/NextGotoItem.h>

#include <container/SafeArray.h>
#include <controller/rio_ControllerMgr.h>
#include <gfx/rio_Window.h>
#include <gfx/lyr/rio_Renderer.h>
#include <gpu/rio_RenderState.h>
#include <gpu/rio_RenderStateMRT.h>

#if RIO_IS_CAFE
#include <gx2/event.h>
#endif // RIO_IS_CAFE

#include <imgui.h>

#include <unordered_set>

CourseView* CourseView::sInstance = nullptr;

bool CourseView::createSingleton(s32 width, s32 height, const rio::BaseVec2f& window_pos)
{
    if (sInstance)
        return false;

    sInstance = new CourseView(width, height, window_pos);
    return true;
}

void CourseView::destroySingleton()
{
    if (!sInstance)
        return;

    delete sInstance;
    sInstance = nullptr;
}

CourseView::CourseView(s32 width, s32 height, const rio::BaseVec2f& window_pos)
    : mIsFocused(false)
    , mIsHovered(false)
    , mDrawCallback3D(*this)
    , mDrawCallbackDV(*this)
    , mpLayer3D(nullptr)
    , mpLayerDV(nullptr)
    , mpDVControlArea(nullptr)
    , mCursorAction(CURSOR_ACTION_NONE)
    , mCursorButtonCurrent(CURSOR_BUTTON_NONE)
    , mCursorState(CURSOR_STATE_RELEASE)
    , mCursorForceReleaseFlag(CURSOR_RELEASE_FLAG_NONE)
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

    setZoomUnitSize(32);
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
    mActorShown = true;
    mActorGraphicsShown = true;
    mNextGotoShown = true;
    mLocationShown = true;

    updateCursorPos(window_pos);

    ActorCreateMgr::createSingleton();
}

CourseView::~CourseView()
{
    mSelectedItems.clear(); mSelectionChange = true;
    mBgUnitItem[LAYER_0].clear();
    mBgUnitItem[LAYER_1].clear();
    mBgUnitItem[LAYER_2].clear();
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

void CourseView::resize(s32 width, s32 height, bool preserve_unit_size)
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
         mSize.x    // Right
    );

    if (preserve_unit_size)
        setZoomUnitSize(getZoomUnitSize());
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

void CourseView::setCameraCenterWorldPos(const rio::BaseVec2f& center_pos)
{
    const f32 screen_world_h_half = /* mSize.x / (2 * mCamera.getZoomScale()) */ (224 / 2) * mBgZoom;
    const f32 screen_world_w_half = /* mSize.y / (2 * mCamera.getZoomScale()) */ screen_world_h_half * mAspect;

    mCamera.pos().x = center_pos.x - screen_world_w_half;
    mCamera.pos().y = center_pos.y + screen_world_h_half;
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
    onCursorRelease_L_();
    onCursorRelease_R_();

#if RIO_IS_CAFE
    GX2DrawDone();
#elif RIO_IS_WIN
    RIO_GL_CALL(glFinish());
#endif

    mCursorState = CURSOR_STATE_RELEASE;;
    mCursorButtonCurrent = CURSOR_BUTTON_NONE;
    mCursorForceReleaseFlag = CURSOR_RELEASE_FLAG_NONE;

    // Clear items
    mSelectedItems.clear(); mSelectionChange = true;
    mBgUnitItem[LAYER_0].clear();
    mBgUnitItem[LAYER_1].clear();
    mBgUnitItem[LAYER_2].clear();
    mMapActorItemPtr.clear();
    mNextGotoItem.clear();
    mLocationItem.clear();
    mAreaItem.clear();

    mpCourseDataFile = p_cd_file;
    mpDVControlArea = nullptr;

    mCursorAction = CURSOR_ACTION_NONE;

    setZoomUnitSize(32);
    mRealBgZoom = mBgZoom;

    if (mpCourseDataFile == nullptr)
    {
        // Clear BG
        Bg::instance()->clearBgCourseData();
        BgRenderer::instance()->createVertexBuffer();

        // Load default distant view
        const char* dv_name = "Nohara";
        const std::string& dv_path = Globals::getContentPath() + "/Common/distant_view";
        RIO_LOG("DV Path: \"%s\", DV Name: \"%s\"\n", dv_path.c_str(), dv_name);
        DistantViewMgr::instance()->initialize(dv_name, dv_path, Globals::forceSharcfb());

        return;
    }

    Bg::instance()->processBgCourseData(*mpCourseDataFile);
    BgRenderer::instance()->createVertexBuffer();

    for (u8 layer = 0; layer < CD_FILE_LAYER_MAX_NUM; layer++)
    {
        std::vector<BgCourseData>& vec = mpCourseDataFile->getBgData(layer);
        size_t num = vec.size();
        for (u32 i = 0; i < num; i++)
            mBgUnitItem[layer].emplace_back(vec[i], layer << 22 | i);
    }

    {
        std::vector<MapActorData>& vec = mpCourseDataFile->getMapActorData();
        size_t num = vec.size();
        for (u32 i = 0; i < num; i++)
            mMapActorItemPtr.emplace_back(ActorCreateMgr::instance()->create(vec[i], i));
    }

    {
        std::vector<NextGoto>& vec = mpCourseDataFile->getNextGoto();
        size_t num = vec.size();
        for (u32 i = 0; i < num; i++)
            mNextGotoItem.emplace_back(vec[i], i);
    }

    {
        std::vector<Location>& vec = mpCourseDataFile->getLocation();
        size_t num = vec.size();
        for (u32 i = 0; i < num; i++)
            mLocationItem.emplace_back(vec[i], i);
    }

    {
        std::vector<AreaData>& vec = mpCourseDataFile->getAreaData();
        size_t num = vec.size();
        for (u32 i = 0; i < num; i++)
            mAreaItem.emplace_back(i);
    }

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

    const char* dv_name = nullptr;

    if (mpCourseDataFile->getAreaData().size() > 0)
    {
        u8 area;

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

    rio::BaseVec2f center_pos;

    if (start_next_goto)
    {
        center_pos.x =   f32(start_next_goto->offset.x + 8 + start_next_goto->camera_offset.x) ;
        center_pos.y = -(f32(start_next_goto->offset.y + 8 + start_next_goto->camera_offset.y));
    }
    else
    {
        center_pos.x = 0.0f;
        center_pos.y = 0.0f;
    }

    RIO_ASSERT(dv_name != nullptr);

    const std::string& dv_path = Globals::getContentPath() + "/Common/distant_view";
    RIO_LOG("DV Path: \"%s\", DV Name: \"%s\"\n", dv_path.c_str(), dv_name);

    const f32 screen_world_h_half = /* mSize.x / (2 * mCamera.getZoomScale()) */ (224 / 2) * mBgZoom;
    const f32 screen_world_w_half = /* mSize.y / (2 * mCamera.getZoomScale()) */ screen_world_h_half * mAspect;

    rio::BaseVec2f& camera_pos = mCamera.pos();
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
        Globals::forceSharcfb(),
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

    mIsFocused = focused;
    mIsHovered = hovered;

    bool press = false;

    if (focused && hovered && mCursorButtonCurrent == CURSOR_BUTTON_NONE)
    {
        bool press_l = ImGui::IsMouseClicked(ImGuiMouseButton_Left);
        bool press_r = ImGui::IsMouseClicked(ImGuiMouseButton_Right);

        if (press_l && !press_r)
        {
            press = true;
            mCursorButtonCurrent = CURSOR_BUTTON_L;
        }
        else if (press_r && !press_l)
        {
            press = true;
            mCursorButtonCurrent = CURSOR_BUTTON_R;
        }
    }

    if (press)
        mCursorState = CURSOR_STATE_PRESS;

    else
    {
        bool hold = false;

        switch (mCursorButtonCurrent)
        {
        default:
            break;
        case CURSOR_BUTTON_L:
            hold = ImGui::IsMouseDown(ImGuiMouseButton_Left);
            break;
        case CURSOR_BUTTON_R:
            hold = ImGui::IsMouseDown(ImGuiMouseButton_Right);
            break;
        }

        if (hold)
            mCursorState = CURSOR_STATE_HOLD;
        else
            mCursorState = CURSOR_STATE_RELEASE;
    }

    if (focused && hovered && ImGui::IsMouseDown(ImGuiMouseButton_Middle))
    {
        if (!press)
        {
            switch (mCursorButtonCurrent)
            {
            default:
                break;
            case CURSOR_BUTTON_L:
                mCursorForceReleaseFlag = CURSOR_RELEASE_FLAG_L;
                break;
            case CURSOR_BUTTON_R:
                mCursorForceReleaseFlag = CURSOR_RELEASE_FLAG_R;
                break;
            }
        }

        mCursorState = CURSOR_STATE_RELEASE;
        mCursorButtonCurrent = CURSOR_BUTTON_NONE;

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
    // For processing keyboard inputs irrespective of the current mouse action
    RIO_ASSERT(mIsFocused);
}

void CourseView::undo()
{
    if (!ActionMgr::instance()->canUndo())
        return;

    clearSelection();
    ActionMgr::instance()->undo();
}

void CourseView::redo()
{
    if (!ActionMgr::instance()->canRedo())
        return;

    clearSelection();
    ActionMgr::instance()->redo();
}

void CourseView::moveItems(const std::vector<ItemID>& items, s16 dx, s16 dy, bool commit)
{
    bool layers_changed[CD_FILE_LAYER_MAX_NUM] = {
        false, false, false
    };

    for (const ItemID& item_id : items)
    {
        switch (item_id.getType())
        {
        default:
            break;
        case ITEM_TYPE_BG_UNIT_OBJ:
            {
                u8 layer = item_id.getIndex() >> 22;
                mBgUnitItem[layer][item_id.getIndex() & 0x003FFFFF].move(dx, dy, commit);
                layers_changed[layer] = true;
            }
            break;
        case ITEM_TYPE_MAP_ACTOR:
            mMapActorItemPtr[item_id.getIndex()]->move(dx, dy, commit);
            break;
        case ITEM_TYPE_NEXT_GOTO:
            mNextGotoItem[item_id.getIndex()].move(dx, dy, commit);
            break;
        case ITEM_TYPE_LOCATION:
            mLocationItem[item_id.getIndex()].move(dx, dy, commit);
            break;
        }
    }

    for (u8 layer = 0; layer < CD_FILE_LAYER_MAX_NUM; layer++)
    {
        if (layers_changed[layer])
        {
            Bg::instance()->processBgCourseData(*mpCourseDataFile, layer);
            BgRenderer::instance()->createVertexBuffer(layer);
        }
    }
}

void CourseView::setItemData(const ItemID& item_id, const void* data, u32 data_change_flag)
{
    RIO_ASSERT(data != nullptr);

    switch (item_id.getType())
    {
    default:
        break;
    case ITEM_TYPE_BG_UNIT_OBJ:
        {
            u8 layer = item_id.getIndex() >> 22;

            mpCourseDataFile->getBgData(layer)[item_id.getIndex() & 0x003FFFFF] = *static_cast<const BgCourseData*>(data);

            Bg::instance()->processBgCourseData(*mpCourseDataFile, layer);
            BgRenderer::instance()->createVertexBuffer(layer);
        }
        break;
    case ITEM_TYPE_MAP_ACTOR:
        {
            const MapActorData& map_actor_data = *static_cast<const MapActorData*>(data);
            mpCourseDataFile->getMapActorData()[item_id.getIndex()] = map_actor_data;
            mMapActorItemPtr[item_id.getIndex()]->onDataChange(map_actor_data, (MapActorItem::DataChangeFlag)data_change_flag);
        }
        break;
    case ITEM_TYPE_NEXT_GOTO:
        mpCourseDataFile->getNextGoto()[item_id.getIndex()] = *static_cast<const NextGoto*>(data);
        break;
    case ITEM_TYPE_LOCATION:
        mpCourseDataFile->getLocation()[item_id.getIndex()] = *static_cast<const Location*>(data);
        break;
    }
}

void CourseView::moveItems_(bool commit)
{
    const rio::BaseVec2f& last_cursor_pos_world = viewToWorldPos(mCursorP1);
    const rio::BaseVec2f& cursor_pos_world = viewToWorldPos(mCursorPos);

    const rio::Vector2f& mouse_delta_world =
        static_cast<const rio::Vector2f&>(cursor_pos_world)
        - static_cast<const rio::Vector2f&>(last_cursor_pos_world);

    bool bg_selected = false;
    for (const ItemID& item_id : mSelectedItems)
    {
        if (item_id.getType() == ITEM_TYPE_BG_UNIT_OBJ)
        {
            bg_selected = true;
            break;
        }
    }

    s16 dx, dy;

    if (bg_selected)
    {
        dx = std::lround( mouse_delta_world.x / 16) * 16;
        dy = std::lround(-mouse_delta_world.y / 16) * 16;
    }
    else
    {
        dx = std::lround( mouse_delta_world.x / 8) * 8;
        dy = std::lround(-mouse_delta_world.y / 8) * 8;
    }

    if (commit)
    {
        if (dx == 0 && dy == 0)
            return;

        ActionItemSelectionMove::Context context { mSelectedItems, dx, dy };
        ActionMgr::instance()->pushAction<ActionItemSelectionMove>(&context);
    }
    else
    {
        moveItems(mSelectedItems, dx, dy, false);
    }

    if (bg_selected)
        BgRenderer::instance()->calcSelectionVertexBuffer(mSelectedItems);
}

void CourseView::onCursorHold_MoveItem_()
{
    RIO_ASSERT(!mSelectedItems.empty());

    const rio::BaseVec2f& mouse_delta = reinterpret_cast<const rio::BaseVec2f&>(ImGui::GetIO().MouseDelta.x);
    if (mouse_delta.x == 0.0f && mouse_delta.y == 0.0f)
        return;

    moveItems_(false);
}

void CourseView::onCursorRelease_MoveItem_()
{
    if (mCursorPos == mCursorP1)
        return;

    moveItems_(true);
}

void CourseView::onCursorRelease_SelectionBox_()
{
    RIO_ASSERT(mSelectedItems.empty());

    s32 width = mpItemIDTexture->getWidth();
    s32 height = mpItemIDTexture->getHeight();

    s32 x1 = std::clamp<s32>(std::min(mCursorP1.x, mCursorPos.x), 0, width - 1);
    s32 x2 = std::clamp<s32>(std::max(mCursorP1.x, mCursorPos.x), 0, width - 1);
    s32 y1 = std::clamp<s32>(std::min(mCursorP1.y, mCursorPos.y), 0, height - 1);
    s32 y2 = std::clamp<s32>(std::max(mCursorP1.y, mCursorPos.y), 0, height - 1);

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

void CourseView::onCursorPress_L_()
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
            selectItem(id_under_mouse);

        mCursorAction = CURSOR_ACTION_MOVE_ITEM;
    }
    else
    {
        clearSelection_();
        mCursorAction = CURSOR_ACTION_SELECTION_BOX;
    }
    mCursorP1 = mCursorPos;
}

void CourseView::onCursorHold_L_()
{
    switch (mCursorAction)
    {
    default:
        break;
    case CURSOR_ACTION_MOVE_ITEM:
        onCursorHold_MoveItem_();
        break;
    }
}

void CourseView::onCursorRelease_L_()
{
    switch (mCursorAction)
    {
    default:
        break;
    case CURSOR_ACTION_MOVE_ITEM:
        onCursorRelease_MoveItem_();
        mCursorAction = CURSOR_ACTION_NONE;
        break;
    case CURSOR_ACTION_SELECTION_BOX:
        onCursorRelease_SelectionBox_();
        mCursorAction = CURSOR_ACTION_NONE;
        break;
    }
}

void CourseView::pushBackItem_BgUnitObj_(const BgCourseData& data, u8 layer)
{
    RIO_ASSERT(layer < CD_FILE_LAYER_MAX_NUM);

    std::vector<BgCourseData>& data_vec = mpCourseDataFile->getBgData(layer);
    std::vector<BgUnitItem>& item_vec = mBgUnitItem[layer];
    RIO_ASSERT(data_vec.size() == item_vec.size());
    u32 i = item_vec.size();

    data_vec.push_back(data);
    RIO_ASSERT(data_vec.size() == i + 1);

    item_vec.emplace_back(data, layer << 22 | i);
    RIO_ASSERT(item_vec.size() == i + 1);
}

void CourseView::popBackItem_BgUnitObj_(u8 layer)
{
    std::vector<BgCourseData>& data_vec = mpCourseDataFile->getBgData(layer);
    std::vector<BgUnitItem>& item_vec = mBgUnitItem[layer];
    RIO_ASSERT(data_vec.size() == item_vec.size());

    item_vec.pop_back();
    data_vec.pop_back();

    RIO_ASSERT(data_vec.size() == item_vec.size());
}

void CourseView::pushBackItem_MapActor_(const MapActorData& data)
{
    std::vector<MapActorData>& vec = mpCourseDataFile->getMapActorData();
    RIO_ASSERT(vec.size() == mMapActorItemPtr.size());
    u32 i = mMapActorItemPtr.size();

    vec.push_back(data);
    RIO_ASSERT(vec.size() == i + 1);

    mMapActorItemPtr.emplace_back(ActorCreateMgr::instance()->create(data, i));
    RIO_ASSERT(mMapActorItemPtr.size() == i + 1);
}

void CourseView::popBackItem_MapActor_()
{
    std::vector<MapActorData>& vec = mpCourseDataFile->getMapActorData();
    RIO_ASSERT(vec.size() == mMapActorItemPtr.size());

    mMapActorItemPtr.pop_back();
    vec.pop_back();

    RIO_ASSERT(vec.size() == mMapActorItemPtr.size());
}

void CourseView::pushBackItem_NextGoto_(const NextGoto& data)
{
    std::vector<NextGoto>& vec = mpCourseDataFile->getNextGoto();
    RIO_ASSERT(vec.size() == mNextGotoItem.size());
    u32 i = mNextGotoItem.size();

    vec.push_back(data);
    RIO_ASSERT(vec.size() == i + 1);

    mNextGotoItem.emplace_back(data, i);
    RIO_ASSERT(mNextGotoItem.size() == i + 1);
}

void CourseView::popBackItem_NextGoto_()
{
    std::vector<NextGoto>& vec = mpCourseDataFile->getNextGoto();
    RIO_ASSERT(vec.size() == mNextGotoItem.size());

    mNextGotoItem.pop_back();
    vec.pop_back();

    RIO_ASSERT(vec.size() == mNextGotoItem.size());
}

void CourseView::pushBackItem_Location_(const Location& data)
{
    std::vector<Location>& vec = mpCourseDataFile->getLocation();
    RIO_ASSERT(vec.size() == mLocationItem.size());
    u32 i = mLocationItem.size();

    vec.push_back(data);
    RIO_ASSERT(vec.size() == i + 1);

    mLocationItem.emplace_back(data, i);
    RIO_ASSERT(mLocationItem.size() == i + 1);
}

void CourseView::popBackItem_Location_()
{
    std::vector<Location>& vec = mpCourseDataFile->getLocation();
    RIO_ASSERT(vec.size() == mLocationItem.size());

    mLocationItem.pop_back();
    vec.pop_back();

    RIO_ASSERT(vec.size() == mLocationItem.size());
}

void CourseView::pushBackItem(ItemType item_type, const void* data, const void* extra)
{
    switch (item_type)
    {
    default:
        break;
    case ITEM_TYPE_BG_UNIT_OBJ:
        pushBackItem_BgUnitObj_(*static_cast<const BgCourseData*>(data), *static_cast<const u8*>(extra));
        break;
    case ITEM_TYPE_MAP_ACTOR:
        pushBackItem_MapActor_(*static_cast<const MapActorData*>(data));
        break;
    case ITEM_TYPE_NEXT_GOTO:
        pushBackItem_NextGoto_(*static_cast<const NextGoto*>(data));
        break;
    case ITEM_TYPE_LOCATION:
        pushBackItem_Location_(*static_cast<const Location*>(data));
        break;
    }
}

void CourseView::pushBackItemWithTransform(s32 dx, s32 dy, ItemType item_type, const void* data, const void* extra)
{
    switch (item_type)
    {
    default:
        break;
    case ITEM_TYPE_BG_UNIT_OBJ:
        {
            BgCourseData data_(*static_cast<const BgCourseData*>(data));
            data_.offset.x = std::clamp<s32>(data_.offset.x + dx, 0, BG_MAX_UNIT_X - 1);
            data_.offset.y = std::clamp<s32>(data_.offset.y + dy, 0, BG_MAX_UNIT_Y - 1);
            pushBackItem_BgUnitObj_(data_, *static_cast<const u8*>(extra));
        }
        break;
    case ITEM_TYPE_MAP_ACTOR:
        {
            MapActorData data_(*static_cast<const MapActorData*>(data));
            data_.offset.x = std::clamp<s32>(data_.offset.x + dx * 16, 0, BG_MAX_X - 1);
            data_.offset.y = std::clamp<s32>(data_.offset.y + dy * 16, 0, BG_MAX_Y - 1);
            pushBackItem_MapActor_(data_);
        }
        break;
    case ITEM_TYPE_NEXT_GOTO:
        {
            NextGoto data_(*static_cast<const NextGoto*>(data));
            data_.offset.x = std::clamp<s32>(data_.offset.x + dx * 16, 0, BG_MAX_X - 1);
            data_.offset.y = std::clamp<s32>(data_.offset.y + dy * 16, 0, BG_MAX_Y - 1);
            pushBackItem_NextGoto_(data_);
        }
        break;
    case ITEM_TYPE_LOCATION:
        {
            Location data_(*static_cast<const Location*>(data));
            data_.offset.x = std::clamp<s32>(data_.offset.x + dx * 16, 0, BG_MAX_X - 1);
            data_.offset.y = std::clamp<s32>(data_.offset.y + dy * 16, 0, BG_MAX_Y - 1);
            pushBackItem_Location_(data_);
        }
        break;
    }
}

void CourseView::popBackItem(ItemType item_type, const void* extra)
{
    switch (item_type)
    {
    default:
        break;
    case ITEM_TYPE_BG_UNIT_OBJ:
        popBackItem_BgUnitObj_(*static_cast<const u8*>(extra));
        break;
    case ITEM_TYPE_MAP_ACTOR:
        popBackItem_MapActor_();
        break;
    case ITEM_TYPE_NEXT_GOTO:
        popBackItem_NextGoto_();
        break;
    case ITEM_TYPE_LOCATION:
        popBackItem_Location_();
        break;
    }
}

void CourseView::onCursorPress_Paint_BgUnitObj_()
{
    clearSelection_();

    const rio::BaseVec2f& p = viewToWorldPos(mCursorPos);
    s32 x =  p.x / 16;
    s32 y = -p.y / 16;

    if (x < 0 || x >= BG_MAX_UNIT_X || y < 0 || y >= BG_MAX_UNIT_Y)
    {
        mPaintCurrent.type = ITEM_TYPE_MAX_NUM;
        return;
    }

    mCursorP1World.x = x;
    mCursorP1World.y = y;

    pushBackItem_BgUnitObj_({ mPaintCurrent.bg_unit_obj_type, { u16(x), u16(y) }, { 1, 1 } }, mPaintCurrent.layer);

    Bg::instance()->processBgCourseData(*mpCourseDataFile, mPaintCurrent.layer);
    BgRenderer::instance()->createVertexBuffer(mPaintCurrent.layer);
}

void CourseView::onCursorHold_Paint_BgUnitObj_()
{
    std::vector<BgCourseData>& vec = mpCourseDataFile->getBgData(mPaintCurrent.layer);
    BgCourseData& data = vec[vec.size() - 1];

    const rio::BaseVec2f& p = viewToWorldPos(mCursorPos);
    s32 x = std::clamp<s32>( p.x / 16, 0, BG_MAX_UNIT_X);
    s32 y = std::clamp<s32>(-p.y / 16, 0, BG_MAX_UNIT_Y);

    u16 x1 = std::min<u16>(x, mCursorP1World.x); if (x1 == BG_MAX_UNIT_X) x1 = BG_MAX_UNIT_X - 1;
    u16 y1 = std::min<u16>(y, mCursorP1World.y); if (y1 == BG_MAX_UNIT_Y) y1 = BG_MAX_UNIT_Y - 1;

    u16 x2 = std::max<u16>(x, mCursorP1World.x);
    u16 y2 = std::max<u16>(y, mCursorP1World.y);

    u32 w = x2 - x1 + 1;
    u32 h = y2 - y1 + 1;

    if (x1 == data.offset.x && y1 == data.offset.y && w == data.size.x && h == data.size.y)
        return;

    data.offset.x = x1;
    data.offset.y = y1;
    data.size.x = w;
    data.size.y = h;

    Bg::instance()->processBgCourseData(*mpCourseDataFile, mPaintCurrent.layer);
    BgRenderer::instance()->createVertexBuffer(mPaintCurrent.layer);
}

void CourseView::onCursorRelease_Paint_BgUnitObj_()
{
    const std::vector<BgCourseData>& vec = mpCourseDataFile->getBgData(mPaintCurrent.layer);
    std::shared_ptr<BgCourseData> p_data = std::make_shared<BgCourseData>(vec[vec.size() - 1]);

    popBackItem_BgUnitObj_(mPaintCurrent.layer);

    const rio::BaseVec2f& p = viewToWorldPos(mCursorPos);
    s32 x = std::clamp<s32>( p.x / 16, 0, BG_MAX_UNIT_X);
    s32 y = std::clamp<s32>(-p.y / 16, 0, BG_MAX_UNIT_Y);

    u16 x1 = std::min<u16>(x, mCursorP1World.x); if (x1 == BG_MAX_UNIT_X) x1 = BG_MAX_UNIT_X - 1;
    u16 y1 = std::min<u16>(y, mCursorP1World.y); if (y1 == BG_MAX_UNIT_Y) y1 = BG_MAX_UNIT_Y - 1;

    u16 x2 = std::max<u16>(x, mCursorP1World.x);
    u16 y2 = std::max<u16>(y, mCursorP1World.y);

    u32 w = x2 - x1 + 1;
    u32 h = y2 - y1 + 1;

    p_data->offset.x = x1;
    p_data->offset.y = y1;
    p_data->size.x = w;
    p_data->size.y = h;

    ActionItemPushBack::Context context;
    context.items.emplace_back(
        ITEM_TYPE_BG_UNIT_OBJ,
        std::static_pointer_cast<const void>(p_data),
        std::static_pointer_cast<const void>(std::make_shared<u8>(mPaintCurrent.layer))
    );
    ActionMgr::instance()->pushAction<ActionItemPushBack>(&context);
}

void CourseView::onCursorPress_Paint_MapActor_()
{
    clearSelection_();

    const rio::BaseVec2f& p = viewToWorldPos(mCursorPos);
    s32 x = s32( p.x / 8) * 8;
    s32 y = s32(-p.y / 8) * 8;

    if (x < 0 || x >= BG_MAX_X || y < 0 || y >= BG_MAX_Y)
    {
        mPaintCurrent.type = ITEM_TYPE_MAX_NUM;
        return;
    }

    MapActorData map_actor_data = { 0 };

    const auto& it = ActorCreateMgr::instance()->getActorFactory(mPaintCurrent.map_actor_id);
    if (it != nullptr && it->second != nullptr)
        map_actor_data = *it->second;

    map_actor_data.id = mPaintCurrent.map_actor_id;
    map_actor_data.offset.x = x;
    map_actor_data.offset.y = y;

    pushBackItem_MapActor_(map_actor_data);
}

void CourseView::onCursorHold_Paint_MapActor_()
{
    std::vector<MapActorData>& vec = mpCourseDataFile->getMapActorData();
    MapActorData& data = vec[vec.size() - 1];

    const rio::BaseVec2f& p = viewToWorldPos(mCursorPos);
    s32 x = std::clamp<s32>(s32( p.x / 8) * 8, 0, BG_MAX_X - 8);
    s32 y = std::clamp<s32>(s32(-p.y / 8) * 8, 0, BG_MAX_Y - 8);

    if (x == data.offset.x && y == data.offset.y)
        return;

    data.offset.x = x;
    data.offset.y = y;

    mMapActorItemPtr[vec.size() - 1]->onDataChange(data, MapActorItem::DATA_CHANGE_FLAG_OFFSET);
}

void CourseView::onCursorRelease_Paint_MapActor_()
{
    const std::vector<MapActorData>& vec = mpCourseDataFile->getMapActorData();
    std::shared_ptr<MapActorData> p_data = std::make_shared<MapActorData>(vec[vec.size() - 1]);

    popBackItem_MapActor_();

    const rio::BaseVec2f& p = viewToWorldPos(mCursorPos);
    s32 x = std::clamp<s32>(s32( p.x / 8) * 8, 0, BG_MAX_X - 8);
    s32 y = std::clamp<s32>(s32(-p.y / 8) * 8, 0, BG_MAX_Y - 8);

    p_data->offset.x = x;
    p_data->offset.y = y;

    ActionItemPushBack::Context context;
    context.items.emplace_back(
        ITEM_TYPE_MAP_ACTOR,
        std::static_pointer_cast<const void>(p_data)
    );
    ActionMgr::instance()->pushAction<ActionItemPushBack>(&context);
}

void CourseView::onCursorPress_Paint_NextGoto_()
{
    clearSelection_();

    const rio::BaseVec2f& p = viewToWorldPos(mCursorPos);
    s32 x = s32( p.x / 8) * 8;
    s32 y = s32(-p.y / 8) * 8;

    if (x < 0 || x >= BG_MAX_X || y < 0 || y >= BG_MAX_Y)
    {
        mPaintCurrent.type = ITEM_TYPE_MAX_NUM;
        return;
    }

    u8 id = 0;
    while (true)
    {
        bool conflict = false;

        for (const NextGoto& next_goto : mpCourseDataFile->getNextGoto())
        {
            if (next_goto.id == id)
            {
                conflict = true;
                break;
            }
        }

        if (!conflict)
            break;

        if (id == 0xff) // bruh
            break;

        id++;
    }

    pushBackItem_NextGoto_({ .offset = { u16(x), u16(y) }, .id = id });
}

void CourseView::onCursorHold_Paint_NextGoto_()
{
    std::vector<NextGoto>& vec = mpCourseDataFile->getNextGoto();
    NextGoto& data = vec[vec.size() - 1];

    const rio::BaseVec2f& p = viewToWorldPos(mCursorPos);
    s32 x = std::clamp<s32>(s32( p.x / 8) * 8, 0, BG_MAX_X - 8);
    s32 y = std::clamp<s32>(s32(-p.y / 8) * 8, 0, BG_MAX_Y - 8);

    data.offset.x = x;
    data.offset.y = y;
}

void CourseView::onCursorRelease_Paint_NextGoto_()
{
    const std::vector<NextGoto>& vec = mpCourseDataFile->getNextGoto();
    std::shared_ptr<NextGoto> p_data = std::make_shared<NextGoto>(vec[vec.size() - 1]);

    popBackItem_NextGoto_();

    const rio::BaseVec2f& p = viewToWorldPos(mCursorPos);
    s32 x = std::clamp<s32>(s32( p.x / 8) * 8, 0, BG_MAX_X - 8);
    s32 y = std::clamp<s32>(s32(-p.y / 8) * 8, 0, BG_MAX_Y - 8);

    p_data->offset.x = x;
    p_data->offset.y = y;

    ActionItemPushBack::Context context;
    context.items.emplace_back(
        ITEM_TYPE_NEXT_GOTO,
        std::static_pointer_cast<const void>(p_data)
    );
    ActionMgr::instance()->pushAction<ActionItemPushBack>(&context);
}

void CourseView::onCursorPress_Paint_Location_()
{
    clearSelection_();

    const rio::BaseVec2f& p = viewToWorldPos(mCursorPos);
    s32 x = s32( p.x / 8) * 8;
    s32 y = s32(-p.y / 8) * 8;

    if (x < 0 || x >= BG_MAX_X || y < 0 || y >= BG_MAX_Y)
    {
        mPaintCurrent.type = ITEM_TYPE_MAX_NUM;
        return;
    }

    u8 id = 0;
    while (true)
    {
        bool conflict = false;

        for (const Location& location : mpCourseDataFile->getLocation())
        {
            if (location.id == id)
            {
                conflict = true;
                break;
            }
        }

        if (!conflict)
            break;

        if (id == 0xff) // bruh
            break;

        id++;
    }

    mCursorP1World.x = x;
    mCursorP1World.y = y;

    pushBackItem_Location_({ { u16(x), u16(y) }, { 8, 8 }, id });
}

void CourseView::onCursorHold_Paint_Location_()
{
    std::vector<Location>& vec = mpCourseDataFile->getLocation();
    Location& data = vec[vec.size() - 1];

    const rio::BaseVec2f& p = viewToWorldPos(mCursorPos);
    s32 x = std::clamp<s32>(s32( p.x / 8) * 8, 0, BG_MAX_X);
    s32 y = std::clamp<s32>(s32(-p.y / 8) * 8, 0, BG_MAX_Y);

    u16 x1 = std::min<u16>(x, mCursorP1World.x); if (x1 == BG_MAX_X) x1 = BG_MAX_X - 8;
    u16 y1 = std::min<u16>(y, mCursorP1World.y); if (y1 == BG_MAX_Y) y1 = BG_MAX_Y - 8;

    u16 x2 = std::max<u16>(x, mCursorP1World.x);
    u16 y2 = std::max<u16>(y, mCursorP1World.y);

    u32 w = x2 - x1 + 8;
    u32 h = y2 - y1 + 8;

    data.offset.x = x1;
    data.offset.y = y1;
    data.size.x = w;
    data.size.y = h;
}

void CourseView::onCursorRelease_Paint_Location_()
{
    const std::vector<Location>& vec = mpCourseDataFile->getLocation();
    std::shared_ptr<Location> p_data = std::make_shared<Location>(vec[vec.size() - 1]);

    popBackItem_Location_();

    const rio::BaseVec2f& p = viewToWorldPos(mCursorPos);
    s32 x = std::clamp<s32>(s32( p.x / 8) * 8, 0, BG_MAX_X);
    s32 y = std::clamp<s32>(s32(-p.y / 8) * 8, 0, BG_MAX_Y);

    u16 x1 = std::min<u16>(x, mCursorP1World.x); if (x1 == BG_MAX_X) x1 = BG_MAX_X - 8;
    u16 y1 = std::min<u16>(y, mCursorP1World.y); if (y1 == BG_MAX_Y) y1 = BG_MAX_Y - 8;

    u16 x2 = std::max<u16>(x, mCursorP1World.x);
    u16 y2 = std::max<u16>(y, mCursorP1World.y);

    u32 w = x2 - x1 + 8;
    u32 h = y2 - y1 + 8;

    p_data->offset.x = x1;
    p_data->offset.y = y1;
    p_data->size.x = w;
    p_data->size.y = h;

    ActionItemPushBack::Context context;
    context.items.emplace_back(
        ITEM_TYPE_LOCATION,
        std::static_pointer_cast<const void>(p_data)
    );
    ActionMgr::instance()->pushAction<ActionItemPushBack>(&context);
}

void CourseView::onCursorPress_R_()
{
    switch (mPaintNext.type)
    {
    default:
        break;
    case ITEM_TYPE_BG_UNIT_OBJ:
        mPaintCurrent.type = ITEM_TYPE_BG_UNIT_OBJ;
        mPaintCurrent.layer = mPaintNext.layer;
        mPaintCurrent.bg_unit_obj_type = mPaintNext.bg_unit_obj_type;
        onCursorPress_Paint_BgUnitObj_();
        break;
    case ITEM_TYPE_MAP_ACTOR:
        mPaintCurrent.type = ITEM_TYPE_MAP_ACTOR;
        mPaintCurrent.map_actor_id = mPaintNext.map_actor_id;
        onCursorPress_Paint_MapActor_();
        break;
    case ITEM_TYPE_NEXT_GOTO:
        mPaintCurrent.type = ITEM_TYPE_NEXT_GOTO;
        onCursorPress_Paint_NextGoto_();
        break;
    case ITEM_TYPE_LOCATION:
        mPaintCurrent.type = ITEM_TYPE_LOCATION;
        onCursorPress_Paint_Location_();
        break;
    }
}

void CourseView::onCursorHold_R_()
{
    switch (mPaintCurrent.type)
    {
    default:
        break;
    case ITEM_TYPE_BG_UNIT_OBJ:
        onCursorHold_Paint_BgUnitObj_();
        break;
    case ITEM_TYPE_MAP_ACTOR:
        onCursorHold_Paint_MapActor_();
        break;
    case ITEM_TYPE_NEXT_GOTO:
        onCursorHold_Paint_NextGoto_();
        break;
    case ITEM_TYPE_LOCATION:
        onCursorHold_Paint_Location_();
        break;
    }
}

void CourseView::onCursorRelease_R_()
{
    switch (mPaintCurrent.type)
    {
    default:
        break;
    case ITEM_TYPE_BG_UNIT_OBJ:
        onCursorRelease_Paint_BgUnitObj_();
        mPaintCurrent.type = ITEM_TYPE_MAX_NUM;
        break;
    case ITEM_TYPE_MAP_ACTOR:
        onCursorRelease_Paint_MapActor_();
        mPaintCurrent.type = ITEM_TYPE_MAX_NUM;
        break;
    case ITEM_TYPE_NEXT_GOTO:
        onCursorRelease_Paint_NextGoto_();
        mPaintCurrent.type = ITEM_TYPE_MAX_NUM;
        break;
    case ITEM_TYPE_LOCATION:
        onCursorRelease_Paint_Location_();
        mPaintCurrent.type = ITEM_TYPE_MAX_NUM;
        break;
    }
}

void CourseView::onCursorReleasedCompletely_()
{
    if (!mIsFocused)
        return;

    if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) || ImGui::IsKeyDown(ImGuiKey_RightCtrl))
    {
        if (!(ImGui::IsKeyDown(ImGuiKey_LeftShift) || ImGui::IsKeyDown(ImGuiKey_RightShift)) &&
            ImGui::IsKeyPressed(ImGuiKey_Z))
        {
            if (ActionMgr::instance()->canUndo())
                undo();
        }
        else if (((ImGui::IsKeyDown(ImGuiKey_LeftShift) || ImGui::IsKeyDown(ImGuiKey_RightShift)) &&
                  ImGui::IsKeyPressed(ImGuiKey_Z)) ||
                 ImGui::IsKeyPressed(ImGuiKey_Y))
        {
            if (ActionMgr::instance()->canRedo())
                redo();
        }
        else if (ImGui::IsKeyPressed(ImGuiKey_C))
        {
            if (hasSelection())
                copySelection();
        }
        else if (ImGui::IsKeyPressed(ImGuiKey_X))
        {
            if (hasSelection())
                cutSelection();
        }
        else if (ImGui::IsKeyPressed(ImGuiKey_V))
        {
            if (hasClipboard())
                pasteClipboard();
        }
        else if (ImGui::IsKeyPressed(ImGuiKey_1))
        {
            mLayerShown[LAYER_0] ^= 1;
        }
        else if (ImGui::IsKeyPressed(ImGuiKey_2))
        {
            mLayerShown[LAYER_1] ^= 1;
        }
        else if (ImGui::IsKeyPressed(ImGuiKey_3))
        {
            mLayerShown[LAYER_2] ^= 1;
        }
        else if (ImGui::IsKeyPressed(ImGuiKey_4))
        {
            mActorShown ^= 1;
        }
        else if (ImGui::IsKeyPressed(ImGuiKey_5))
        {
            if (mActorShown)
                mActorGraphicsShown ^= 1;
        }
        else if (ImGui::IsKeyPressed(ImGuiKey_6))
        {
            mNextGotoShown ^= 1;
        }
        else if (ImGui::IsKeyPressed(ImGuiKey_7))
        {
            mLocationShown ^= 1;
        }
    }
    else if (ImGui::IsKeyPressed(ImGuiKey_Delete) ||
             ImGui::IsKeyPressed(ImGuiKey_Backspace))
    {
        if (hasSelection())
            deleteSelection();
    }
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

    CursorReleaseFlag cursor_release_flag = mCursorForceReleaseFlag;
    mCursorForceReleaseFlag = CURSOR_RELEASE_FLAG_NONE;

    if (mCursorState == CURSOR_STATE_RELEASE)
    {
        switch (mCursorButtonCurrent)
        {
        default:
            break;
        case CURSOR_BUTTON_L:
            cursor_release_flag |= CURSOR_RELEASE_FLAG_L;
            mCursorButtonCurrent = CURSOR_BUTTON_NONE;
            break;
        case CURSOR_BUTTON_R:
            cursor_release_flag |= CURSOR_RELEASE_FLAG_R;
            mCursorButtonCurrent = CURSOR_BUTTON_NONE;
            break;
        }
    }

    if (cursor_release_flag & CURSOR_RELEASE_FLAG_L)
        onCursorRelease_L_();

    if (cursor_release_flag & CURSOR_RELEASE_FLAG_R)
        onCursorRelease_R_();

    switch (mCursorState)
    {
    case CURSOR_STATE_PRESS:
        switch (mCursorButtonCurrent)
        {
        default:
            break;
        case CURSOR_BUTTON_L:
            onCursorPress_L_();
            break;
        case CURSOR_BUTTON_R:
            onCursorPress_R_();
            break;
        }
        break;
    case CURSOR_STATE_HOLD:
        switch (mCursorButtonCurrent)
        {
        default:
            break;
        case CURSOR_BUTTON_L:
            onCursorHold_L_();
            break;
        case CURSOR_BUTTON_R:
            onCursorHold_R_();
            break;
        }
        break;
  //case CURSOR_STATE_RELEASE:
    default:
        onCursorReleasedCompletely_();
        break;
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
    if (Globals::applyDistantViewScissor())
        calcDistantViewScissor_();

    if (mDrawDV)
        DistantViewMgr::instance()->draw(getDistantViewLayer());

    if (mActorShown && mActorGraphicsShown)
    {
        Renderer::instance()->setLayer(get3DLayer());
        {
            for (std::unique_ptr<MapActorItem>& p_item : mMapActorItemPtr)
                if (p_item->hasGraphics())
                    p_item->scheduleDraw();
        }
        Renderer::instance()->resetLayer();
    }

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

void CourseView::insertItem(const ItemID& item_id, const void* data)
{
    clearSelection();

    switch (item_id.getType())
    {
    default:
        break;
    case ITEM_TYPE_BG_UNIT_OBJ:
        {
            u8 layer = item_id.getIndex() >> 22;
            u32 i = item_id.getIndex() & 0x003FFFFF;
            const BgCourseData& data_ = *static_cast<const BgCourseData*>(data);

            std::vector<BgCourseData>& data_vec = mpCourseDataFile->getBgData(layer);
            std::vector<BgUnitItem>& item_vec = mBgUnitItem[layer];
            RIO_ASSERT(data_vec.size() == item_vec.size());

            data_vec.insert(data_vec.begin() + i, data_);
            item_vec.emplace(item_vec.begin() + i, data_, layer << 22 | i);
            RIO_ASSERT(data_vec.size() == item_vec.size());

            for (u32 j = i + 1; j < item_vec.size(); j++)
                item_vec[j].setIndex(layer << 22 | j);
        }
        break;
    case ITEM_TYPE_MAP_ACTOR:
        {
            u32 i = item_id.getIndex();
            const MapActorData& data_ = *static_cast<const MapActorData*>(data);

            std::vector<MapActorData>& data_vec = mpCourseDataFile->getMapActorData();
            RIO_ASSERT(data_vec.size() == mMapActorItemPtr.size());

            data_vec.insert(data_vec.begin() + i, data_);
            mMapActorItemPtr.emplace(mMapActorItemPtr.begin() + i, ActorCreateMgr::instance()->create(data_, i));
            RIO_ASSERT(data_vec.size() == mMapActorItemPtr.size());

            for (u32 j = i + 1; j < mMapActorItemPtr.size(); j++)
                mMapActorItemPtr[j]->setIndex(j);
        }
        break;
    case ITEM_TYPE_NEXT_GOTO:
        {
            u32 i = item_id.getIndex();
            const NextGoto& data_ = *static_cast<const NextGoto*>(data);

            std::vector<NextGoto>& data_vec = mpCourseDataFile->getNextGoto();
            RIO_ASSERT(data_vec.size() == mNextGotoItem.size());

            data_vec.insert(data_vec.begin() + i, data_);
            mNextGotoItem.emplace(mNextGotoItem.begin() + i, data_, i);
            RIO_ASSERT(data_vec.size() == mNextGotoItem.size());

            for (u32 j = i + 1; j < mNextGotoItem.size(); j++)
                mNextGotoItem[j].setIndex(j);
        }
        break;
    case ITEM_TYPE_LOCATION:
        {
            u32 i = item_id.getIndex();
            const Location& data_ = *static_cast<const Location*>(data);

            std::vector<Location>& data_vec = mpCourseDataFile->getLocation();
            RIO_ASSERT(data_vec.size() == mLocationItem.size());

            data_vec.insert(data_vec.begin() + i, data_);
            mLocationItem.emplace(mLocationItem.begin() + i, data_, i);
            RIO_ASSERT(data_vec.size() == mLocationItem.size());

            for (u32 j = i + 1; j < mLocationItem.size(); j++)
                mLocationItem[j].setIndex(j);
        }
        break;
    }
}

void CourseView::eraseItem(const ItemID& item_id)
{
    clearSelection();

    switch (item_id.getType())
    {
    default:
        break;
    case ITEM_TYPE_BG_UNIT_OBJ:
        {
            u8 layer = item_id.getIndex() >> 22;
            u32 i = item_id.getIndex() & 0x003FFFFF;

            std::vector<BgCourseData>& data_vec = mpCourseDataFile->getBgData(layer);
            std::vector<BgUnitItem>& item_vec = mBgUnitItem[layer];
            RIO_ASSERT(data_vec.size() == item_vec.size());

            item_vec.erase(item_vec.begin() + i);
            data_vec.erase(data_vec.begin() + i);
            RIO_ASSERT(data_vec.size() == item_vec.size());

            for (u32 j = i; j < item_vec.size(); j++)
                item_vec[j].setIndex(layer << 22 | j);
        }
        break;
    case ITEM_TYPE_MAP_ACTOR:
        {
            u32 i = item_id.getIndex();

            std::vector<MapActorData>& data_vec = mpCourseDataFile->getMapActorData();
            RIO_ASSERT(data_vec.size() == mMapActorItemPtr.size());

            mMapActorItemPtr.erase(mMapActorItemPtr.begin() + i);
            data_vec.erase(data_vec.begin() + i);
            RIO_ASSERT(data_vec.size() == mMapActorItemPtr.size());

            for (u32 j = i; j < mMapActorItemPtr.size(); j++)
                mMapActorItemPtr[j]->setIndex(j);
        }
        break;
    case ITEM_TYPE_NEXT_GOTO:
        {
            u32 i = item_id.getIndex();

            std::vector<NextGoto>& data_vec = mpCourseDataFile->getNextGoto();
            RIO_ASSERT(data_vec.size() == mNextGotoItem.size());

            mNextGotoItem.erase(mNextGotoItem.begin() + i);
            data_vec.erase(data_vec.begin() + i);
            RIO_ASSERT(data_vec.size() == mNextGotoItem.size());

            for (u32 j = i; j < mNextGotoItem.size(); j++)
                mNextGotoItem[j].setIndex(j);
        }
        break;
    case ITEM_TYPE_LOCATION:
        {
            u32 i = item_id.getIndex();

            std::vector<Location>& data_vec = mpCourseDataFile->getLocation();
            RIO_ASSERT(data_vec.size() == mLocationItem.size());

            mLocationItem.erase(mLocationItem.begin() + i);
            data_vec.erase(data_vec.begin() + i);
            RIO_ASSERT(data_vec.size() == mLocationItem.size());

            for (u32 j = i; j < mLocationItem.size(); j++)
                mLocationItem[j].setIndex(j);
        }
        break;
    }
}

void CourseView::deleteSelection()
{
    if (mSelectedItems.empty())
        return;

    ActionItemDelete::Context context;
    for (const ItemID& item_id : mSelectedItems)
    {
        switch (item_id.getType())
        {
        default:
            break;
        case ITEM_TYPE_BG_UNIT_OBJ:
            context.items.emplace_back(item_id, std::static_pointer_cast<const void>(
                std::make_shared<BgCourseData>(
                    mpCourseDataFile->getBgData(item_id.getIndex() >> 22)[item_id.getIndex() & 0x003FFFFF]
                )
            ));
            break;
        case ITEM_TYPE_MAP_ACTOR:
            context.items.emplace_back(item_id, std::static_pointer_cast<const void>(
                std::make_shared<MapActorData>(
                    mpCourseDataFile->getMapActorData()[item_id.getIndex()]
                )
            ));
            break;
        case ITEM_TYPE_NEXT_GOTO:
            context.items.emplace_back(item_id, std::static_pointer_cast<const void>(
                std::make_shared<NextGoto>(
                    mpCourseDataFile->getNextGoto()[item_id.getIndex()]
                )
            ));
            break;
        case ITEM_TYPE_LOCATION:
            context.items.emplace_back(item_id, std::static_pointer_cast<const void>(
                std::make_shared<Location>(
                    mpCourseDataFile->getLocation()[item_id.getIndex()]
                )
            ));
            break;
        }
    }
    ActionMgr::instance()->pushAction<ActionItemDelete>(&context);
}

void CourseView::copySelection()
{
    clearClipboard();

    if (mSelectedItems.empty())
        return;

    const rio::BaseVec2f& center_pos = getCenterWorldPos();
    s32 center_unit_x =  center_pos.x / 16;
    s32 center_unit_y = -center_pos.y / 16;

    std::shared_ptr<ActionItemPushBack::Context> context = std::make_shared<ActionItemPushBack::Context>();
    context->transform = true;
    context->center_unit_x = center_unit_x;
    context->center_unit_y = center_unit_y;

    for (const ItemID& item_id : mSelectedItems)
    {
        switch (item_id.getType())
        {
        default:
            break;
        case ITEM_TYPE_BG_UNIT_OBJ:
            context->items.emplace_back(ITEM_TYPE_BG_UNIT_OBJ, std::static_pointer_cast<const void>(
                std::make_shared<BgCourseData>(
                    mpCourseDataFile->getBgData(item_id.getIndex() >> 22)[item_id.getIndex() & 0x003FFFFF]
                )
            ), std::static_pointer_cast<const void>(
                std::make_shared<u8>(item_id.getIndex() >> 22)
            ));
            break;
        case ITEM_TYPE_MAP_ACTOR:
            context->items.emplace_back(ITEM_TYPE_MAP_ACTOR, std::static_pointer_cast<const void>(
                std::make_shared<MapActorData>(
                    mpCourseDataFile->getMapActorData()[item_id.getIndex()]
                )
            ));
            break;
        case ITEM_TYPE_NEXT_GOTO:
            context->items.emplace_back(ITEM_TYPE_NEXT_GOTO, std::static_pointer_cast<const void>(
                std::make_shared<NextGoto>(
                    mpCourseDataFile->getNextGoto()[item_id.getIndex()]
                )
            ));
            break;
        case ITEM_TYPE_LOCATION:
            context->items.emplace_back(ITEM_TYPE_LOCATION, std::static_pointer_cast<const void>(
                std::make_shared<Location>(
                    mpCourseDataFile->getLocation()[item_id.getIndex()]
                )
            ));
            break;
        }
    }

    mClipboard.type = CLIPBOARD_TYPE_ITEMS;
    mClipboard.data = std::static_pointer_cast<const void>(context);
}

void CourseView::pasteClipboard()
{
    switch (mClipboard.type)
    {
    default:
        break;
    case CLIPBOARD_TYPE_ITEMS:
        clearSelection();
        ActionMgr::instance()->pushAction<ActionItemPushBack>(mClipboard.data.get());
        break;
    }
}

void CourseView::setItemSelection_(const ItemID& item_id, bool is_selected)
{
    switch (item_id.getType())
    {
    default:
        break;
    case ITEM_TYPE_BG_UNIT_OBJ:
        mBgUnitItem[item_id.getIndex() >> 22][item_id.getIndex() & 0x003FFFFF].setSelection(is_selected);
        break;
    case ITEM_TYPE_MAP_ACTOR:
        mMapActorItemPtr[item_id.getIndex()]->setSelection(is_selected);
        break;
    case ITEM_TYPE_NEXT_GOTO:
        mNextGotoItem[item_id.getIndex()].setSelection(is_selected);
        break;
    case ITEM_TYPE_LOCATION:
        mLocationItem[item_id.getIndex()].setSelection(is_selected);
        break;
    }
}

void CourseView::clearSelection_()
{
    if (mSelectedItems.empty())
        return;

    for (const ItemID& item_id : mSelectedItems)
        setItemSelection_(item_id, false);

    mSelectedItems.clear();
    mSelectionChange = true;
}

void CourseView::selectItem(const ItemID& item_id)
{
    clearSelection_();
    mSelectedItems.push_back(item_id);
    mSelectionChange = true;
    setItemSelection_(item_id, true);
}

void CourseView::onSelectionChange_()
{
    BgRenderer::instance()->calcSelectionVertexBuffer(mSelectedItems);
}

void CourseView::drawSelectionBox_()
{
    const rio::BaseVec2f& p1 = viewToWorldPos(mCursorP1);
    const rio::BaseVec2f& p2 = viewToWorldPos(mCursorPos);

    const rio::Vector2f min {
        std::min(p1.x, p2.x),
        std::min(p1.y, p2.y)
    };

    const rio::Vector2f max {
        std::max(p1.x, p2.x),
        std::max(p1.y, p2.y)
    };

    QuadRenderer::instance()->drawQuad(
        QuadRenderer::Arg(rio::Color4f{ 0.25f, 0.25f, 1.0f, 0.375f })
            .setCornerAndSize({ min.x, min.y, -mProjection.getNear() + 10000.0f }, max - min)
    );
    QuadRenderer::instance()->drawBox(
        QuadRenderer::Arg(rio::Color4f{ 0.25f, 0.25f, 1.0f, 1.0f })
            .setCornerAndSize({ min.x, min.y, -mProjection.getNear() + 10000.0f }, max - min)
    );
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
    mCourseView.bindRenderBuffer_(false);
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
    if (Globals::applyDistantViewScissor())
        mCourseView.mRenderBuffer.resetScissor();

    mCourseView.mpColorTexture->setCompMap(0x00010203);
    mCourseView.bindRenderBuffer_(true);
}

void CourseView::DrawCallback3D::preDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
}

void CourseView::DrawCallback3D::postDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
    QuadRenderer::instance()->setViewProjMtx(mCourseView.mCamera, mCourseView.mProjection);

    rio::RenderState render_state;
    render_state.setBlendEnable(false);
    render_state.apply();

    if (mCourseView.mpCourseDataFile != nullptr)
    {
        if (mCourseView.mActorShown)
        {
            std::vector< std::unique_ptr<MapActorItem> >& map_actor_item_vec = mCourseView.mMapActorItemPtr;
            const std::vector<MapActorData>& map_actor_data_vec = mCourseView.mpCourseDataFile->getMapActorData();

            for (u32 i = 0; i < map_actor_item_vec.size(); i++)
                if (map_actor_data_vec[i].layer != LAYER_1)
                    map_actor_item_vec[i]->drawOpa(draw_info);

            for (u32 i = 0; i < map_actor_item_vec.size(); i++)
                if (map_actor_data_vec[i].layer == LAYER_1)
                    map_actor_item_vec[i]->drawOpa(draw_info);
        }

        if (mCourseView.mNextGotoShown)
            for (NextGotoItem& item : mCourseView.mNextGotoItem)
                item.drawOpa();

        if (mCourseView.mLocationShown)
            for (LocationItem& item : mCourseView.mLocationItem)
                item.drawOpa();

        for (AreaItem& item : mCourseView.mAreaItem)
            item.drawOpa();
    }
}

void CourseView::DrawCallback3D::postDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
    QuadRenderer::instance()->setViewProjMtx(mCourseView.mCamera, mCourseView.mProjection);

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

        bg_renderer.render(LAYER_2, cd_file, layer_shown[LAYER_2]);

        if (mCourseView.mActorShown)
        {
            std::vector< std::unique_ptr<MapActorItem> >& map_actor_item_vec = mCourseView.mMapActorItemPtr;
            const std::vector<MapActorData>& map_actor_data_vec = mCourseView.mpCourseDataFile->getMapActorData();

            for (u32 i = 0; i < map_actor_item_vec.size(); i++)
                if (map_actor_data_vec[i].layer != LAYER_1)
                    map_actor_item_vec[i]->drawXlu(draw_info);

            bg_renderer.render(LAYER_1, cd_file, layer_shown[LAYER_1]);

            for (u32 i = 0; i < map_actor_item_vec.size(); i++)
                if (map_actor_data_vec[i].layer == LAYER_1)
                    map_actor_item_vec[i]->drawXlu(draw_info);
        }
        else
        {
            bg_renderer.render(LAYER_1, cd_file, layer_shown[LAYER_1]);
        }

        if (mCourseView.mNextGotoShown)
            for (NextGotoItem& item : mCourseView.mNextGotoItem)
                item.drawXlu();

        if (mCourseView.mLocationShown)
            for (LocationItem& item : mCourseView.mLocationItem)
                item.drawXlu();

        bg_renderer.render(LAYER_0, cd_file, layer_shown[LAYER_0]);

        for (AreaItem& item : mCourseView.mAreaItem)
            item.drawXlu();
    }

    mCourseView.bindRenderBuffer_(false);

    if (mCourseView.mCursorAction == CURSOR_ACTION_SELECTION_BOX)
        mCourseView.drawSelectionBox_();

    mCourseView.unbindRenderBuffer_();
}

void CourseView::drawSelectionUI()
{
    if (mSelectedItems.empty())
        return;

    if (ImGui::Begin("Selection", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing))
    {
        const ItemID& selected_item = mSelectedItems[0];

        if (mSelectedItems.size() > 1)
        {
            ImGui::Text("%d item(s) selected.\nUnable to edit the selected items.", mSelectedItems.size());
        }
        else
        {
            switch (selected_item.getType())
            {
            default:
                ImGui::Text("Unknown item selected.");
                break;
            case ITEM_TYPE_BG_UNIT_OBJ:
                mBgUnitItem[selected_item.getIndex() >> 22][selected_item.getIndex() & 0x003FFFFF].drawSelectionUI();
                break;
            case ITEM_TYPE_MAP_ACTOR:
                mMapActorItemPtr[selected_item.getIndex()]->drawSelectionUI();
                break;
            case ITEM_TYPE_NEXT_GOTO:
                mNextGotoItem[selected_item.getIndex()].drawSelectionUI();
                break;
            case ITEM_TYPE_LOCATION:
                mLocationItem[selected_item.getIndex()].drawSelectionUI();
                break;
            }
        }
    }
    ImGui::End();
}
