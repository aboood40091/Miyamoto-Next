#pragma once

#include <course/CourseDataFile.h>

class MapActorItem
{
public:
    MapActorItem(MapActorData& map_actor_data);

    MapActorData& getMapActorData() { return mMapActorData; }
    const MapActorData& getMapActorData() const { return mMapActorData; }

    void draw() const;

private:
    MapActorData& mMapActorData;
};
