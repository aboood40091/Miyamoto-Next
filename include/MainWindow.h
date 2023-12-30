#pragma once

#include <graphics/RenderMgr.h>
#include <graphics/RenderObjLayer.h>
#include <item/ItemType.h>
#include <resource/SharcArchiveRes.h>

#include <task/rio_Task.h>

#if RIO_IS_CAFE
#include <imgui_impl_gx2.h>
#endif // RIO_IS_CAFE

class CourseView;

class MainWindow : public rio::ITask, public rio::lyr::IDrawable
{
public:
    MainWindow();

    RenderObjLayer* getBgPrepareLayer() const
    {
        return static_cast<RenderObjLayer*>(mLayerBgPrepare.ptr);
    }

    void courseNew();
    void courseOpen();
    void courseSave();
    void courseSaveAs();
    void courseItemSelect();

private:
    void prepare_() override;
    void calc_()    override;
    void exit_()    override;

#if RIO_IS_WIN
    void resize_(s32 width, s32 height);
    static void onResizeCallback_(s32 width, s32 height);
#endif // RIO_IS_WIN

    void courseNew_();
    void courseOpen_();
    void courseFileSwitch_(u32 file_index);

    void handlePopupCallback_();

    void setCurrentCourseDataFile_(u32 id);

    void processMouseInput_();
    void processKeyboardInput_();

    void drawMetricsUI_();
    void drawCourseViewUI_();
    void drawPaletteUI_();
    void drawSelectionUI_();
    void drawMainMenuBarUI_();
    void drawFileOptionsUI_();
    void drawFileOptionsMenuItemUI_();

    void gather_ (const rio::lyr::DrawInfo&);
    void dispose_(const rio::lyr::DrawInfo&);

private:
    struct Layer
    {
        Layer()
            : ptr(nullptr)
        {
        }

        rio::lyr::Layer::iterator it;
        rio::lyr::Layer* ptr;
    } mLayerGather, mLayerDispose, mLayerBgPrepare;

    struct Sharc
    {
        Sharc()
            : p_archive(nullptr)
        {
        }

        void* p_archive;
        SharcArchiveRes archive_res;
    } mAglRes, mJyotyuActorPack, mCobPack;

    enum PopupType
    {
        POPUP_TYPE_NONE = 0,
        POPUP_TYPE_SETTINGS = 0,
        POPUP_TYPE_ACTION_DISCARD,
        POPUP_TYPE_SAVE,
        POPUP_TYPE_SELECT
    };

    enum PopupCallbackType
    {
        POPUP_CALLBACK_TYPE_NONE = 0,
        POPUP_CALLBACK_TYPE_COURSE_NEW,
        POPUP_CALLBACK_TYPE_COURSE_OPEN,
        POPUP_CALLBACK_TYPE_COURSE_FILE_SWITCH,
        POPUP_CALLBACK_TYPE_COURSE_ITEM_SELECT
    };

    CourseView*             mpCourseView;
    rio::BaseVec2f          mCourseViewPos;
    rio::BaseVec2i          mCourseViewSize;
    bool                    mCourseViewResized;
    bool                    mCourseViewHovered;
    bool                    mCourseViewFocused;
    bool                    mCourseViewCameraMoved;
    RenderMgr               mRenderMgrBgPrepare;
    std::string             mCoursePath;
    u32                     mCurrentFile;
    ItemType                mPaintType;
    u16                     mEnvSelectedObj;
    s32                     mEnvPaintLayer;
    u16                     mMapActorSelectedType;
    bool                    mPopupOpen;
    PopupType               mPopupType;
    PopupCallbackType       mPopupCallbackType;
    u32                     mNextFile;
    u32                     mItemSelectFlag;
    s32                     mMetricsLocation;
#if RIO_IS_CAFE
    ImGui_ImplGX2_Texture   mImGuiGX2Texture;
    GX2Sampler              mGX2Sampler;
#endif // RIO_IS_CAFE
};
