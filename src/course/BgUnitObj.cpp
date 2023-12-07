#include <course/BgUnitObj.h>

BgUnitObj::BgUnitObj()
    : mWidth(0)
    , mHeight(0)
    , mRandom(0)
    , mMainPartAt(-1)
    , mSubPartAt(-1)
    , mIsReversed(false)
{
}

void BgUnitObj::load(u8 width, u8 height, u16 random, u16 data_offs, const void* unt, u32 unt_size)
{
    // Clear
    mMainPartAt = -1;
    mSubPartAt  = -1;
    mRows.clear();

    mWidth      = width;
    mHeight     = height;
    mRandom     = random;

    if (width && height)
        mDefaultRender = std::make_unique<UnitMtx>(width, height);
    else
        mDefaultRender.reset();

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

    if (mWidth == 0 || mHeight == 0)
        mDefaultRender.reset();

    else
    {
        mDefaultRender = std::make_unique<UnitMtx>(mWidth, mHeight);
        render(mDefaultRender->mtx, mWidth, mHeight);
    }
}

void BgUnitObj::getSlopeSections(std::vector<RefRow>& main_block, std::vector<RefRow>& sub_block) const
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
            for (const Unit& unit : mRows[i])
                if (!(unit.first & 0x80))
                    main_block[i - main_part_at].push_back(&unit);
    }

    if (sub_part_len > 0)
    {
        sub_block.resize(sub_part_len);

        for (s32 i = sub_part_at; i < sub_part_end; i++)
            for (const Unit& unit : mRows[i])
                if (!(unit.first & 0x80))
                    sub_block[i - sub_part_at].push_back(&unit);
    }
}

size_t BgUnitObj::calcRowsByteSize() const
{
    size_t size = 0;

    for (const Row& row : mRows)
    {
        for (const Unit& unit : row)
        {
            size++;
            if (!(unit.first & 0x80))
                size += 2;
        }

        size++;
    }

    size++;

    return size;
}

size_t BgUnitObj::saveRows(void* unt) const
{
    u8* p_dst = static_cast<u8*>(unt);

    for (const Row& row : mRows)
    {
        for (const Unit& unit : row)
        {
            *p_dst++ = unit.first;
            if (!(unit.first & 0x80))
            {
                *p_dst++ = unit.idx;
                *p_dst++ = unit.env | unit.extra << 2;
            }
        }

        *p_dst++ = 0xFE;
    }

    *p_dst++ = 0xFF;

    return uintptr_t(p_dst) - uintptr_t(unt);
}

void BgUnitObj::putObjectArray_(s32 xS, s32 yS, const std::vector<RefRow>& rows, const Unit** out_mtx, u32 width, u32 height)
{
    xS = std::max(0, xS);
    yS = std::max(0, yS);

    s32 yE = std::min<size_t>(height, yS + rows.size());
    for (s32 y = yS; y < yE; y++)
    {
        const Unit** drow = out_mtx + y * width;
        const RefRow& srow = rows[y - yS];

        s32 xE = std::min<size_t>(width, xS + srow.size());
        for (s32 x = xS; x < xE; x++)
            drow[x] = srow[x - xS];
    }
}

void BgUnitObj::renderDiagonal_(const Unit** out_mtx, u32 width, u32 height) const
{
    std::vector<RefRow> main_block, sub_block;
    getSlopeSections(main_block, sub_block);

    u8 cbyte = mRows[0][0].first;

    bool left = cbyte & 1;
    bool down = cbyte & 2;

    s32 main_block_height = main_block.size();
    s32 main_block_width = 0;
    for (const RefRow& row : main_block)
        if (ssize_t(row.size()) > main_block_width)
            main_block_width = row.size();

    s32 sub_block_height = sub_block.size();
    s32 sub_block_width = 0;
    for (const RefRow& row : sub_block)
        if (ssize_t(row.size()) > sub_block_width)
            sub_block_width = row.size();

    s32 draw_num = std::min(height / main_block_height, width / main_block_width);

    s32 x, y, xi, yi;

    if (!left && !down)
    {
        x = 0;
        y = height - main_block_height - sub_block_height;
        xi = main_block_width;
        yi = -main_block_height;
    }
    else if (left && !down)
    {
        x = 0;
        y = 0;
        xi = main_block_width;
        yi = main_block_height;
    }
    else if (!left && down)
    {
        x = 0;
        y = sub_block_height;
        xi = main_block_width;
        yi = main_block_height;
    }
    else
    {
        x = 0;
        y = height - main_block_height;
        xi = main_block_width;
        yi = -main_block_height;
    }

    for (s32 i = 0; i < draw_num; i++)
    {
        putObjectArray_(x, y, main_block, out_mtx, width, height);
        if (sub_block_height > 0)
        {
            s32 xb;

            if (left)
                xb = x + main_block_width - sub_block_width;
            else
                xb = x;

            if (down)
                putObjectArray_(xb, y - sub_block_height, sub_block, out_mtx, width, height);
            else
                putObjectArray_(xb, y + main_block_height, sub_block, out_mtx, width, height);
        }
        x += xi;
        y += yi;
    }
}

