#pragma once

#include <item/MapActorItem.h>
#include <map_obj/Dokan.h>

#include <memory>

class DokanBase : public MapActorItem
{
public:
    DokanBase(MapActorData& map_actor_data, Dokan::Direction dir, bool cb, bool group);

    void update() override = 0;
    void scheduleDraw() override;

protected:
    bool drawBox_() const override
    {
        return mDokan == nullptr;
    }

    f32 getZPos_() const
    {
        switch (mMapActorData.layer)
        {
        case LAYER_0:
            return 3520;
        case LAYER_2:
            return -3628;
        default:
            return -128;
        }
    }

protected:
    std::unique_ptr<Dokan>  mDokan;
};
