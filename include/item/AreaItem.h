#pragma once

#include <course/CourseDataFile.h>

class AreaItem
{
public:
    explicit AreaItem(u32 index);

    void setIndex(u32 index) { mIndex = index; }

    void drawOpa();
    void drawXlu();

private:
    f32 getZPos_() const
    {
        return 3600.0f;
    }

private:
    u32 mIndex;
};
