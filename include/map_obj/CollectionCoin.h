#pragma once

#include <item/MapActorItem.h>

#include <math/rio_MathTypes.h>

class ModelG3d;

class CollectionCoin : public MapActorItem
{
    MAP_ACTOR_ITEM_CREATE(CollectionCoin)

public:
    CollectionCoin(MapActorData& map_actor_data, u32 index);
    virtual ~CollectionCoin();

    void onDataChange(DataChangeFlag flag) override;
    void onSceneUpdate() override;
    void scheduleDraw() override;

private:
    bool drawBox_() const override
    {
        return mpModel == nullptr;
    }

    void updatePositionXY_()
    {
        mPosition.x =  f32(mMapActorData.offset.x + 16);
        mPosition.y = -f32(mMapActorData.offset.y + 16);
    }

    void updatePositionZ_()
    {
        mPosition.z = -3000;
        if (mMapActorData.layer == LAYER_1)
        {
            switch (mMapActorData.settings[0] >> 8 & 0xF)
            {
            default:
                mPosition.z = 550;
                break;
            case 1:
                break;
            case 2:
                mPosition.z = -1000;
                break;
            }
        }
    }

    void setModelItemID_();
    void setModelSelection_();

    void onIndexChange_() override { setModelItemID_(); }
    void onSelectionChange_() override { setModelSelection_(); }

private:
    ModelG3d*       mpModel;
    rio::BaseVec3f  mPosition;
};
