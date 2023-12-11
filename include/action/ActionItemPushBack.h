#pragma once

#include <action/IAction.h>
#include <item/ItemType.h>

class ActionItemPushBack : public IAction
{
    ACTION_CREATE(ActionItemPushBack)

public:
    struct Context
    {
        ItemType                    item_type;
        std::shared_ptr<const void> data;
        std::shared_ptr<const void> extra;

        ~Context();
    };

public:
    ActionItemPushBack(const void* context);

    bool apply() const override;
    void unapply() const override;

private:
    ItemType                    mItemType;
    std::shared_ptr<const void> mData;
    std::shared_ptr<const void> mExtra;
};
