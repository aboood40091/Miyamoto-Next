#pragma once

#include <item/MapActorItem.h>
#include <map_obj/ObjDokan.h>

class ObjDokanActorBase : public MapActorItem
{
public:
    ObjDokanActorBase(const MapActorData& map_actor_data, u32 index, ObjDokan::Direction dir, bool cb, bool group, f32 position_offset_x, f32 position_offset_y);

    void onDataChange(const MapActorData& map_actor_data, DataChangeFlag flag) override;

    void onSceneUpdate() override
    {
        if (mObjDokan.isCreated())
            mObjDokan.onSceneUpdate();
    }

    void scheduleDraw() override
    {
        if (mObjDokan.isCreated())
            mObjDokan.scheduleDraw();
    }

protected:
    bool drawBox_() const override
    {
        return !mObjDokan.isCreated();
    }

    void updatePositionXY_(const MapActorData& map_actor_data)
    {
        mPosition.x =  f32(map_actor_data.offset.x) + cPositionOffset.x;
        mPosition.y = -f32(map_actor_data.offset.y) + cPositionOffset.y;
    }

    void updatePositionZ_(const MapActorData& map_actor_data)
    {
        switch (map_actor_data.layer)
        {
        case LAYER_0:
            mPosition.z = 3520;
            break;
        case LAYER_2:
            mPosition.z = -3628;
            break;
        default:
            mPosition.z = -128;
            break;
        }
    }

    bool updateParam_(const MapActorData& map_actor_data);

    void setModelItemID_();
    void setModelSelection_();

    void onIndexChange_() override { setModelItemID_(); }
    void onSelectionChange_() override { MapActorItem::onSelectionChange_(); setModelSelection_(); }

protected:
    ObjDokan                mObjDokan;

    const bool              cCB;
    const bool              cGroup;
    const rio::BaseVec2f    cPositionOffset;
    rio::BaseVec3f          mPosition;
};
