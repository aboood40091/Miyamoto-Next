#pragma once

#include <misc/rio_Types.h>

#include <vector>

struct BgUnitHead
{
    union
    {
        struct
        {
            u16 data_offs;
            u8  width;
            u8  height;
            u16 random;
        };
        u16 data[3];
    };
};
static_assert(sizeof(BgUnitHead) == 6);

class BgUnit
{
public:
    struct Tile
    {
        u8 first;
        u8 number;
        u8 env;
        u8 extra;
    };
    typedef std::vector<Tile> Row;

public:
    BgUnit();

    void load(u8 width, u8 height, u16 random, u16 data_offs, const void* unt, u32 unt_size);

    u8 getWidth() const
    {
        return mWidth;
    }

    u8 getHeight() const
    {
        return mHeight;
    }

    u8 getRandomType() const
    {
        return mRandom >> 4 & 0xf;
    }

    u8 getRandomLength() const
    {
        return mRandom & 0xf;
    }

    u16 getRandom() const
    {
        return mRandom;
    }

    s32 getSlopeMainStartRow() const
    {
        return mMainPartAt;
    }

    s32 getSlopeSubStartRow() const
    {
        return mSubPartAt;
    }

    const std::vector<Row>& getRows() const
    {
        return mRows;
    }

    void getSlopeSections(std::vector<BgUnit::Row>& main_block, std::vector<BgUnit::Row>& sub_block) const;

    size_t calcRowsByteSize() const;
    size_t saveRows(void* unt) const;

private:
    u8                  mWidth;
    u8                  mHeight;
    u16                 mRandom;

    s32                 mMainPartAt;
    s32                 mSubPartAt;

    bool                mIsReversed;

    std::vector<Row>    mRows;
};
