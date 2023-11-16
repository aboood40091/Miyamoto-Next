#pragma once

#include <course/UnitID.h>
#include <item/MapActorItem.h>

class ActorBlockBigBase : public MapActorItem
{
public:
    ActorBlockBigBase(MapActorData& map_actor_data, bool set_coin)
        : MapActorItem(map_actor_data)
        , mSetCoin(set_coin)
    {
    }

    void drawOpa(const rio::lyr::DrawInfo& draw_info) override
    {
    }

    void drawXlu(const rio::lyr::DrawInfo& draw_info) override;
    void scheduleDraw() override;

protected:
    virtual UnitID getUnitID_() const = 0;

private:
    bool    mSetCoin;
};
