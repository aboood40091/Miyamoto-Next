#pragma once

#include <map_obj/ObjDokanActorBase.h>

class ObjDokanActorDownNextGoto : public ObjDokanActorBase
{
    MAP_ACTOR_ITEM_CREATE_DEFAULT(ObjDokanActorDownNextGoto)

public:
    ObjDokanActorDownNextGoto(const MapActorData& map_actor_data, u32 index)
        : ObjDokanActorBase(map_actor_data, index, ObjDokan::DIRECTION_DOWN, false, false, 16, 16)
    {
    }
};
