#pragma once

#include <map_obj/DokanBase.h>

class DokanRight : public DokanBase
{
    MAP_ACTOR_ITEM_CREATE(DokanRight)

public:
    DokanRight(MapActorData& map_actor_data)
        : DokanBase(map_actor_data, Dokan::DIRECTION_RIGHT, false, map_actor_data.id == 576)
    {
        update();
    }

    void update() override
    {
        if (mDokan == nullptr)
            return;

        mDokan->update({ f32(mMapActorData.offset.x), -f32(mMapActorData.offset.y + 16), getZPos_() });
    }
};

