#pragma once

#include <course/CourseData.h>
#include <course/BgRenderer.h>

#include <graphics/OrthoCamera.h>

#include <graphics/RenderMgr.h>
#include <graphics/RenderObjLayer.h>

#include <item/AreaItem.h>
#include <item/LocationItem.h>
#include <item/NextGotoItem.h>
#include <item/MapActorItem.h>

#include <resource/SharcArchiveRes.h>

#include <gfx/rio_Projection.h>
#include <gfx/lyr/rio_Layer.h>
#include <task/rio_Task.h>

class RenderObjLayer;

class MainWindow : public rio::ITask, public rio::lyr::IDrawable
{
public:
    static const std::string& getContentPath();

public:
    MainWindow();

    void setZoom(f32 zoom)
    {
        mBgZoom = zoom;
        mCamera.setZoomScale(/* s32(rio::Window::instance()->getHeight()) */ 720 / (zoom * 224.0f));
    }

    template <typename T>
    inline void setZoomTileSize(T tile_size)
    {
        setZoom(16.f / tile_size * (/* s32(rio::Window::instance()->getHeight()) */ 720 / 224.0f));
    }

    rio::Vector2f viewToWorldPos(const rio::Vector2f& pos) const;
    rio::Vector3f viewToWorldPos(const rio::Vector3f& pos) const;

    rio::BaseVec2f worldToScreenPos(const rio::BaseVec2f& pos) const;

    const rio::Vector2f& getCursorPos() const
    {
        return mCursorPos;
    }

    rio::Vector2f getCursorWorldPos() const
    {
        return viewToWorldPos(mCursorPos);
    }

    CourseDataFile* getCurrentCourseDataFile()
    {
        if (CourseData::instance() == nullptr || mCurrentFile == -1)
            return nullptr;

        return CourseData::instance()->getFile(mCurrentFile);
    }

    const CourseDataFile* getCurrentCourseDataFile() const
    {
        if (CourseData::instance() == nullptr || mCurrentFile == -1)
            return nullptr;

        return CourseData::instance()->getFile(mCurrentFile);
    }

    BgRenderer& getBgRenderer()
    {
        return mBgRenderer;
    }

    const BgRenderer& getBgRenderer() const
    {
        return mBgRenderer;
    }

    RenderObjLayer* getDistantViewLayer() const
    {
        return static_cast<RenderObjLayer*>(mLayer[SCENE_LAYER_DISTANT_VIEW].ptr);
    }

    RenderObjLayer* getBgPrepareLayer() const
    {
        return static_cast<RenderObjLayer*>(mLayer[SCENE_LAYER_BG_PREPARE].ptr);
    }

    RenderObjLayer* get3DLayer() const
    {
        return static_cast<RenderObjLayer*>(mLayer[SCENE_LAYER_3D].ptr);
    }

    void setCurrentCourseDataFile(u32 id);

private:
    void prepare_() override;
    void calc_()    override;
    void exit_()    override;

    void processInputs_();
    void updateCursorPos_();
    void drawCursor_();

    void calcDistantViewScissor_();

    void gather_ (const rio::lyr::DrawInfo&);
    void dispose_(const rio::lyr::DrawInfo&);

    void dv_PostFx_(const rio::lyr::DrawInfo& draw_info);

private:
    enum SceneLayer
    {
        SCENE_LAYER_DISPOSE = 0,
        SCENE_LAYER_3D,
        SCENE_LAYER_BG_PREPARE,
        SCENE_LAYER_DISTANT_VIEW,
        SCENE_LAYER_GATHER,
        SCENE_LAYER_NUM
    };

    class DrawCallback : public RenderMgr::CallbackBase
    {
    public:
        DrawCallback(MainWindow& window)
            : mWindow(window)
        {
        }

        void preDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info) override;
        void preDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info) override;
        void postDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info) override;
        void postDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info) override;

    private:
        MainWindow& mWindow;
    };

    struct
    {
        rio::lyr::Layer::iterator it;
        rio::lyr::Layer* ptr;
    } mLayer[SCENE_LAYER_NUM];

    struct
    {
        void* p_archive;
        SharcArchiveRes archive_res;
    } mAglRes, mJyotyuActorPack, mCobPack;

    f32 mBgZoom;
    s32 mDVControlArea;

    DrawCallback m3DDrawCallback;

    RenderMgr mBgPrepareRenderMgr;
    RenderMgr m3DRenderMgr;
    RenderMgr mDVRenderMgr;

    bool mDrawDV;

    OrthoCamera                 mCamera;
    rio::OrthoProjection        mProjection;
    rio::Vector2f               mCursorPos;
    rio::Vector2f               mLastCursorPos;

    BgRenderer                  mBgRenderer;
    s32                         mCurrentFile;

    std::vector<NextGotoItem>   mNextGotoItem;
    std::vector< std::unique_ptr<MapActorItem> > mMapActorItemPtr;
    std::vector<AreaItem>       mAreaItem;
    std::vector<LocationItem>   mLocationItem;

    bool    mBlendEnable;
    bool    mRenderNormal;
    bool    mLayerShown[CD_FILE_LAYER_MAX_NUM];
};
