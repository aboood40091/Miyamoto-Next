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
struct  BgCourseData;
class   BgUnitItem;
class   AreaItem;
class   CourseDataFile;
struct  Location;
class   LocationItem;
struct  MapActorData;
class   MapActorItem;
struct  NextGoto;
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
        CURSOR_ACTION_NONE = 0,
        CURSOR_ACTION_MOVE_ITEM,
        CURSOR_ACTION_SELECTION_BOX
    };

    enum CursorButton
    {
        CURSOR_BUTTON_NONE = 0,
        CURSOR_BUTTON_L,
        CURSOR_BUTTON_R
    };

    enum CursorState
    {
        CURSOR_STATE_RELEASE,
        CURSOR_STATE_PRESS,
        CURSOR_STATE_HOLD
    };

    enum CursorReleaseFlag
    {
        CURSOR_RELEASE_FLAG_NONE    = 0,
        CURSOR_RELEASE_FLAG_L       = 1 << 0,
        CURSOR_RELEASE_FLAG_R       = 1 << 1,
        CURSOR_RELEASE_FLAG_ALL     = CURSOR_RELEASE_FLAG_L | CURSOR_RELEASE_FLAG_R
    };

    friend CursorReleaseFlag operator|(const CursorReleaseFlag& lhs, const CursorReleaseFlag& rhs)
    {
        return (CursorReleaseFlag)((u32)lhs | (u32)rhs);
    }

    friend CursorReleaseFlag& operator|=(CursorReleaseFlag& lhs, const CursorReleaseFlag& rhs)
    {
        lhs = lhs | rhs;
        return lhs;
    }

    struct PaintContext
    {
        ItemType    type;

        // BgUnitItem
        u8          layer;
        u16         bg_unit_obj_type;

        // MapActorItem
        u16         map_actor_id;

        // ...

        PaintContext()
            : type(ITEM_TYPE_MAX_NUM)
        {
        }
    };

    enum ClipboardType
    {
        CLIPBOARD_TYPE_NONE = 0,
        CLIPBOARD_TYPE_ITEMS
    };

    struct Clipboard
    {
        ClipboardType               type;
        std::shared_ptr<const void> data;

        Clipboard()
            : type(CLIPBOARD_TYPE_NONE)
            , data(nullptr)
        {
        }
    };

public:
    static bool createSingleton(s32 width, s32 height, const rio::BaseVec2f& window_pos);
    static void destroySingleton();
    static CourseView* instance() { return sInstance; }

private:
    static CourseView* sInstance;

    CourseView(s32 width, s32 height, const rio::BaseVec2f& window_pos);
    ~CourseView();

    CourseView(const CourseView&);
    CourseView& operator=(const CourseView&);

public:
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

    rio::BaseVec2f getCenterPos() const
    {
        return mSize * 0.5f;
    }

    rio::BaseVec2f getCenterWorldPos() const
    {
        return viewToWorldPos(mSize * 0.5f);
    }

    const rio::Texture2D* getColorTexture() const
    {
        return mpColorTexture;
    }

    void drawSelectionUI();

    void resize(s32 width, s32 height, bool preserve_unit_size = false);

    rio::BaseVec2f viewToWorldPos(const rio::BaseVec2f& pos) const;
    rio::BaseVec2f worldToViewPos(const rio::BaseVec2f& pos) const;

    void initialize(CourseDataFile& cd_file, bool real_zoom);
    void uninitialize();

    bool isInitialized() const
    {
        return mpCourseDataFile != nullptr;
    }

    CourseDataFile& getCourseDataFile()
    {
        RIO_ASSERT(isInitialized());
        return *mpCourseDataFile;
    }

    const CourseDataFile& getCourseDataFile() const
    {
        RIO_ASSERT(isInitialized());
        return *mpCourseDataFile;
    }

    bool hasSelection() const
    {
        return !mSelectedItems.empty();
    }

    void clearSelection()
    {
        releaseCursorNow();
        clearSelection_();
    }

    bool hasClipboard() const
    {
        return mClipboard.type != CLIPBOARD_TYPE_NONE;
    }

    void clearClipboard()
    {
        mClipboard.type = CLIPBOARD_TYPE_NONE;
        mClipboard.data = nullptr;
    }

    void cutSelection()
    {
        copySelection();
        deleteSelection();
    }

    void setPaintType_None()
    {
        mPaintNext.type = ITEM_TYPE_MAX_NUM;
    }

    void setPaintType_BgUnitObj(u8 layer, u16 bg_unit_obj_type)
    {
        RIO_ASSERT(layer < CD_FILE_LAYER_MAX_NUM);
        RIO_ASSERT(bg_unit_obj_type < 0x3fff);

        mPaintNext.type = ITEM_TYPE_BG_UNIT_OBJ;
        mPaintNext.layer = layer;
        mPaintNext.bg_unit_obj_type = bg_unit_obj_type;
    }

    void setPaintType_MapActor(u16 map_actor_id)
    {
        mPaintNext.type = ITEM_TYPE_MAP_ACTOR;
        mPaintNext.map_actor_id = map_actor_id;
    }

    void setPaintType_NextGoto()
    {
        mPaintNext.type = ITEM_TYPE_NEXT_GOTO;
    }

    void setPaintType_Location()
    {
        mPaintNext.type = ITEM_TYPE_LOCATION;
    }

    const std::vector< std::unique_ptr<MapActorItem> >& getMapActorItem() const
    {
        return mMapActorItemPtr;
    }

    const std::vector<LocationItem>& getLocationItem() const
    {
        return mLocationItem;
    }

    const std::vector<NextGotoItem>& getNextGotoItem() const
    {
        return mNextGotoItem;
    }

    bool* getLayerVisibility(u8 layer)
    {
        return &(mLayerShown[layer]);
    }

    bool* getActorVisibility()
    {
        return &mActorShown;
    }

    bool* getActorGraphicsEnable()
    {
        return &mActorGraphicsShown;
    }

    bool* getNextGotoVisibility()
    {
        return &mNextGotoShown;
    }

    bool* getLocationVisibility()
    {
        return &mLocationShown;
    }

    void setCursorForceReleaseOnNextUpdate(CursorReleaseFlag flag)
    {
        mCursorForceReleaseFlag |= flag;
    }

    void releaseCursorNow(CursorReleaseFlag flag = CURSOR_RELEASE_FLAG_ALL)
    {
        if (flag & CURSOR_RELEASE_FLAG_L)
            onCursorRelease_L_();

        if (flag & CURSOR_RELEASE_FLAG_R)
            onCursorRelease_R_();
    }

    void setCameraCenterWorldPos(const rio::BaseVec2f& center_pos);

    void updateCursorPos(const rio::BaseVec2f& window_pos);
    bool processMouseInput(bool focused, bool hovered);
    void processKeyboardInput();

    void update();

    void gather();
    void dispose();

    void undo();
    void redo();

    void moveItems(const std::vector<ItemID>& items, s16 dx, s16 dy, bool commit);
    void setItemData(const ItemID& item_id, const void* data, u32 data_change_flag);

    void pushBackItem(ItemType item_type, const void* data, const void* extra);
    void pushBackItemWithTransform(s32 dx, s32 dy, ItemType item_type, const void* data, const void* extra);
    void popBackItem(ItemType item_type, const void* extra);

    void insertItem(const ItemID& item_id, const void* data);
    void eraseItem(const ItemID& item_id);

    void deleteSelection();
    void copySelection();
    void pasteClipboard();

    void selectItem(const ItemID& item_id);

