#pragma once

#include <map_obj/DokanBase.h>

class DokanDownNextGoto : public DokanBase
{
    MAP_ACTOR_ITEM_CREATE(DokanDownNextGoto)

public:
    DokanDownNextGoto(MapActorData& map_actor_data)
        : DokanBase(map_actor_data, Dokan::DIRECTION_DOWN, false, false)
    {
        update();
    }

    void update() override
    {
        if (mDokan == nullptr)
            return;

        mDokan->update({ f32(mMapActorData.offset.x + 16), -f32(mMapActorData.offset.y) + 16, getZPos_() });
    }
};
