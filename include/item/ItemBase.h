#pragma once

#include <item/ItemID.h>

class ItemBase
{
protected:
    ItemBase(ItemType type, u32 index)
        : mItemID(type, index)
        , mIsSelected(false)
    {
    }

public:
    void setIndex(u32 index)
    {
        mItemID.setIndex(index);
        onIndexChange_();
    }

    void setSelection(bool is_selected)
    {
        mIsSelected = is_selected;
        onSelectionChange_();
    }

protected:
    virtual void onIndexChange_()
    {
    }

    virtual void onSelectionChange_()
    {
    }

protected:
    ItemID  mItemID;
    bool    mIsSelected;
};
