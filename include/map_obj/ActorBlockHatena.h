#pragma once

#include <map_obj/BlockCoinBase.h>

class ActorBlockHatena : public BlockCoinBase
{
    MAP_ACTOR_ITEM_CREATE(ActorBlockHatena)

public:
    ActorBlockHatena(MapActorData& map_actor_data)
        : BlockCoinBase(map_actor_data)
    {
    }

    void drawXlu(const rio::lyr::DrawInfo& draw_info) override;

protected:
    UnitID getUnitID_() const override;
};
