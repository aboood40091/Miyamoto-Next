#pragma once

#include <course/CourseDataFile.h>
#include <item/ItemBase.h>

class BgUnitItem : public ItemBase
{
public:
    BgUnitItem(BgCourseData& data, u32 index);

    void move(s16 dx, s16 dy, bool commit) override;
    void drawSelectionUI() override;

private:
    void onSelectionChange_();

private:
    BgCourseData mSelectionData;
};
