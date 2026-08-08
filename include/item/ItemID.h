#pragma once

#include <item/ItemType.h>

class ItemID
{
public:
    static const u32 cInvalidItemID = -1;

public:
    ItemID(u32 value)
        : mValue(value)
    {
        if (isValid())
        {
            RIO_ASSERT(getType() < ITEM_TYPE_MAX_NUM);
        }
    }

    ItemID(ItemType type, u32 index)
    {
        set(type, index);
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

    static u32 getType(u32 value)
    {
        RIO_ASSERT(isValid(value));
        return value >> 24;
    }

    ItemType getType() const
    {
        return ItemType(getType(mValue));
    }

    static u32 getIndex(u32 value)
    {
        RIO_ASSERT(isValid(value));
        return value & 0x00FFFFFF;
    }

    u32 getIndex() const
    {
        return getIndex(mValue);
    }

    void set(ItemType type, u32 index)
    {
        RIO_ASSERT(type < ITEM_TYPE_MAX_NUM);
        RIO_ASSERT(index <= 0x00FFFFFF);
        mValue = type << 24 | index;
    }

    void setIndex(u32 index)
    {
        RIO_ASSERT(isValid());
        RIO_ASSERT(index <= 0x00FFFFFF);
        mValue &= ~0x00FFFFFF;
        mValue |= index;
    }

    static bool isValid(u32 value)
    {
        return value != cInvalidItemID;
    }

    bool isValid() const
    {
        return isValid(mValue);
    }

private:
    u32 mValue;
};
static_assert(sizeof(ItemID) == sizeof(u32));
