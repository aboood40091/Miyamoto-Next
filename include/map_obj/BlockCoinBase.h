#pragma once

#include <course/UnitID.h>
#include <item/MapActorItem.h>

#include <math/rio_MathTypes.h>

class BlockCoinBase : public MapActorItem
{
public:
    BlockCoinBase(MapActorData& map_actor_data)
        : MapActorItem(map_actor_data)
    {
        updatePositionXY_();
        updatePositionZ_();
    }

    void onDataChange(DataChangeFlag flag) override;
    void scheduleDraw() override;

    void drawOpa(const rio::lyr::DrawInfo& draw_info) override
    {
    }

    void drawXlu(const rio::lyr::DrawInfo& draw_info) override
    {
    }

protected:
    virtual UnitID getUnitID_() const = 0;

private:
    void updatePositionXY_()
    {
        mPosition.x =  f32(mMapActorData.offset.x);
        mPosition.y = -f32(mMapActorData.offset.y);
    }

    void updatePositionZ_()
    {
        mPosition.z = getDefaultZPos(mMapActorData.layer);
    }

protected:
    rio::BaseVec3f  mPosition;
};
