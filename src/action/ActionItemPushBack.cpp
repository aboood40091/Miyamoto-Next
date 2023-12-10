#include <CourseView.h>
#include <action/ActionItemPushBack.h>

#include <rio.h>

ActionItemPushBack::ActionItemPushBack(const void* context)
    : IAction(context)
    , mItemType(static_cast<const Context*>(context)->item_type)
    , mData(static_cast<const Context*>(context)->data)
    , mExtra(static_cast<const Context*>(context)->extra)
{
}

bool ActionItemPushBack::apply() const
{
    CourseView::instance()->pushBackItem(mItemType, mData.get(), mExtra.get());
    return true;
}

void ActionItemPushBack::unapply() const
{
    CourseView::instance()->popBackItem(mItemType, mExtra.get());
}

ActionItemPushBack::Context::~Context() = default;
