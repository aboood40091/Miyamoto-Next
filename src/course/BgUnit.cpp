#include <course/BgUnit.h>

BgUnit::BgUnit()
    : mWidth(0)
    , mHeight(0)
    , mRandom(0)
    , mMainPartAt(-1)
    , mSubPartAt(-1)
    , mIsReversed(false)
{
}

void BgUnit::load(u8 width, u8 height, u16 random, u16 data_offs, const void* unt, u32 unt_size)
{
    // Clear
    mMainPartAt = -1;
    mSubPartAt  = -1;
    mRows.clear();

    mWidth      = width;
    mHeight     = height;
    mRandom     = random;

    const u8* source = static_cast<const u8*>(unt) + data_offs;

    RIO_ASSERT(0 < unt_size);
    mIsReversed = (source[0] & (0x80 | 2));

    u32 i = 0;
    Row row;

    while (true)
    {
        RIO_ASSERT(i < unt_size);
        u8 cbyte = source[i];

        if (cbyte == 0xFF)
            break;

        else if (cbyte == 0xFE)
        {
            i++;
            mRows.push_back(row);
            row.clear();
        }
        else if (cbyte & 0x80)
        {
            if (mMainPartAt == -1)
            {
                RIO_ASSERT(mRows.size() == 0);
                mMainPartAt = mRows.size();
            }
            else
            {
                RIO_ASSERT(mSubPartAt == -1);
                mSubPartAt = mRows.size();
            }

            row.push_back({ cbyte });
            i++;
        }
        else
        {
            RIO_ASSERT(i + 2 < unt_size);
            u8 extra = source[i + 2];
            row.push_back({ cbyte, source[i + 1], u8(extra & 3), u8(extra >> 2) });
            i += 3;
        }
    }

    if (mMainPartAt != -1 && mSubPartAt == -1)
        mSubPartAt = mRows.size();
}

void BgUnit::getSlopeSections(std::vector<BgUnit::Row>& main_block, std::vector<BgUnit::Row>& sub_block) const
{
    main_block.clear();
    sub_block.clear();

    if (mMainPartAt == -1)
        return;

    s32 main_part_at = mMainPartAt;
    s32 sub_part_at = mSubPartAt;

    RIO_ASSERT(main_part_at != -1 && sub_part_at != -1);

    s32 main_part_end = sub_part_at;
    s32 sub_part_end = mRows.size();

    s32 main_part_len = main_part_end - main_part_at;
    s32 sub_part_len = sub_part_end - sub_part_at;

    RIO_ASSERT(main_part_len > 0);
    {
        main_block.resize(main_part_len);

        for (s32 i = main_part_at; i < main_part_end; i++)
            for (const BgUnit::Tile& tile : mRows[i])
                if (!(tile.first & 0x80))
                    main_block[i - main_part_at].push_back(tile);
    }

    if (sub_part_len > 0)
    {
        sub_block.resize(sub_part_len);

        for (s32 i = sub_part_at; i < sub_part_end; i++)
            for (const BgUnit::Tile& tile : mRows[i])
                if (!(tile.first & 0x80))
                    sub_block[i - sub_part_at].push_back(tile);
    }
}

size_t BgUnit::calcRowsByteSize() const
{
    size_t size = 0;

    for (const Row& row : mRows)
    {
        for (const Tile& tile : row)
        {
            size++;
            if (!(tile.first & 0x80))
                size += 2;
        }

        size++;
    }

    size++;

    return size;
}

size_t BgUnit::saveRows(void* unt) const
{
    u8* p_dst = static_cast<u8*>(unt);

    for (const Row& row : mRows)
    {
        for (const Tile& tile : row)
        {
            *p_dst++ = tile.first;
            if (!(tile.first & 0x80))
            {
                *p_dst++ = tile.number;
                *p_dst++ = tile.env | tile.extra << 2;
            }
        }

        *p_dst++ = 0xFE;
    }

    *p_dst++ = 0xFF;

    return uintptr_t(p_dst) - uintptr_t(unt);
}
