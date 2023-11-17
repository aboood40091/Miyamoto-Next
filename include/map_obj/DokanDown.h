#pragma once

#include <map_obj/DokanBase.h>

class DokanDown : public DokanBase
{
    MAP_ACTOR_ITEM_CREATE(DokanDown)

public:
    DokanDown(MapActorData& map_actor_data)
        : DokanBase(map_actor_data, Dokan::DIRECTION_DOWN, false, map_actor_data.id == 578)
    {
    }

    void update() override
    {
        if (mDokan == nullptr)
            return;

        mDokan->update({ f32(mMapActorData.offset.x + 16), -f32(mMapActorData.offset.y), getZPos_() });
    }
};
