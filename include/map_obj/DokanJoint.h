#pragma once

#include <item/MapActorItem.h>

class ModelG3d;

class DokanJoint : public MapActorItem
{
    MAP_ACTOR_ITEM_CREATE(DokanJoint)

public:
    DokanJoint(MapActorData& map_actor_data);
    virtual ~DokanJoint();

    void update() override;
    void scheduleDraw() override;

private:
    bool drawBox_() const override
    {
        return mpModel == nullptr;
    }

    f32 getZPos_() const
    {
        switch (mMapActorData.layer)
        {
        case LAYER_0:
            return 3584.0f;
        case LAYER_2:
            return -3564.0f;
        default:
            return -64.0f;
        }
    }

private:
    ModelG3d*   mpModel;
};
