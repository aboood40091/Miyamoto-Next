#pragma once

#include <course/CourseDataFile.h>

#include <memory>

class MapActorItem
{
public:
    MapActorItem(MapActorData& map_actor_data);
    virtual ~MapActorItem() {}

    MapActorData& getMapActorData() { return mMapActorData; }
    const MapActorData& getMapActorData() const { return mMapActorData; }

    virtual void scheduleDraw()
    {
    }

    virtual void drawOpa();
    virtual void drawXlu();

protected:
    f32 getZPos_() const
    {
        return (mMapActorData.layer == LAYER_1) ? 2200.0f : -2500.0f; // Only layer 1 and 2
    }

protected:
    MapActorData& mMapActorData;
};

#define MAP_ACTOR_ITEM_CREATE(CLASS)                                                \
    public:                                                                         \
        static std::unique_ptr<MapActorItem> create(MapActorData& map_actor_data)   \
        {                                                                           \
            return std::make_unique<CLASS>(map_actor_data);                         \
        }
