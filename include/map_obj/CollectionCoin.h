#pragma once

#include <item/MapActorItem.h>

#include <math/rio_MathTypes.h>

class ModelG3d;

class CollectionCoin : public MapActorItem
{
    MAP_ACTOR_ITEM_CREATE_DEFAULT(CollectionCoin)

public:
    CollectionCoin(const MapActorData& map_actor_data, u32 index);
    virtual ~CollectionCoin();

    void onDataChange(const MapActorData& map_actor_data, DataChangeFlag flag) override;
    void onSceneUpdate() override;
    void scheduleDraw() override;

    bool hasGraphics() const override
    {
        return mpModel != nullptr;
    }

private:
    void updatePositionXY_(const MapActorData& map_actor_data)
    {
        mPosition.x =  f32(map_actor_data.offset.x + 16);
        mPosition.y = -f32(map_actor_data.offset.y + 16);
    }

    void updatePositionZ_(const MapActorData& map_actor_data)
    {
        mPosition.z = -3000;
        if (map_actor_data.layer == LAYER_1)
        {
            switch (map_actor_data.settings[0] >> 8 & 0xF)
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
    void onSelectionChange_() override { MapActorItem::onSelectionChange_(); setModelSelection_(); }

private:
    ModelG3d*       mpModel;
    rio::BaseVec3f  mPosition;
};
