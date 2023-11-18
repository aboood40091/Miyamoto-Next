#pragma once

#include <map_obj/ObjDokanActorBase.h>

class ObjDokanActorDown : public ObjDokanActorBase
{
    MAP_ACTOR_ITEM_CREATE(ObjDokanActorDown)

public:
    ObjDokanActorDown(MapActorData& map_actor_data)
        : ObjDokanActorBase(map_actor_data, ObjDokan::DIRECTION_DOWN, false, map_actor_data.id == 578)
    {
        update();
    }

    void update() override
    {
        if (mObjDokan == nullptr)
            return;

        mObjDokan->update({ f32(mMapActorData.offset.x + 16), -f32(mMapActorData.offset.y), getZPos_() });
    }
};
