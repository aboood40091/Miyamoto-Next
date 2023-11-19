#pragma once

#include <map_obj/ActorBlockBigBase.h>

class ActorBlockBigHatena : public ActorBlockBigBase
{
    MAP_ACTOR_ITEM_CREATE(ActorBlockBigHatena)

public:
    ActorBlockBigHatena(MapActorData& map_actor_data)
        : ActorBlockBigBase(map_actor_data, UnitID(114), false)
    {
    }
};
