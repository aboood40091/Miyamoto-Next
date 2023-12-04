#include <CourseView.h>
#include <MainWindow.h>
#include <course/Bg.h>
#include <course/BgRenderer.h>
#include <item/BgUnitItem.h>

#include <rio.h>

BgUnitItem::BgUnitItem(BgCourseData& data, u32 index)
    : ItemBase(ITEM_TYPE_BG_UNIT_OBJ, index, data.offset.x, data.offset.y)
    , mBgCourseData(data)
{
}

void BgUnitItem::move(s16 dx, s16 dy, bool commit)
{
    dx /= 16;
    dy /= 16;

    if (dx == 0 && dy == 0)
    {
        if (mBgCourseData.offset.x == mBasePosition.x && mBgCourseData.offset.y == mBasePosition.y)
            return;

        mBgCourseData.offset.x = mBasePosition.x;
        mBgCourseData.offset.y = mBasePosition.y;
    }
    else
    {
        mBgCourseData.offset.x = mBasePosition.x + dx;
        mBgCourseData.offset.y = mBasePosition.y + dy;
        if (commit)
        {
            mBasePosition.x = mBgCourseData.offset.x;
            mBasePosition.y = mBgCourseData.offset.y;
        }
    }
}
