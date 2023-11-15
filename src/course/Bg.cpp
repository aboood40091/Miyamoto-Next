#include <course/Bg.h>
#include <course/BgUnitFile.h>
#include <course/CourseDataFile.h>
#include <course/UnitID.h>
#include <resource/SharcArchiveRes.h>

#include <misc/rio_MemUtil.h>

namespace {

static const u8 cUnit[24] = {
    cUnitID_BrickBlockCoin,
    cUnitID_BrickBlockCoin10,
    cUnitID_BrickBlockFireFlower,
    cUnitID_BrickBlockStar,
    cUnitID_BrickBlock1UP,
    cUnitID_BrickBlockVine,
    cUnitID_BrickBlockMiniMushroom,
    cUnitID_BrickBlockPropeller,
    cUnitID_BrickBlockPenguin,
    cUnitID_BrickBlockYoshiEgg,
    cUnitID_BrickBlockIceFlower,
    cUnitID_BrickBlockAcorn,
    cUnitID_QBlock,
    cUnitID_QBlockFireFlower,
    cUnitID_QBlockStar,
    cUnitID_QBlockCoinStar,
    cUnitID_QBlockVine,
    cUnitID_QBlockSpring,
    cUnitID_QBlockMiniMushroom,
    cUnitID_QBlockPropeller,
    cUnitID_QBlockPenguin,
    cUnitID_QBlockYoshiEgg,
    cUnitID_QBlockIceFlower,
    cUnitID_QBlockAcorn
};

static inline u16 mapUnitNo(u8 env, u8 number, u8 flag)
{
    if (flag == 0)
        return env << 8 | number;

    RIO_ASSERT(flag <= 24);
    return cUnit[flag - 1];
}

}

Bg::Bg()
{
}

Bg::~Bg()
{
    clear();
}

bool Bg::loadUnit(const SharcArchiveRes& pack_arc, const std::string& name)
{
    if (name.empty() ||     // Case 1: No tileset
        getUnitFile(name))  // Case 2: Tileset already loaded
        return true;

    u32 filesize = 0;
    void* file = pack_arc.getFile(name.c_str(), &filesize);

    BgUnitFile* p_unit_file = new BgUnitFile(name);
    if (!p_unit_file->load({ (u8*)file, filesize }))
    {
        delete p_unit_file;
        return false;
    }

    mpBgUnitFile.try_emplace(name, p_unit_file);
    return true;
}

void Bg::clear()
{
    for (auto it : mpBgUnitFile)
        delete it.second;

    mpBgUnitFile.clear();
}

void Bg::processRow_(u8 layer, u32 y, const BgUnit::Row& row, const BgCourseData& obj)
{
    if (row.size() == 0)
        return;

    u16* dest = &mBlockUnitNumber[layer][obj.offset.y + y][obj.offset.x];

    bool repeat_found = false;
    std::vector<const BgUnit::Tile*> repeat_before;
    std::vector<const BgUnit::Tile*> repeat_in;
    std::vector<const BgUnit::Tile*> repeat_after;

    for (const BgUnit::Tile& tile : row)
    {
        if (tile.first & 1)
        {
            repeat_found = true;
            repeat_in.push_back(&tile);
        }
        else if (repeat_found)
        {
            repeat_after.push_back(&tile);
        }
        else
        {
            repeat_before.push_back(&tile);
        }
    }

    u32 bc = repeat_before.size();
    u32 ic = repeat_in.size();
    u32 ac = repeat_after.size();

    if (ic == 0)
    {
        for (u32 x = 0; x < obj.size.x; x++)
        {
            const BgUnit::Tile& tile = *(repeat_before[x % bc]);
            u16 value = mapUnitNo(tile.env, tile.number, obj.flag);
            if (value == 0)
                continue;

            dest[x] = value;
        }
    }
    else if (obj.size.x <= bc + ac)
    {
        for (u32 x = 0; x < bc; x++)
        {
            const BgUnit::Tile& tile = *(repeat_before[x]);
            u16 value = mapUnitNo(tile.env, tile.number, obj.flag);
            if (value == 0)
                continue;

            dest[x] = value;
        }

        for (u32 x = bc; x < obj.size.x; x++)
        {
            const BgUnit::Tile& tile = *(repeat_after[x - bc]);
            u16 value = mapUnitNo(tile.env, tile.number, obj.flag);
            if (value == 0)
                continue;

            dest[x] = value;
        }
    }
    else
    {
        u32 after_threshold = u32(obj.size.x) - ac;

        for (u32 x = 0; x < bc; x++)
        {
            const BgUnit::Tile& tile = *(repeat_before[x]);
            u16 value = mapUnitNo(tile.env, tile.number, obj.flag);
            if (value == 0)
                continue;

            dest[x] = value;
        }

        for (u32 x = bc; x < after_threshold; x++)
        {
            const BgUnit::Tile& tile = *(repeat_in[(x - bc) % ic]);
            u16 value = mapUnitNo(tile.env, tile.number, obj.flag);
            if (value == 0)
                continue;

            dest[x] = value;
        }

        for (u32 x = after_threshold; x < obj.size.x; x++)
        {
            const BgUnit::Tile& tile = *(repeat_after[x - after_threshold]);
            u16 value = mapUnitNo(tile.env, tile.number, obj.flag);
            if (value == 0)
                continue;

            dest[x] = value;
        }
    }
}