private:
    void createRenderBuffer_(s32 width, s32 height);
    void bindRenderBuffer_(bool with_item_id);
    void unbindRenderBuffer_();
    void clearItemIDTexture_();

    void onCursorPress_L_();
    void onCursorHold_L_();
    void onCursorRelease_L_();

    void onCursorPress_R_();
    void onCursorHold_R_();
    void onCursorRelease_R_();

    void moveItems_(bool commit);
    void onCursorHold_MoveItem_();
    void onCursorRelease_MoveItem_();

    void onCursorRelease_SelectionBox_();

    void pushBackItem_BgUnitObj_(const BgCourseData& data, u8 layer);
    void popBackItem_BgUnitObj_(u8 layer);

    void pushBackItem_MapActor_(const MapActorData& data);
    void popBackItem_MapActor_();

    void pushBackItem_NextGoto_(const NextGoto& data);
    void popBackItem_NextGoto_();

    void pushBackItem_Location_(const Location& data);
    void popBackItem_Location_();

    void onCursorPress_Paint_BgUnitObj_();
    void onCursorHold_Paint_BgUnitObj_();
    void onCursorRelease_Paint_BgUnitObj_();

    void onCursorPress_Paint_MapActor_();
    void onCursorHold_Paint_MapActor_();
    void onCursorRelease_Paint_MapActor_();

    void onCursorPress_Paint_NextGoto_();
    void onCursorHold_Paint_NextGoto_();
    void onCursorRelease_Paint_NextGoto_();

    void onCursorPress_Paint_Location_();
    void onCursorHold_Paint_Location_();
    void onCursorRelease_Paint_Location_();

    void onCursorReleasedCompletely_();

    void setItemSelection_(const ItemID& item_id, bool is_selected);
    void clearSelection_();
    void onSelectionChange_();
    void drawSelectionBox_();

    s32 findNearestArea_(s32 x, s32 y);

    void calcDistantViewScissor_();
    void dv_PostFx_(const rio::lyr::DrawInfo& draw_info);

private:
    bool                        mIsFocused,
                                mIsHovered;
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
    PaintContext                mPaintCurrent,
                                mPaintNext;
    rio::Vector2f               mCursorPos;
    CursorAction                mCursorAction;
    CursorButton                mCursorButtonCurrent;
    CursorState                 mCursorState;
    CursorReleaseFlag           mCursorForceReleaseFlag;
    bool                        mSelectionChange;
    rio::Vector2f               mCursorP1;
    rio::Vector2i               mCursorP1World;
    Clipboard                   mClipboard;
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
    bool                        mDrawDV,
                                mLayerShown[CD_FILE_LAYER_MAX_NUM],
                                mActorShown,
                                mActorGraphicsShown,
                                mNextGotoShown,
                                mLocationShown;

    enum RenderTargetColorType
    {
        TARGET_TYPE_COLOR   = 0,
        TARGET_TYPE_NORMAL  = 1,    // Currently not used by Miyamoto Next
        TARGET_TYPE_ITEM_ID = 2
    };
};
