#pragma once

#include <map_obj/ObjDokanActorBase.h>

class ObjDokanActorUp : public ObjDokanActorBase
{
    MAP_ACTOR_ITEM_CREATE_DEFAULT(ObjDokanActorUp)

public:
    ObjDokanActorUp(const MapActorData& map_actor_data, u32 index)
        : ObjDokanActorBase(map_actor_data, index, ObjDokan::DIRECTION_UP, false, map_actor_data.type == 577, 16, -16)
    {
    }
};

