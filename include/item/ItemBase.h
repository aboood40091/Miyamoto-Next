#pragma once

#include <item/ItemID.h>

class ItemBase
{
protected:
    ItemBase(ItemType type, u32 index, u16 x, u16 y)
        : mItemID(type, index)
        , mIsSelected(false)
    {
        mBasePosition.x = x;
        mBasePosition.y = y;
    }

    virtual ~ItemBase()
    {
    }

public:
    const ItemID& getItemID() const
    {
        return mItemID;
    }

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

    virtual void move(s16 dx, s16 dy, bool commit) = 0;
    virtual void drawSelectionUI() = 0;

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

    struct { u16 x, y; } mBasePosition;
};
