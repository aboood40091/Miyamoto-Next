#include <CourseView.h>
#include <MainWindow.h>
#include <action/ActionItemDataChange.h>

#include <rio.h>

ActionItemDataChange::ActionItemDataChange(const void* context)
    : IAction(context)
    , mItemID(static_cast<const Context*>(context)->item_id)
    , mBefore(static_cast<const Context*>(context)->before)
    , mAfter(static_cast<const Context*>(context)->after)
{
}

bool ActionItemDataChange::apply() const
{
    CourseView* p_view = static_cast<MainWindow*>(rio::sRootTask)->getCourseView();
    p_view->setItemData(mItemID, mAfter.get());
    return true;
}

void ActionItemDataChange::unapply() const
{
    CourseView* p_view = static_cast<MainWindow*>(rio::sRootTask)->getCourseView();
    p_view->setItemData(mItemID, mBefore.get());
}