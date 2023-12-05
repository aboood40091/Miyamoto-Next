#include <CourseView.h>
#include <MainWindow.h>
#include <action/ActionBgUnitItemEdit.h>

#include <rio.h>

ActionBgUnitItemEdit::ActionBgUnitItemEdit(const void* context)
    : IAction(context)
    , mItemId(static_cast<const Context*>(context)->item_id)
    , mBefore(static_cast<const Context*>(context)->before)
    , mAfter(static_cast<const Context*>(context)->after)
{
}

bool ActionBgUnitItemEdit::apply() const
{
    CourseView* p_view = static_cast<MainWindow*>(rio::sRootTask)->getCourseView();
    p_view->setItemData(mItemId, &mAfter);
    return true;
}

void ActionBgUnitItemEdit::unapply() const
{
    CourseView* p_view = static_cast<MainWindow*>(rio::sRootTask)->getCourseView();
    p_view->setItemData(mItemId, &mBefore);
}
