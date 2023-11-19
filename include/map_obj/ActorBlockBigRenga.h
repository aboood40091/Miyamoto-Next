#pragma once

#include <map_obj/ActorBlockBigBase.h>

class ActorBlockBigRenga : public ActorBlockBigBase
{
    MAP_ACTOR_ITEM_CREATE(ActorBlockBigRenga)

public:
    ActorBlockBigRenga(MapActorData& map_actor_data)
        : ActorBlockBigBase(map_actor_data, UnitID(112), true)
    {
    }
};
