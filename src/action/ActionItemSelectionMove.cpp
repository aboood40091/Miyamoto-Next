#include <CourseView.h>
#include <action/ActionItemSelectionMove.h>

#include <rio.h>

ActionItemSelectionMove::ActionItemSelectionMove(const void* context)
    : IAction(context)
    , mSelectedItems(static_cast<const Context*>(context)->selected_items)
    , m_dx(static_cast<const Context*>(context)->dx)
    , m_dy(static_cast<const Context*>(context)->dy)
{
}

bool ActionItemSelectionMove::apply() const
{
    CourseView::instance()->moveItems(mSelectedItems, m_dx, m_dy, true);
    return true;
}

void ActionItemSelectionMove::unapply() const
{
    CourseView::instance()->moveItems(mSelectedItems, -m_dx, -m_dy, true);
}
