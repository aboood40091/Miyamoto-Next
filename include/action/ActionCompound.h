#pragma once

#include <action/IAction.h>

#include <vector>

// Groups several actions so that they undo and redo as a single step.
//
// Children are added *already applied*, because ActionMgr applies each one as it is pushed.
// (apply() therefore exists only to serve redo.)
class ActionCompound : public IAction
{
public:
    explicit ActionCompound(std::string description);

    void addAction(std::unique_ptr<IAction> action);

    u32 getActionNum() const
    {
        return u32(mAction.size());
    }

    bool isEmpty() const
    {
        return mAction.empty();
    }

    void resolveDescription();

    bool apply() const override;
    void unapply() const override;

    void unapplyFirst(u32 count) const;

private:
    std::vector< std::unique_ptr<IAction> > mAction;
};
