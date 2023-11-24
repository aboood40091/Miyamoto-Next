#pragma once

#include <map_obj/BlockCoinBase.h>

class ActorCoin : public BlockCoinBase
{
    MAP_ACTOR_ITEM_CREATE(ActorCoin)

public:
    ActorCoin(MapActorData& map_actor_data)
        : BlockCoinBase(map_actor_data)
    {
        updatePositionZ_();
    }

protected:
    UnitID getUnitID_() const override
    {
        return cUnitID_Coin;
    }

    void updatePositionZ_() override
    {
        mPosition.z = (mMapActorData.layer == LAYER_1 && !(mMapActorData.settings[0] >> 8 & 0xf)) ? 550.0f : -3000.0f;
    }
};
