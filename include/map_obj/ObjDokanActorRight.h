#pragma once

#include <map_obj/ObjDokanActorBase.h>

class ObjDokanActorRight : public ObjDokanActorBase
{
    MAP_ACTOR_ITEM_CREATE_DEFAULT(ObjDokanActorRight)

public:
    ObjDokanActorRight(const MapActorData& map_actor_data, u32 index)
        : ObjDokanActorBase(map_actor_data, index, ObjDokan::DIRECTION_RIGHT, false, map_actor_data.type == 576, 0, -16)
    {
    }
};

