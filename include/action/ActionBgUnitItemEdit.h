#pragma once

#include <action/IAction.h>
#include <item/ItemID.h>
#include <course/CourseDataFile.h>

class ActionBgUnitItemEdit : public IAction
{
    ACTION_CREATE(ActionBgUnitItemEdit)

public:
    struct Context
    {
        ItemID item_id;
        BgCourseData before;
        BgCourseData after;
    };

public:
    ActionBgUnitItemEdit(const void* context);

    bool apply() const override;
    void unapply() const override;

private:
    ItemID              mItemId;
    BgCourseData        mBefore;
    BgCourseData        mAfter;
};
