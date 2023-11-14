#pragma once

#include <map_obj/BlockCoinBase.h>

class ActorBlockHatena : public BlockCoinBase
{
    MAP_ACTOR_ITEM_CREATE(ActorBlockHatena)

public:
    ActorBlockHatena(MapActorData& map_actor_data)
        : BlockCoinBase(map_actor_data)
    {
    }

protected:
    UnitID getUnitID_() override
    {
        return cUnitID_QBlock;
    }
};