void Bg::processBgUnit_(const BgUnit& bg_unit, const BgCourseData& obj, u8 layer)
{
    const std::vector<BgUnit::Row>& rows = bg_unit.getRows();
    if (rows.size() == 0)
        return;

    if (rows[0][0].first & 0x80)
    {
        processDiagonalBgUnit_(bg_unit, obj, layer);
        return;
    }

    bool repeat_found = false;
    std::vector<const BgUnit::Row*> repeat_before;
    std::vector<const BgUnit::Row*> repeat_in;
    std::vector<const BgUnit::Row*> repeat_after;

    for (const BgUnit::Row& row : rows)
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

    if (ic == 0)
    {
        for (u32 y = 0; y < obj.size.y; y++)
            processRow_(layer, y, *(repeat_before[y % bc]), obj);
    }
    else if (obj.size.y <= bc + ac)
    {
        for (u32 y = 0; y < bc; y++)
            processRow_(layer, y, *(repeat_before[y]), obj);

        for (u32 y = bc; y < obj.size.y; y++)
            processRow_(layer, y, *(repeat_after[y - bc]), obj);
    }
    else
    {
        u32 after_threshold = u32(obj.size.y) - ac;

        for (u32 y = 0; y < bc; y++)
            processRow_(layer, y, *(repeat_before[y]), obj);

        for (u32 y = bc; y < after_threshold; y++)
            processRow_(layer, y, *(repeat_in[(y - bc) % ic]), obj);

        for (u32 y = after_threshold; y < obj.size.y; y++)
            processRow_(layer, y, *(repeat_after[y - after_threshold]), obj);
    }
}

void Bg::putObjectArray_(u8 layer, s32 xS, s32 yS, const std::vector<BgUnit::Row>& rows, const BgCourseData& obj)
{
    xS = std::max(0, xS);
    yS = std::max(0, yS);

    s32 yE = yS + std::min(size_t(obj.size.y), rows.size());
    for (s32 y = yS; y < yE; y++)
    {
        u16* drow = &mBlockUnitNumber[layer][obj.offset.y + y][obj.offset.x];
        const BgUnit::Row& srow = rows[y - yS];

        s32 xE = xS + std::min(size_t(obj.size.x), srow.size());
        for (s32 x = xS; x < xE; x++)
        {
            const BgUnit::Tile& tile = srow[x - xS];
            u16 value = mapUnitNo(tile.env, tile.number, obj.flag);
            if (value == 0)
                continue;

            drow[x] = value;
        }
    }
}

void Bg::processDiagonalBgUnit_(const BgUnit& bg_unit, const BgCourseData& obj, u8 layer)
{
    std::vector<BgUnit::Row> main_block, sub_block;
    bg_unit.getSlopeSections(main_block, sub_block);

    const std::vector<BgUnit::Row>& rows = bg_unit.getRows();

    u8 cbyte = rows[0][0].first;

    bool left = cbyte & 1;
    bool down = cbyte & 2;

    s32 main_block_height = main_block.size();
    s32 main_block_width = 0;
    for (const BgUnit::Row& row : main_block)
        if (ssize_t(row.size()) > main_block_width)
            main_block_width = row.size();

    s32 sub_block_height = sub_block.size();
    s32 sub_block_width = 0;
    for (const BgUnit::Row& row : sub_block)
        if (ssize_t(row.size()) > sub_block_width)
            sub_block_width = row.size();

    s32 draw_num = std::min(obj.size.y / main_block_height, obj.size.x / main_block_width);

    s32 x, y, xi, yi;

    if (!left && !down)
    {
        x = 0;
        y = obj.size.y - main_block_height - sub_block_height;
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
        y = obj.size.y - main_block_height;
        xi = main_block_width;
        yi = -main_block_height;
    }

    for (s32 i = 0; i < draw_num; i++)
    {
        putObjectArray_(layer, x, y, main_block, obj);
        if (sub_block_height > 0)
        {
            s32 xb;

            if (left)
                xb = x + main_block_width - sub_block_width;
            else
                xb = x;

            if (down)
                putObjectArray_(layer, xb, y - sub_block_height, sub_block, obj);
            else
                putObjectArray_(layer, xb, y + main_block_height, sub_block, obj);
        }
        x += xi;
        y += yi;
    }
}

void Bg::processBgCourseData(const CourseDataFile& cd_file)
{
    clearBgCourseData();

    const BgUnitFile* files[CD_FILE_ENV_MAX_NUM] = {
        getUnitFile(cd_file.getEnvironment(0)),
        getUnitFile(cd_file.getEnvironment(1)),
        getUnitFile(cd_file.getEnvironment(2)),
        getUnitFile(cd_file.getEnvironment(3))
    };

    for (u8 layer = 0; layer < 3; layer++)
    {
        for (const BgCourseData& obj : cd_file.getBgData(layer))
        {
            if (obj.type == 0x7fff)
                continue;

            u16 idx = obj.type & 0x0fff;
            u16 env = obj.type >> 12;
            RIO_ASSERT(env < CD_FILE_ENV_MAX_NUM);

            // TODO: BgUnitFile cache for faster access
            const BgUnitFile* file = files[env];
            RIO_ASSERT(file);

            const BgUnit& bg_unit = file->getBgUnit(idx);
            processBgUnit_(bg_unit, obj, layer);
        }
    }
}

void Bg::clearBgCourseData()
{
    rio::MemUtil::set(mBlockUnitNumber, 0, sizeof(BlockUntArray));
}
