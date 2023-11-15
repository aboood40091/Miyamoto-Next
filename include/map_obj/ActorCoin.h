#pragma once

#include <map_obj/BlockCoinBase.h>

class ActorCoin : public BlockCoinBase
{
    MAP_ACTOR_ITEM_CREATE(ActorCoin)

public:
    ActorCoin(MapActorData& map_actor_data)
        : BlockCoinBase(map_actor_data)
    {
    }

protected:
    UnitID getUnitID_() const override
    {
        return cUnitID_Coin;
    }
};
