#pragma once

#include <map_obj/ObjDokanActorBase.h>

class ObjDokanActorUp : public ObjDokanActorBase
{
    MAP_ACTOR_ITEM_CREATE(ObjDokanActorUp)

public:
    ObjDokanActorUp(MapActorData& map_actor_data, u32 index)
        : ObjDokanActorBase(map_actor_data, index, ObjDokan::DIRECTION_UP, false, map_actor_data.id == 577, 16, -16)
    {
    }
};

