#pragma once

#include <course/CourseDataFile.h>

class NextGotoItem
{
public:
    NextGotoItem(NextGoto& next_goto);

    NextGoto& getNextGoto() { return mNextGoto; }
    const NextGoto& getNextGoto() const { return mNextGoto; }

    void draw() const;

private:
    NextGoto& mNextGoto;
};
