#pragma once

#include <course/CourseDataFile.h>

class AreaItem
{
public:
    AreaItem(AreaData& area);

    AreaData& getAreaData() { return mAreaData; }
    const AreaData& getAreaData() const { return mAreaData; }

    void drawOpa();
    void drawXlu();

private:
    f32 getZPos_() const
    {
        return 3600.0f;
    }

private:
    AreaData& mAreaData;
};
