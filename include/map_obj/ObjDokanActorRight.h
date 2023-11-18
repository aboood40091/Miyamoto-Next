#pragma once

#include <map_obj/ObjDokanActorBase.h>

class ObjDokanActorRight : public ObjDokanActorBase
{
    MAP_ACTOR_ITEM_CREATE(ObjDokanActorRight)

public:
    ObjDokanActorRight(MapActorData& map_actor_data)
        : ObjDokanActorBase(map_actor_data, ObjDokan::DIRECTION_RIGHT, false, map_actor_data.id == 576)
    {
        update();
    }

    void update() override
    {
        if (mObjDokan == nullptr)
            return;

        mObjDokan->update({ f32(mMapActorData.offset.x), -f32(mMapActorData.offset.y + 16), getZPos_() });
    }
};

