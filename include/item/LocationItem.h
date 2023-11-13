#pragma once

#include <course/CourseDataFile.h>

class LocationItem
{
public:
    LocationItem(Location& location);

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
