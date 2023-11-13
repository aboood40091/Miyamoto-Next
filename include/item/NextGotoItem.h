#pragma once

#include <course/CourseDataFile.h>

class NextGotoItem
{
public:
    NextGotoItem(NextGoto& next_goto);

    NextGoto& getNextGoto() { return mNextGoto; }
    const NextGoto& getNextGoto() const { return mNextGoto; }

    void drawOpa();
    void drawXlu();

private:
    f32 getZPos_() const
    {
        return 3000.0f;
    }

private:
    NextGoto& mNextGoto;
};
