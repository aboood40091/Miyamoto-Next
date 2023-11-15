#pragma once

#include <course/CourseDataFile.h>

#include <gfx/lyr/rio_Drawable.h>

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

    virtual void drawOpa(const rio::lyr::DrawInfo& draw_info);
    virtual void drawXlu(const rio::lyr::DrawInfo& draw_info);

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
