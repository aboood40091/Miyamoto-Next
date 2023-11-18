#pragma once

#include <item/MapActorItem.h>
#include <map_obj/ObjDokan.h>

#include <memory>

class ObjDokanActorBase : public MapActorItem
{
public:
    ObjDokanActorBase(MapActorData& map_actor_data, ObjDokan::Direction dir, bool cb, bool group);

    void update() override = 0;
    void scheduleDraw() override;

protected:
    bool drawBox_() const override
    {
        return mObjDokan == nullptr;
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
    std::unique_ptr<ObjDokan>   mObjDokan;
};
