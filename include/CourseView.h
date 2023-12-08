#pragma once

#include <course/Constants.h>
#include <graphics/OrthoCamera.h>
#include <graphics/RenderMgr.h>
#include <graphics/RenderObjLayer.h>
#include <item/ItemID.h>

#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <gpu/rio_RenderBuffer.h>
#include <gpu/rio_RenderTarget.h>

#include <array>
#include <memory>

struct  AreaData;
class   BgUnitItem;
class   AreaItem;
class   CourseDataFile;
class   LocationItem;
class   MapActorItem;
class   NextGotoItem;

class CourseView : public rio::lyr::IDrawable
{
private:
    class DrawCallback3D : public RenderMgr::CallbackBase
    {
    public:
        DrawCallback3D(CourseView& course_view)
            : mCourseView(course_view)
        {
        }

        void preDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info) override;
        void preDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info) override;
        void postDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info) override;
        void postDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info) override;

    private:
        CourseView& mCourseView;
    };

    class DrawCallbackDV : public RenderMgr::CallbackBase
    {
    public:
        DrawCallbackDV(CourseView& course_view)
            : mCourseView(course_view)
        {
        }

        void preDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info) override;
        void preDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info) override;
        void postDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info) override;
        void postDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info) override;

    private:
        CourseView& mCourseView;
    };

    enum CursorAction
    {
        CURSOR_ACTION_NONE,
        CURSOR_ACTION_MOVE_ITEM,
        CURSOR_ACTION_SELECTION_BOX
    };

public:
    CourseView(s32 width, s32 height, const rio::BaseVec2f& window_pos);
    ~CourseView();

    void setZoom(f32 zoom)
    {
        mBgZoom = zoom;
        mCamera.setZoomScale(mSize.y / (zoom * 224.0f));
    }

    template <typename T>
    inline void setZoomUnitSize(T unit_size)
    {
        setZoom(16.f / unit_size * (mSize.y / 224.0f));
    }

    f32 getZoomUnitSize() const
    {
        return mCamera.getZoomScale() * 16.f;
    }

    RenderObjLayer* getDistantViewLayer()
    {
        return static_cast<RenderObjLayer*>(mpLayerDV);
    }

    const RenderObjLayer* getDistantViewLayer() const
    {
        return static_cast<const RenderObjLayer*>(mpLayerDV);
    }

    RenderObjLayer* get3DLayer()
    {
        return static_cast<RenderObjLayer*>(mpLayer3D);
    }

    const RenderObjLayer* get3DLayer() const
    {
        return static_cast<const RenderObjLayer*>(mpLayer3D);
    }

    const rio::BaseVec2f& getCursorPos() const
    {
        return mCursorPos;
    }

    rio::BaseVec2f getCursorWorldPos() const
    {
        return viewToWorldPos(mCursorPos);
    }

    const rio::Texture2D* getColorTexture() const
    {
        return mpColorTexture;
    }

    void drawSelectionUI();

    void resize(s32 width, s32 height, bool preserve_unit_size = false);

    rio::BaseVec2f viewToWorldPos(const rio::BaseVec2f& pos) const;
    rio::BaseVec2f worldToViewPos(const rio::BaseVec2f& pos) const;

    void initialize(CourseDataFile* p_cd_file, bool real_zoom);
    void reset()
    {
        initialize(nullptr, false);
    }

    CourseDataFile* getCourseDataFile()
    {
        return mpCourseDataFile;
    }

    const CourseDataFile* getCourseDataFile() const
    {
        return mpCourseDataFile;
    }

    void updateCursorPos(const rio::BaseVec2f& window_pos);
    bool processMouseInput(bool focused, bool hovered);
    void processKeyboardInput();

    void update();

    void gather();
    void dispose();

    void moveItems(const std::vector<ItemID>& items, s16 dx, s16 dy, bool commit);
    void setItemData(const ItemID& item_id, const void* data, u32 data_change_flag);

    void clearSelection()
    {
        clearSelection_();
        mCursorAction = CURSOR_ACTION_NONE;
    }

private:
    void createRenderBuffer_(s32 width, s32 height);
    void bindRenderBuffer_(bool with_item_id);
    void unbindRenderBuffer_();
    void clearItemIDTexture_();

    void moveItems_(bool commit);
    void onCursorMove_MoveItem_();
    void onCursorRelease_MoveItem_();

    void onCursorRelease_SelectionBox_();

    void setItemSelection_(const ItemID& item_id, bool is_selected);
    void clearSelection_();
    void onSelectionChange_();
    void drawSelectionBox_();

    void calcDistantViewScissor_();
    void dv_PostFx_(const rio::lyr::DrawInfo& draw_info);

private:
    rio::Vector2f               mSize;
    f32                         mAspect;
    OrthoCamera                 mCamera;
    rio::OrthoProjection        mProjection;
    DrawCallback3D              mDrawCallback3D;
    DrawCallbackDV              mDrawCallbackDV;
    RenderMgr                   mRenderMgr3D,
                                mRenderMgrDV;
    rio::lyr::Layer::iterator   mLayerItr3D,
                                mLayerItrDV;
    rio::lyr::Layer            *mpLayer3D,
                               *mpLayerDV;
    CourseDataFile*             mpCourseDataFile;
    const AreaData*             mpDVControlArea;
    f32                         mBgZoom,
                                mRealBgZoom;
    rio::Vector2f               mCursorPos;
    CursorAction                mCursorAction;
    bool                        mIsCursorPress;
    bool                        mIsCursorRelease;
    bool                        mSelectionChange;
    rio::Vector2f               mCursorP1;
    std::vector<ItemID>         mSelectedItems;
    std::array<std::vector<BgUnitItem>, CD_FILE_LAYER_MAX_NUM>
                                mBgUnitItem;
    std::vector<NextGotoItem>   mNextGotoItem;
    std::vector< std::unique_ptr<MapActorItem> >
                                mMapActorItemPtr;
    std::vector<AreaItem>       mAreaItem;
    std::vector<LocationItem>   mLocationItem;
    u8*                         mpItemIDReadBuffer;
#if RIO_IS_WIN
    u8*                         mpItemIDClearBuffer;
#endif // RIO_IS_WIN
    rio::Texture2D             *mpColorTexture,
                               *mpItemIDTexture,
                               *mpDepthTexture;
    rio::RenderTargetColor      mColorTarget;
    agl::RenderTargetColor      mColorTargetDV;
    rio::RenderTargetDepth      mDepthTarget;
    agl::RenderTargetDepth      mDepthTargetDV;
    rio::RenderTargetColor      mItemIDTarget;
    rio::RenderBuffer           mRenderBuffer;
    agl::RenderBuffer           mRenderBufferDV;
    bool                        mDrawDV;
    bool                        mLayerShown[CD_FILE_LAYER_MAX_NUM];

    enum RenderTargetColorType
    {
        TARGET_TYPE_COLOR   = 0,
        TARGET_TYPE_NORMAL  = 1,    // Currently not used by Miyamoto Next
        TARGET_TYPE_ITEM_ID = 2
    };
};
