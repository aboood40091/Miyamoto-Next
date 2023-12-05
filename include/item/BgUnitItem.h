#pragma once

#include <course/CourseDataFile.h>
#include <item/ItemBase.h>

class BgUnitItem : public ItemBase
{
public:
    BgUnitItem(BgCourseData& data, u32 index);

    BgCourseData& getBgCourseData() { return mBgCourseData; }
    const BgCourseData& getBgCourseData() const { return mBgCourseData; }

    void move(s16 dx, s16 dy, bool commit) override;
    void drawSelectionUI() override;

private:
    BgCourseData& mBgCourseData;

    struct SelectionData
    {
        u16 env;
        u16 idx;
        u16 width;
        u16 height;
        u8 flag;
    } mSelectionData;
};
