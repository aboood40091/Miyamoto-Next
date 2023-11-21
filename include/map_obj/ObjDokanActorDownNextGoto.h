#pragma once

#include <map_obj/ObjDokanActorBase.h>

class ObjDokanActorDownNextGoto : public ObjDokanActorBase
{
    MAP_ACTOR_ITEM_CREATE(ObjDokanActorDownNextGoto)

public:
    ObjDokanActorDownNextGoto(MapActorData& map_actor_data)
        : ObjDokanActorBase(map_actor_data, ObjDokan::DIRECTION_DOWN, false, false, 16, 16)
    {
    }
};
