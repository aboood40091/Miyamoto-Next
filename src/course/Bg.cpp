#include <course/Bg.h>
#include <course/BgUnitFile.h>
#include <course/CourseDataFile.h>
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

static inline UnitID mapUnit(u8 env, u8 idx, u8 flag)
{
    if (flag == 0)
        return UnitID(env << 8 | idx);

    RIO_ASSERT(flag <= 24);
    return UnitID(cUnit[flag - 1]);
}

}

Bg* Bg::sInstance = nullptr;

bool Bg::createSingleton()
{
    if (sInstance)
        return false;

    sInstance = new Bg();
    return true;
}

void Bg::destroySingleton()
{
    if (!sInstance)
        return;

    delete sInstance;
    sInstance = nullptr;
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
    if (name.empty() ||     // Case 1: Empty slot
        getUnitFile(name))  // Case 2: Slot already loaded
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

void Bg::processRow_(u32 y, const BgUnitObj::Row& row, const BgUnitObj::Unit** out_mtx, u32 width)
{
    if (row.size() == 0)
        return;

    const BgUnitObj::Unit** dest = out_mtx + y * width;

    bool repeat_found = false;
    std::vector<const BgUnitObj::Unit*> repeat_before;
    std::vector<const BgUnitObj::Unit*> repeat_in;
    std::vector<const BgUnitObj::Unit*> repeat_after;

    for (const BgUnitObj::Unit& unit : row)
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

void Bg::processBgUnitObj(const BgUnitObj& bg_unit_obj, const BgUnitObj::Unit** out_mtx, u32 width, u32 height)
{
    const std::vector<BgUnitObj::Row>& rows = bg_unit_obj.getRows();
    if (rows.size() == 0)
        return;

    if (width == 0 || height == 0)
        return;

    if (rows[0][0].first & 0x80)
    {
        processDiagonalBgUnitObj_(bg_unit_obj, out_mtx, width, height);
        return;
    }

    bool repeat_found = false;
    std::vector<const BgUnitObj::Row*> repeat_before;
    std::vector<const BgUnitObj::Row*> repeat_in;
    std::vector<const BgUnitObj::Row*> repeat_after;

    for (const BgUnitObj::Row& row : rows)
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

void Bg::putObjectArray_(s32 xS, s32 yS, const std::vector<BgUnitObj::Row>& rows, const BgUnitObj::Unit** out_mtx, u32 width, u32 height)
{
    xS = std::max(0, xS);
    yS = std::max(0, yS);

    s32 yE = std::min<size_t>(height, yS + rows.size());
    for (s32 y = yS; y < yE; y++)
    {
        const BgUnitObj::Unit** drow = out_mtx + y * width;
        const BgUnitObj::Row& srow = rows[y - yS];

        s32 xE = std::min<size_t>(width, xS + srow.size());
        for (s32 x = xS; x < xE; x++)
            drow[x] = &(srow[x - xS]);
    }
}

void Bg::processDiagonalBgUnitObj_(const BgUnitObj& bg_unit_obj, const BgUnitObj::Unit** out_mtx, u32 width, u32 height)
{
    std::vector<BgUnitObj::Row> main_block, sub_block;
    bg_unit_obj.getSlopeSections(main_block, sub_block);

    const std::vector<BgUnitObj::Row>& rows = bg_unit_obj.getRows();

    u8 cbyte = rows[0][0].first;

    bool left = cbyte & 1;
    bool down = cbyte & 2;

    s32 main_block_height = main_block.size();
    s32 main_block_width = 0;
    for (const BgUnitObj::Row& row : main_block)
        if (ssize_t(row.size()) > main_block_width)
            main_block_width = row.size();

    s32 sub_block_height = sub_block.size();
    s32 sub_block_width = 0;
    for (const BgUnitObj::Row& row : sub_block)
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

void Bg::processBgUnitObj_(const BgUnitObj& bg_unit_obj, const BgCourseData& obj_instance, u32 obj_index, u8 layer)
{
    RIO_ASSERT(layer < CD_FILE_LAYER_MAX_NUM);

    u32 inst_x = obj_instance.offset.x;
    u32 inst_y = obj_instance.offset.y;

    if (inst_x >= BG_MAX_UNIT_X || inst_y >= BG_MAX_UNIT_Y)
        return;

    u32 width = obj_instance.size.x;
    u32 height = obj_instance.size.y;

    u32 real_w = std::min<u32>(width,  BG_MAX_UNIT_X - inst_x);
    u32 real_h = std::min<u32>(height, BG_MAX_UNIT_Y - inst_y);

    if (real_w == 0 || real_h == 0)
        return;

    const BgUnitObj::Unit** const mtx = new const BgUnitObj::Unit*[width * height];
    rio::MemUtil::set(mtx, 0, sizeof(const BgUnitObj::Unit*) * (width * height));
    {
        processBgUnitObj(bg_unit_obj, mtx, width, height);

        for (u32 y = 0; y < real_h; y++)
        {
            Unit* dest = mUnitMtx[layer][inst_y + y] + inst_x;

            for (u32 x = 0; x < real_w; x++)
            {
                const BgUnitObj::Unit* p_unit = mtx[y * width + x];
                if (p_unit == nullptr)
                    continue;

                UnitID value = mapUnit(p_unit->env, p_unit->idx, obj_instance.flag);
                if (value == 0)
                    continue;

                dest[x].value = value;
                dest[x].obj_index = obj_index;
            }
        }
    }
    delete[] mtx;
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
        const auto& bg_data = cd_file.getBgData(layer);

        for (u32 i = 0; i < bg_data.size(); i++)
        {
            const BgCourseData& obj_instance = bg_data[i];
            if (obj_instance.type == 0x7fff)
                continue;

            u16 idx = obj_instance.type & 0x0fff;
            u16 env = obj_instance.type >> 12;
            RIO_ASSERT(env < CD_FILE_ENV_MAX_NUM);

            // TODO: BgUnitFile cache for faster access
            const BgUnitFile* file = files[env];
            RIO_ASSERT(file);

            const BgUnitObj& bg_unit_obj = file->getObj(idx);
            processBgUnitObj_(bg_unit_obj, obj_instance, i, layer);
        }
    }
}

void Bg::clearBgCourseData()
{
    rio::MemUtil::set(mUnitMtx, 0, sizeof(UnitMtx));
}
