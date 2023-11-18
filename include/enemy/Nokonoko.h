#pragma once

#include <item/MapActorItem.h>

class BasicModel;

class Nokonoko : public MapActorItem
{
    MAP_ACTOR_ITEM_CREATE(Nokonoko)

public:
    Nokonoko(MapActorData& map_actor_data);
    virtual ~Nokonoko();

    void update() override;
    void scheduleDraw() override;

private:
    bool drawBox_() const override
    {
        return mpModel == nullptr;
    }

    f32 getZPos_() const
    {
        return mMapActorData.layer == LAYER_1 ? 1500.0f : -2500.0f;
    }

private:
    bool        mIsBig;
    BasicModel* mpModel;
    BasicModel* mpShellModel;
};
