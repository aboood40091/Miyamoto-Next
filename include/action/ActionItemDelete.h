#pragma once

#include <action/IAction.h>
#include <item/ItemID.h>

#include <array>
#include <set>
#include <vector>

class ActionItemDelete : public IAction
{
    ACTION_CREATE(ActionItemDelete)

public:
    struct Item
    {
        ItemID                      item_id;
        std::shared_ptr<const void> data;

        Item(const ItemID& item_id_, const std::shared_ptr<const void>& data_)
            : item_id(item_id_)
            , data(data_)
        {
        }

        bool operator<(const Item& rhs) const
        {
            return u32(item_id) < u32(rhs.item_id);
        }
    };

    struct Context
    {
        std::vector<Item>   items;

        ~Context();
    };

public:
    ActionItemDelete(const void* context);

    bool apply() const override;
    void unapply() const override;

private:
    std::array<std::set<Item>, ITEM_TYPE_MAX_NUM>   mItems;
};
