#pragma once

#include <map_obj/ActorBlockBigBase.h>

class ActorBlockBigHatena : public ActorBlockBigBase
{
    MAP_ACTOR_ITEM_CREATE(ActorBlockBigHatena)

public:
    ActorBlockBigHatena(MapActorData& map_actor_data)
        : ActorBlockBigBase(map_actor_data, false)
    {
    }

protected:
    UnitID getUnitID_() const override
    {
        return UnitID(114);
    }
};
