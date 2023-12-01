#pragma once

#include <course/BgTexMgr.h>
#include <map_obj/BlockCoinBase.h>

class ActorBlockHatena : public BlockCoinBase
{
    MAP_ACTOR_ITEM_CREATE(ActorBlockHatena)

public:
    ActorBlockHatena(MapActorData& map_actor_data, u32 index)
        : BlockCoinBase(map_actor_data, index)
    {
        updatePositionZ_();
        updateType_();
    }

    void onDataChange(DataChangeFlag flag) override;

    void drawXlu(const rio::lyr::DrawInfo& draw_info) override;

private:
    UnitID getUnitID_() const override
    {
        return mUnitID;
    }

    void updatePositionZ_() override
    {
        mPosition.z = (mMapActorData.layer == LAYER_1 && !(mMapActorData.settings[0] >> 8 & 1)) ? 500.0f : -3000.0f;
    }

    void updateType_();

private:
    UnitID              mUnitID;
    BgTexMgr::ItemType  mItemType;
};
