#pragma once

#include <map_obj/ObjDokanActorBase.h>

class ObjDokanActorLeft : public ObjDokanActorBase
{
    MAP_ACTOR_ITEM_CREATE(ObjDokanActorLeft)

public:
    ObjDokanActorLeft(MapActorData& map_actor_data)
        : ObjDokanActorBase(map_actor_data, ObjDokan::DIRECTION_LEFT, false, map_actor_data.id == 575, 16, -16)
    {
    }
};
