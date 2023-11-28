#pragma once

#include <course/Constants.h>
#include <graphics/OrthoCamera.h>
#include <graphics/RenderMgr.h>
#include <graphics/RenderObjLayer.h>

#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <gpu/rio_RenderBuffer.h>
#include <gpu/rio_RenderTarget.h>

#include <memory>

struct  AreaData;
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

public:
    CourseView(s32 width, s32 height, const rio::BaseVec2f& window_pos);
    ~CourseView();

    void setZoom(f32 zoom)
    {
        mBgZoom = zoom;
        mCamera.setZoomScale(mSize.y / (zoom * 224.0f));
    }

    template <typename T>
    inline void setZoomTileSize(T tile_size)
    {
        setZoom(16.f / tile_size * (mSize.y / 224.0f));
    }

    f32 getZoomTileSize() const
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

    void resize(s32 width, s32 height, bool preserve_tile_size = false);

    rio::BaseVec2f viewToWorldPos(const rio::BaseVec2f& pos) const;
    rio::BaseVec2f worldToViewPos(const rio::BaseVec2f& pos) const;

    void initialize(CourseDataFile* p_cd_file, bool real_zoom);
    void reset()
    {
        initialize(nullptr, false);
    }

    void updateCursorPos(const rio::BaseVec2f& window_pos);
    void processMouseInput();
    void processKeyboardInput();

    void update();

    void gather();
    void dispose();

private:
    void createRenderBuffer_(s32 width, s32 height);
    void bindRenderBuffer_();
    void unbindRenderBuffer_();

    void drawCursor_();

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
    f32                         mBgZoom;
    rio::Vector2f               mCursorPos;
    rio::Vector2f               mLastCursorPos;
    std::vector<NextGotoItem>   mNextGotoItem;
    std::vector< std::unique_ptr<MapActorItem> >
                                mMapActorItemPtr;
    std::vector<AreaItem>       mAreaItem;
    std::vector<LocationItem>   mLocationItem;
    rio::Texture2D             *mpColorTexture,
                               *mpDepthTexture;
    rio::RenderTargetColor      mColorTarget;
    agl::RenderTargetColor      mColorTargetDV;
    rio::RenderTargetDepth      mDepthTarget;
    agl::RenderTargetDepth      mDepthTargetDV;
    rio::RenderBuffer           mRenderBuffer;
    agl::RenderBuffer           mRenderBufferDV;
    bool                        mDrawDV;
    bool                        mLayerShown[CD_FILE_LAYER_MAX_NUM];
};
