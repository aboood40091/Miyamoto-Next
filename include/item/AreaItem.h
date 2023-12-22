#pragma once

#include <course/CourseDataFile.h>
#include <distant_view/DistantViewMgr.h>
#include <item/ItemBase.h>

#include <gfx/lyr/rio_Drawable.h>

class AreaItem : public ItemBase, public rio::lyr::IDrawable
{
    class DrawCallbackDV : public RenderMgr::CallbackBase
    {
    public:
        DrawCallbackDV(s32 index)
            : mIndex(index)
        {
        }

        void setIndex(u32 index)
        {
            mIndex = index;
        }

        void preDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info) override;
        void preDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info) override;
        void postDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info) override;
        void postDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info) override;

    private:
        s32 mIndex;
    };

public:
    AreaItem(const AreaData& area_data, u32 index, const agl::RenderBuffer& render_buffer);
    virtual ~AreaItem();

    AreaItem(const AreaItem&) = delete;
    AreaItem(AreaItem&&) = delete;
    AreaItem& operator=(const AreaItem&) = delete;
    AreaItem& operator=(AreaItem&&) = delete;

    f32 getRealBgZoom() const
    {
        return mRealBgZoom;
    }

    RenderObjLayer* getDistantViewLayer()
    {
        return static_cast<RenderObjLayer*>(mpLayerDV);
    }

    const RenderObjLayer* getDistantViewLayer() const
    {
        return static_cast<const RenderObjLayer*>(mpLayerDV);
    }

    void onResizeRenderBuffer()
    {
        if (mpDistantViewMgr)
            mpDistantViewMgr->onResizeRenderBuffer();
    }

    void onSceneUpdate();

    void gather();
    void dispose();

    void move(s16 dx, s16 dy, bool commit) override;
    void drawSelectionUI() override;

    void drawOpa();
    void drawXlu();

private:
    f32 getZPos_() const
    {
        return 3600.0f;
    }

    void onSelectionChange_() override;

    void onIndexChange_() override
    {
        mDrawCallbackDV.setIndex(mItemID.getIndex());
    }

    void calcDistantViewScissor_();
    void dv_PostFx_(const rio::lyr::DrawInfo& draw_info);

private:
    AreaData                        mSelectionData;
    const agl::RenderBuffer*        mpRenderBufferDV;
    f32                             mRealBgZoom;
    std::unique_ptr<DistantViewMgr> mpDistantViewMgr;
    DrawCallbackDV                  mDrawCallbackDV;
    RenderMgr                       mRenderMgrDV;
    rio::lyr::Layer::iterator       mLayerItrDV;
    rio::lyr::Layer*                mpLayerDV;
    rio::BaseVec2i                  mScissorMin;
    rio::BaseVec2u                  mScissorSize;
    bool                            mDrawDV;
};
