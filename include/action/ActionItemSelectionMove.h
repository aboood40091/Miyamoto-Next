#pragma once

#include <action/IAction.h>
#include <item/ItemID.h>

#include <vector>

class ActionItemSelectionMove : public IAction
{
    ACTION_CREATE(ActionItemSelectionMove)

public:
    struct Context
    {
        const std::vector<ItemID>&  selected_items;
        s16                         dx;
        s16                         dy;
    };

public:
    ActionItemSelectionMove(const void* context);

    bool apply() const override;
    void unapply() const override;

private:
    std::vector<ItemID> mSelectedItems;
    s16                 m_dx;
    s16                 m_dy;
};
