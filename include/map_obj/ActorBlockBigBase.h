#pragma once

#include <course/BgTexMgr.h>
#include <item/MapActorItem.h>

class ActorBlockBigBase : public MapActorItem
{
public:
    ActorBlockBigBase(MapActorData& map_actor_data, u32 index, UnitID unit, bool set_coin)
        : MapActorItem(map_actor_data, index)
        , cUnitID(unit)
        , cSetCoin(set_coin)
    {
        updatePositionXY_();
        updatePositionZ_();
        updateItemType_();
    }

    void onDataChange(DataChangeFlag flag) override;
    void scheduleDraw() override;

    void drawOpa(const rio::lyr::DrawInfo& draw_info) override
    {
    }

    void drawXlu(const rio::lyr::DrawInfo& draw_info) override;

private:
    void updatePositionXY_()
    {
        mPosition.x =  f32(mMapActorData.offset.x);
        mPosition.y = -f32(mMapActorData.offset.y + 16);
    }

    void updatePositionZ_()
    {
        mPosition.z = mMapActorData.layer == LAYER_1 ? 500.0f : -3000.0f;
    }

    void updateItemType_();

private:
    const UnitID        cUnitID;
    const bool          cSetCoin;

    BgTexMgr::ItemType  mItemType;
    rio::BaseVec3f      mPosition;
};
