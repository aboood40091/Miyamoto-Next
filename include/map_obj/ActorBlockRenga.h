#pragma once

#include <course/BgTexMgr.h>
#include <map_obj/BlockCoinBase.h>

class ActorBlockRenga : public BlockCoinBase
{
    MAP_ACTOR_ITEM_CREATE_DEFAULT(ActorBlockRenga)

public:
    ActorBlockRenga(const MapActorData& map_actor_data, u32 index)
        : BlockCoinBase(map_actor_data, index)
    {
        updatePositionZ_(map_actor_data);
        updateType_(map_actor_data);
    }

    void onDataChange(const MapActorData& map_actor_data, DataChangeFlag flag) override;

    void drawXlu(const rio::lyr::DrawInfo& draw_info) override;

private:
    UnitID getUnitID_() const override
    {
        return mUnitID;
    }

    void updatePositionZ_(const MapActorData& map_actor_data) override
    {
        mPosition.z = (map_actor_data.layer == LAYER_1 && !(map_actor_data.settings[0] >> 8 & 1)) ? 500.0f : -3000.0f;
    }

    void updateType_(const MapActorData& map_actor_data);

private:
    UnitID              mUnitID;
    BgTexMgr::ItemType  mItemType;
};
