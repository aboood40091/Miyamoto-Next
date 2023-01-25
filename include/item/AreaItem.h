#pragma once

#include <course/CourseDataFile.h>

class AreaItem
{
public:
    AreaItem(AreaData& area);

    AreaData& getAreaData() { return mAreaData; }
    const AreaData& getAreaData() const { return mAreaData; }

    void draw() const;

private:
    AreaData& mAreaData;
};
