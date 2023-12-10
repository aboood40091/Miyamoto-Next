#pragma once

#include <course/BgTexMgr.h>
#include <item/MapActorItem.h>

class ActorBlockBigBase : public MapActorItem
{
public:
    ActorBlockBigBase(const MapActorData& map_actor_data, u32 index, UnitID unit, bool set_coin)
        : MapActorItem(map_actor_data, index)
        , cUnitID(unit)
        , cSetCoin(set_coin)
    {
        updatePositionXY_(map_actor_data);
        updatePositionZ_(map_actor_data);
        updateItemType_(map_actor_data);
    }

    void onDataChange(const MapActorData& map_actor_data, DataChangeFlag flag) override;
    void scheduleDraw() override;

    void drawOpa(const rio::lyr::DrawInfo& draw_info) override
    {
    }

    void drawXlu(const rio::lyr::DrawInfo& draw_info) override;

private:
    void updatePositionXY_(const MapActorData& map_actor_data)
    {
        mPosition.x =  f32(map_actor_data.offset.x);
        mPosition.y = -f32(map_actor_data.offset.y + 16);
    }

    void updatePositionZ_(const MapActorData& map_actor_data)
    {
        mPosition.z = map_actor_data.layer == LAYER_1 ? 500.0f : -3000.0f;
    }

    void updateItemType_(const MapActorData& map_actor_data);

private:
    const UnitID        cUnitID;
    const bool          cSetCoin;

    BgTexMgr::ItemType  mItemType;
    rio::BaseVec3f      mPosition;
};
