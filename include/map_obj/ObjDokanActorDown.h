#pragma once

#include <map_obj/ObjDokanActorBase.h>

class ObjDokanActorDown : public ObjDokanActorBase
{
    MAP_ACTOR_ITEM_CREATE_DEFAULT(ObjDokanActorDown)

public:
    ObjDokanActorDown(const MapActorData& map_actor_data, u32 index)
        : ObjDokanActorBase(map_actor_data, index, ObjDokan::DIRECTION_DOWN, false, map_actor_data.type == 578, 16, 0)
    {
    }
};
