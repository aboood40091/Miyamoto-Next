#pragma once

#include <map_obj/BlockCoinBase.h>

class ActorCoin : public BlockCoinBase
{
    MAP_ACTOR_ITEM_CREATE(ActorCoin)

public:
    ActorCoin(const MapActorData& map_actor_data, u32 index)
        : BlockCoinBase(map_actor_data, index)
    {
        updatePositionZ_(map_actor_data);
    }

protected:
    UnitID getUnitID_() const override
    {
        return cUnitID_Coin;
    }

    void updatePositionZ_(const MapActorData& map_actor_data) override
    {
        mPosition.z = (map_actor_data.layer == LAYER_1 && !(map_actor_data.settings[0] >> 8 & 0xf)) ? 550.0f : -3000.0f;
    }
};
