#include <action/ActionCompound.h>

ActionCompound::ActionCompound(std::string description)
    : IAction(nullptr)
{
    mDescription = std::move(description);
}

void ActionCompound::addAction(std::unique_ptr<IAction> action)
{
    RIO_ASSERT(action);
    mAction.emplace_back(std::move(action));
}

void ActionCompound::resolveDescription()
{
    if (!getDescription().empty())
        return;

    if (mAction.size() == 1)
        mDescription = mAction.front()->getDescription();
    else
        mDescription = std::to_string(mAction.size()) + " Changes";
}

bool ActionCompound::apply() const
{
    for (u32 i = 0; i < mAction.size(); i++)
    {
        if (!mAction[i]->apply())
        {
            unapplyFirst(i);
            return false;
        }
    }

    return true;
}

void ActionCompound::unapply() const
{
    unapplyFirst(u32(mAction.size()));
}

void ActionCompound::unapplyFirst(u32 count) const
{
    RIO_ASSERT(count <= mAction.size());

    for (u32 i = count; i > 0; i--)
        mAction[i - 1]->unapply();
}
