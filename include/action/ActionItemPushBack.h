#pragma once

#include <action/IAction.h>
#include <item/ItemType.h>

#include <vector>

class ActionItemPushBack : public IAction
{
    ACTION_CREATE(ActionItemPushBack)

public:
    struct Item
    {
        ItemType                    item_type;
        std::shared_ptr<const void> data;
        std::shared_ptr<const void> extra;
    };

    struct Context
    {
        std::vector<Item>   items;

        ~Context();
    };

public:
    ActionItemPushBack(const void* context);

    bool apply() const override;
    void unapply() const override;

private:
    std::vector<Item>   mItems;
};
