#pragma once

#include <map_obj/ObjDokanActorBase.h>

class ObjDokanActorUp : public ObjDokanActorBase
{
    MAP_ACTOR_ITEM_CREATE(ObjDokanActorUp)

public:
    ObjDokanActorUp(MapActorData& map_actor_data)
        : ObjDokanActorBase(map_actor_data, ObjDokan::DIRECTION_UP, false, map_actor_data.id == 577)
    {
        update();
    }

    void update() override
    {
        if (mObjDokan == nullptr)
            return;

        mObjDokan->update({ f32(mMapActorData.offset.x + 16), -f32(mMapActorData.offset.y + 16), getZPos_() });
    }
};

