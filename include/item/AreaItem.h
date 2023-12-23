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
    enum DataChangeFlag
    {
        DATA_CHANGE_FLAG_NONE           = 0,

        DATA_CHANGE_FLAG_ID             = 1 << 0,
        DATA_CHANGE_FLAG_OFFSET         = 1 << 1,
        DATA_CHANGE_FLAG_SIZE           = 1 << 2,
        DATA_CHANGE_FLAG_COLOR_OBJ      = 1 << 3,
        DATA_CHANGE_FLAG_COLOR_BG       = 1 << 4,
        DATA_CHANGE_FLAG_SCROLL         = 1 << 5,
        DATA_CHANGE_FLAG_ZOOM_TYPE      = 1 << 6,
        DATA_CHANGE_FLAG_ZOOM_ID        = 1 << 7,
        DATA_CHANGE_FLAG_ZOOM_CHANGE    = 1 << 8,
        DATA_CHANGE_FLAG_MASK           = 1 << 9,
        DATA_CHANGE_FLAG_BG2            = 1 << 10,
        DATA_CHANGE_FLAG_BG3            = 1 << 11,
        DATA_CHANGE_FLAG_DIRECTION      = 1 << 12,
        DATA_CHANGE_FLAG_UNK_15         = 1 << 13,
        DATA_CHANGE_FLAG_BGM            = 1 << 14,
        DATA_CHANGE_FLAG_BGM_MODE       = 1 << 15,
        DATA_CHANGE_FLAG_DV             = 1 << 16,
        DATA_CHANGE_FLAG_FLAG           = 1 << 17   // (lol)
    };

    friend DataChangeFlag operator|(const DataChangeFlag& lhs, const DataChangeFlag& rhs)
    {
        return (DataChangeFlag)((u32)lhs | (u32)rhs);
    }

    friend DataChangeFlag& operator|=(DataChangeFlag& lhs, const DataChangeFlag& rhs)
    {
        lhs = lhs | rhs;
        return lhs;
    }

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

    void SetDrawDV(bool drawDV)
    {
        mDrawDV = drawDV;
    }

    void onResizeRenderBuffer()
    {
        if (mpDistantViewMgr)
            mpDistantViewMgr->onResizeRenderBuffer();
    }

    void onDataChange(const AreaData& area_data, DataChangeFlag flag);

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

    void loadDistantView_(f32 x, f32 y, f32 w, f32 h, const DistantViewData& dv_data);
    void destroyDV_();

    void calcDistantViewScissor_();
    void dv_PostFx_(const rio::lyr::DrawInfo& draw_info);

private:
    AreaData                        mSelectionData;
    const agl::RenderBuffer*        mpRenderBufferDV;
    f32                             mRealBgZoom;
    std::unique_ptr<DistantViewMgr> mpDistantViewMgr;
    std::string                     mDVName;
    DrawCallbackDV                  mDrawCallbackDV;
    RenderMgr                       mRenderMgrDV;
    rio::lyr::Layer::iterator       mLayerItrDV;
    rio::lyr::Layer*                mpLayerDV;
    rio::BaseVec2i                  mScissorMin;
    rio::BaseVec2u                  mScissorSize;
    bool                            mDrawDV;
};