void BgUnitObj::processRow_(u32 y, const Row& row, const Unit** out_mtx, u32 width)
{
    if (row.size() == 0)
        return;

    const Unit** dest = out_mtx + y * width;

    bool repeat_found = false;
    RefRow repeat_before;
    RefRow repeat_in;
    RefRow repeat_after;

    for (const Unit& unit : row)
    {
        if (unit.first & 1)
        {
            repeat_found = true;
            repeat_in.push_back(&unit);
        }
        else if (repeat_found)
        {
            repeat_after.push_back(&unit);
        }
        else
        {
            repeat_before.push_back(&unit);
        }
    }

    u32 bc = repeat_before.size();
    u32 ic = repeat_in.size();
    u32 ac = repeat_after.size();

    if (ic == 0 || width <= bc)
        for (u32 x = 0; x < width; x++)
            dest[x] = repeat_before[x % bc];

    else if (width <= bc + ac)
    {
        for (u32 x = 0; x < bc; x++)
            dest[x] = repeat_before[x];

        for (u32 x = bc; x < width; x++)
            dest[x] = repeat_after[x - bc];
    }
    else
    {
        u32 after_threshold = width - ac;

        for (u32 x = 0; x < bc; x++)
            dest[x] = repeat_before[x];

        for (u32 x = bc; x < after_threshold; x++)
            dest[x] = repeat_in[(x - bc) % ic];

        for (u32 x = after_threshold; x < width; x++)
            dest[x] = repeat_after[x - after_threshold];
    }
}

void BgUnitObj::render(const Unit** out_mtx, u32 width, u32 height) const
{
    if (mRows.size() == 0)
        return;

    if (width == 0 || height == 0)
        return;

    if (mRows[0][0].first & 0x80)
    {
        renderDiagonal_(out_mtx, width, height);
        return;
    }

    bool repeat_found = false;
    std::vector<const Row*> repeat_before;
    std::vector<const Row*> repeat_in;
    std::vector<const Row*> repeat_after;

    for (const Row& row : mRows)
    {
        if (row.size() > 0 && row[0].first & 2)
        {
            repeat_found = true;
            repeat_in.push_back(&row);
        }
        else if (repeat_found)
        {
            repeat_after.push_back(&row);
        }
        else
        {
            repeat_before.push_back(&row);
        }
    }

    u32 bc = repeat_before.size();
    u32 ic = repeat_in.size();
    u32 ac = repeat_after.size();

    if (ic == 0 || height <= bc)
    {
        for (u32 y = 0; y < height; y++)
            processRow_(y, *(repeat_before[y % bc]), out_mtx, width);
    }
    else if (height <= bc + ac)
    {
        for (u32 y = 0; y < bc; y++)
            processRow_(y, *(repeat_before[y]), out_mtx, width);

        for (u32 y = bc; y < height; y++)
            processRow_(y, *(repeat_after[y - bc]), out_mtx, width);
    }
    else
    {
        u32 after_threshold = height - ac;

        for (u32 y = 0; y < bc; y++)
            processRow_(y, *(repeat_before[y]), out_mtx, width);

        for (u32 y = bc; y < after_threshold; y++)
            processRow_(y, *(repeat_in[(y - bc) % ic]), out_mtx, width);

        for (u32 y = after_threshold; y < height; y++)
            processRow_(y, *(repeat_after[y - after_threshold]), out_mtx, width);
    }
}
