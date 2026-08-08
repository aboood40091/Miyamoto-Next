#include <CourseView.h>
#include <action/ActionItemSelectionMove.h>

ActionItemSelectionMove::ActionItemSelectionMove(const void* context)
    : IAction(context)
    , mSelectedItems(static_cast<const Context*>(context)->selected_items)
    , m_dx(static_cast<const Context*>(context)->dx)
    , m_dy(static_cast<const Context*>(context)->dy)
{
    RIO_ASSERT(!mSelectedItems.empty());

    const ItemType first_type = mSelectedItems.front().getType();
    bool same_type = true;
    for (const ItemID& item_id : mSelectedItems)
    {
        if (item_id.getType() != first_type)
        {
            same_type = false;
            break;
        }
    }

    mDescription = (
        "Move " + (
            same_type
                ? getItemCountText(u32(mSelectedItems.size()), first_type)
                : getItemCountText(u32(mSelectedItems.size()))
        )
    );
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
