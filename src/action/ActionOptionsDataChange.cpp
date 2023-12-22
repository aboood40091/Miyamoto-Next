#include <CourseView.h>
#include <action/ActionOptionsDataChange.h>

ActionOptionsDataChange::ActionOptionsDataChange(const void* context)
    : IAction(context)
    , mBefore(static_cast<const Context*>(context)->before)
    , mAfter(static_cast<const Context*>(context)->after)
{
}

bool ActionOptionsDataChange::apply() const
{
    CourseView::instance()->getCourseDataFile().getOptions() = mAfter;
    return true;
}

void ActionOptionsDataChange::unapply() const
{
    CourseView::instance()->getCourseDataFile().getOptions() = mBefore;
}

ActionOptionsDataChange::Context::~Context() = default;
