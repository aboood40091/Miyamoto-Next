#pragma once

#include <course/CourseDataFile.h>

class LocationItem
{
public:
    LocationItem(Location& location);

    Location& getLocation() { return mLocation; }
    const Location& getLocation() const { return mLocation; }

    void draw() const;

private:
    Location& mLocation;
};
