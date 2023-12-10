#pragma once

#include <course/CourseDataFile.h>
#include <item/ItemBase.h>

class NextGotoItem : public ItemBase
{
public:
    NextGotoItem(NextGoto& next_goto, u32 index);

    void move(s16 dx, s16 dy, bool commit) override;
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
    NextGoto mSelectionData;
};
