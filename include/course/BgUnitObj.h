#pragma once

#include <misc/rio_Types.h>

#include <vector>

struct BgUnitObjHead
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
static_assert(sizeof(BgUnitObjHead) == 6);

class BgUnitObj
{
public:
    struct Unit
    {
        u8 first;
        u8 idx;
        u8 env;
        u8 extra;
    };
    typedef std::vector<Unit> Row;
    typedef std::vector<const Unit*> RefRow;

public:
    BgUnitObj();

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

    void getSlopeSections(std::vector<RefRow>& main_block, std::vector<RefRow>& sub_block) const;

    size_t calcRowsByteSize() const;
    size_t saveRows(void* unt) const;

    void render(const Unit** out_mtx, u32 width, u32 height) const;

private:
    static void processRow_(u32 y, const Row& row, const Unit** out_mtx, u32 width);
    static void putObjectArray_(s32 xS, s32 yS, const std::vector<RefRow>& rows, const Unit** out_mtx, u32 width, u32 height);

    void renderDiagonal_(const Unit** out_mtx, u32 width, u32 height) const;

private:
    u8                  mWidth;
    u8                  mHeight;
    u16                 mRandom;

    s32                 mMainPartAt;
    s32                 mSubPartAt;

    bool                mIsReversed;

    std::vector<Row>    mRows;
};
