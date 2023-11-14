#pragma once

#include <course/UnitID.h>
#include <item/MapActorItem.h>

class BlockCoinBase : public MapActorItem
{
public:
    BlockCoinBase(MapActorData& map_actor_data)
        : MapActorItem(map_actor_data)
    {
    }

    void drawOpa() override
    {
    }

    void drawXlu() override
    {
    }

    void scheduleDraw() override;

protected:
    virtual UnitID getUnitID_() = 0;
};
