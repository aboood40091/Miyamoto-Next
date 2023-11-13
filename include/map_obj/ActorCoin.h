#pragma once

#include <item/MapActorItem.h>

class ActorCoin : public MapActorItem
{
    MAP_ACTOR_ITEM_CREATE(ActorCoin)

public:
    ActorCoin(MapActorData& map_actor_data);

    void drawOpa() override
    {
    }

    void drawXlu() override
    {
    }

    void scheduleDraw() override;
};
