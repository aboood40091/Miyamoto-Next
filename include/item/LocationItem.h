#pragma once

#include <course/CourseDataFile.h>
#include <item/ItemBase.h>

class LocationItem : public ItemBase
{
public:
    LocationItem(Location& location, u32 index);

    Location& getLocation() { return mLocation; }
    const Location& getLocation() const { return mLocation; }

    void drawOpa();
    void drawXlu();

private:
    f32 getZPos_() const
    {
        return 3600.0f - 10;
    }

private:
    Location& mLocation;
};
