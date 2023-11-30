#pragma once

#include <misc/rio_Types.h>

enum ItemType : u8
{
    ITEM_TYPE_BG_UNIT_OBJ   = 0,
    ITEM_TYPE_MAX_NUM
};

class ItemID
{
public:
    static const u32 cInvalidItemID = -1;

public:
    ItemID(u32 value)
        : mValue(value)
    {
    }

    ItemID(ItemType type, u32 index)
    {
        RIO_ASSERT(type < ITEM_TYPE_MAX_NUM);
        RIO_ASSERT(index < 0x00FFFFFF);
        mValue = type << 24 | index;
    }

    operator u32() const
    {
        return mValue;
    }

    friend bool operator==(const ItemID& lhs, const ItemID& rhs)
    {
        return lhs.mValue == rhs.mValue;
    }

    friend bool operator!=(const ItemID& lhs, const ItemID& rhs)
    {
        return lhs.mValue != rhs.mValue;
    }

    ItemType getType() const
    {
        RIO_ASSERT(isValid());
        return ItemType(mValue >> 24);
    }

    u32 getIndex() const
    {
        RIO_ASSERT(isValid());
        return mValue & 0x00FFFFFF;
    }

    bool isValid() const
    {
        return mValue != cInvalidItemID;
    }

private:
    u32 mValue;
};
