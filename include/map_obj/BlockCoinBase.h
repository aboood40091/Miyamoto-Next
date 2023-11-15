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

    void drawOpa(const rio::lyr::DrawInfo& draw_info) override
    {
    }

    void drawXlu(const rio::lyr::DrawInfo& draw_info) override
    {
    }

    void scheduleDraw() override;

protected:
    virtual UnitID getUnitID_() const = 0;
};
