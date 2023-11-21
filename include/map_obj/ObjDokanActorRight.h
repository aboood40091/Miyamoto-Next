#pragma once

#include <map_obj/ObjDokanActorBase.h>

class ObjDokanActorRight : public ObjDokanActorBase
{
    MAP_ACTOR_ITEM_CREATE(ObjDokanActorRight)

public:
    ObjDokanActorRight(MapActorData& map_actor_data)
        : ObjDokanActorBase(map_actor_data, ObjDokan::DIRECTION_RIGHT, false, map_actor_data.id == 576, 0, -16)
    {
    }
};

