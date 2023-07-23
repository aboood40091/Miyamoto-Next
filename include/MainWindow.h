#pragma once

#include <course/CourseData.h>
#include <course/BgRenderer.h>

#include <graphics/OrthoCamera.h>

#include <item/AreaItem.h>
#include <item/LocationItem.h>
#include <item/NextGotoItem.h>
#include <item/MapActorItem.h>

#include <resource/SharcArchiveRes.h>

#include <gfx/rio_Projection.h>
#include <gfx/lyr/rio_Layer.h>
#include <task/rio_Task.h>

class MainWindow : public rio::ITask, public rio::lyr::IDrawable
{
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

    void setCurrentCourseDataFile(u32 id);

private:
    void prepare_() override;
    void calc_()    override;
    void exit_()    override;

    void processInputs_();
    void updateCursorPos_();
    void drawCursor_();

    void dv_CalcMdl_(const rio::lyr::DrawInfo& draw_info);
    void dv_CalcGPU_(const rio::lyr::DrawInfo& draw_info);
    void dv_DrawOpa_(const rio::lyr::DrawInfo& draw_info);
    void dv_DrawXlu_(const rio::lyr::DrawInfo& draw_info);
    void dv_PostFx_ (const rio::lyr::DrawInfo& draw_info);

    void bg_Render_ (const rio::lyr::DrawInfo& draw_info);

private:
    enum SceneLayer
    {
        SCENE_LAYER_BG = 0,
        SCENE_LAYER_DISTANT_VIEW,
        SCENE_LAYER_NUM
    };

    struct
    {
        rio::lyr::Layer::iterator it;
        rio::lyr::Layer* ptr;
    } mLayer[SCENE_LAYER_NUM];

    void* mpArchive;
    SharcArchiveRes mArchiveRes;

    f32 mBgZoom;
    s32 mDVControlArea;

    bool mDrawDV;
    bool mRestoreScissor;

    OrthoCamera                 mCamera;
    rio::OrthoProjection        mProjection;
    rio::Vector2f               mCursorPos;
    rio::Vector2f               mLastCursorPos;

    CourseData                  mCourseData;
    BgRenderer                  mBgRenderer;
    s32                         mCurrentFile;

    std::vector<NextGotoItem>   mNextGotoItem;
    std::vector<MapActorItem>   mMapActorItem;
    std::vector<AreaItem>       mAreaItem;
    std::vector<LocationItem>   mLocationItem;

    bool    mBlendEnable;
    bool    mLayerShown[CD_FILE_LAYER_MAX_NUM];
};
