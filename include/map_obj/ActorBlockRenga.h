#pragma once

#include <course/BgTexMgr.h>
#include <map_obj/BlockCoinBase.h>

class ActorBlockRenga : public BlockCoinBase
{
    MAP_ACTOR_ITEM_CREATE(ActorBlockRenga)

public:
    ActorBlockRenga(MapActorData& map_actor_data)
        : BlockCoinBase(map_actor_data)
    {
        updateType_();
    }

    void onDataChange(DataChangeFlag flag) override;

    void drawXlu(const rio::lyr::DrawInfo& draw_info) override;

private:
    UnitID getUnitID_() const override
    {
        return mUnitID;
    }

    void updateType_();

private:
    UnitID              mUnitID;
    BgTexMgr::ItemType  mItemType;
};
