#pragma once

#include <map_obj/DokanBase.h>

class DokanUp : public DokanBase
{
    MAP_ACTOR_ITEM_CREATE(DokanUp)

public:
    DokanUp(MapActorData& map_actor_data)
        : DokanBase(map_actor_data, Dokan::DIRECTION_UP, false, map_actor_data.id == 577)
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

