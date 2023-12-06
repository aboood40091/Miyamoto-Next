#pragma once

#include <course/CourseDataFile.h>
#include <item/ItemBase.h>

class NextGotoItem : public ItemBase
{
public:
    NextGotoItem(NextGoto& next_goto, u32 index);

    NextGoto& getNextGoto() { return mNextGoto; }
    const NextGoto& getNextGoto() const { return mNextGoto; }

    void move(s16 dx, s16 dy, bool commit) override
    {
        mNextGoto.offset.x = mBasePosition.x + dx;
        mNextGoto.offset.y = mBasePosition.y + dy;
        if (commit)
        {
            mBasePosition.x = mNextGoto.offset.x;
            mBasePosition.y = mNextGoto.offset.y;
        }
    }

    void drawSelectionUI() override;

    void drawOpa();
    void drawXlu();

private:
    f32 getZPos_() const
    {
        return 3000.0f;
    }

    void onSelectionChange_() override;

private:
    NextGoto& mNextGoto;
    NextGoto mSelectionData;
};
