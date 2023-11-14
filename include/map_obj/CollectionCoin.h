#pragma once

#include <item/MapActorItem.h>

class ModelG3d;

class CollectionCoin : public MapActorItem
{
    MAP_ACTOR_ITEM_CREATE(CollectionCoin)

public:
    CollectionCoin(MapActorData& map_actor_data);
    virtual ~CollectionCoin();

    void drawOpa() override;
    void drawXlu() override;
    void scheduleDraw() override;

private:
    f32 getZPos_() const
    {
        if (mMapActorData.layer == LAYER_1)
        {
            switch (mMapActorData.settings[0] >> 8 & 0xF)
            {
            default:
                return 550;
            case 1:
                break;
            case 2:
                return -1000;
            }
        }
        return -3000;
    }

private:
    ModelG3d*   mpModel;
};
