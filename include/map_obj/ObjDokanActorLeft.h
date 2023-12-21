#pragma once

#include <map_obj/ObjDokanActorBase.h>

class ObjDokanActorLeft : public ObjDokanActorBase
{
    MAP_ACTOR_ITEM_CREATE_DEFAULT(ObjDokanActorLeft)

public:
    ObjDokanActorLeft(const MapActorData& map_actor_data, u32 index)
        : ObjDokanActorBase(map_actor_data, index, ObjDokan::DIRECTION_LEFT, false, map_actor_data.type == 575, 16, -16)
    {
    }
};
