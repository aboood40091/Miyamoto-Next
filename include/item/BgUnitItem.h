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
    void onSelectionChange_();

private:
    BgCourseData& mBgCourseData;
    BgCourseData mSelectionData;
};
