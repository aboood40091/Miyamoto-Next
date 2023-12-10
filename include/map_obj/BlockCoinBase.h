#pragma once

#include <course/UnitID.h>
#include <item/MapActorItem.h>

#include <math/rio_MathTypes.h>

class BlockCoinBase : public MapActorItem
{
public:
    BlockCoinBase(MapActorData& map_actor_data, u32 index)
        : MapActorItem(map_actor_data, index)
    {
        updatePositionXY_(map_actor_data);
    }

    void onDataChange(const MapActorData& map_actor_data, DataChangeFlag flag) override;
    void scheduleDraw() override;

    void drawOpa(const rio::lyr::DrawInfo& draw_info) override
    {
    }

    void drawXlu(const rio::lyr::DrawInfo& draw_info) override
    {
    }

protected:
    virtual UnitID getUnitID_() const = 0;

    void updatePositionXY_(const MapActorData& map_actor_data)
    {
        mPosition.x =  f32(map_actor_data.offset.x);
        mPosition.y = -f32(map_actor_data.offset.y);
    }

    virtual void updatePositionZ_(const MapActorData& map_actor_data) = 0;

protected:
    rio::BaseVec3f  mPosition;
};
