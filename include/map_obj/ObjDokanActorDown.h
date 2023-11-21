#pragma once

#include <map_obj/ObjDokanActorBase.h>

class ObjDokanActorDown : public ObjDokanActorBase
{
    MAP_ACTOR_ITEM_CREATE(ObjDokanActorDown)

public:
    ObjDokanActorDown(MapActorData& map_actor_data)
        : ObjDokanActorBase(map_actor_data, ObjDokan::DIRECTION_DOWN, false, map_actor_data.id == 578, 16, 0)
    {
    }
};
