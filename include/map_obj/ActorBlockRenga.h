#pragma once

#include <map_obj/BlockCoinBase.h>

class ActorBlockRenga : public BlockCoinBase
{
    MAP_ACTOR_ITEM_CREATE(ActorBlockRenga)

public:
    ActorBlockRenga(MapActorData& map_actor_data)
        : BlockCoinBase(map_actor_data)
    {
    }

protected:
    UnitID getUnitID_() override
    {
        return cUnitID_BrickBlock;
    }
};
