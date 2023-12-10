#pragma once

#include <map_obj/ActorBlockBigBase.h>

class ActorBlockBigRenga : public ActorBlockBigBase
{
    MAP_ACTOR_ITEM_CREATE(ActorBlockBigRenga)

public:
    ActorBlockBigRenga(const MapActorData& map_actor_data, u32 index)
        : ActorBlockBigBase(map_actor_data, index, UnitID(112), true)
    {
    }
};
