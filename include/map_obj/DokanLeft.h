#pragma once

#include <map_obj/DokanBase.h>

class DokanLeft : public DokanBase
{
    MAP_ACTOR_ITEM_CREATE(DokanLeft)

public:
    DokanLeft(MapActorData& map_actor_data)
        : DokanBase(map_actor_data, Dokan::DIRECTION_LEFT, false, map_actor_data.id == 575)
    {
        update();
    }

    void update() override
    {
        if (mDokan == nullptr)
            return;

        mDokan->update({ f32(mMapActorData.offset.x + 16), -f32(mMapActorData.offset.y + 16), getZPos_() });
    }
};
