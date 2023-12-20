#include <course/Bg.h>
#include <course/BgUnitFile.h>
#include <course/CourseDataFile.h>
#include <resource/SharcArchiveRes.h>

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
    const void* file = pack_arc.getFileConst(name.c_str(), &filesize);

    BgUnitFile* p_unit_file = new BgUnitFile(name);
    if (!p_unit_file->load({ (const u8*)file, filesize }))
    {
        delete p_unit_file;
        return false;
    }

    mUnitFileMap.try_emplace(name, p_unit_file);
    return true;
}

bool Bg::loadUnit(const void* file, u32 filesize, const std::string& name)
{
    if (name.empty() ||     // Case 1: Empty slot
        getUnitFile(name))  // Case 2: Slot already loaded
        return true;

    BgUnitFile* p_unit_file = new BgUnitFile(name);
    if (!p_unit_file->load({ (u8*)file, filesize }))
    {
        delete p_unit_file;
        return false;
    }

    mUnitFileMap.try_emplace(name, p_unit_file);
    return true;
}

void Bg::clear()
{
    for (auto it : mUnitFileMap)
        delete it.second;

    mUnitFileMap.clear();
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

    const BgUnitObj::UnitMtx unit_mtx(width, height);
    bg_unit_obj.render(unit_mtx.mtx, width, height);

    for (u32 y = 0; y < real_h; y++)
    {
        Unit* dest = mUnitMtx[layer][inst_y + y] + inst_x;

        for (u32 x = 0; x < real_w; x++)
        {
            const BgUnitObj::Unit* p_unit = unit_mtx.mtx[y * width + x];
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

void Bg::processBgCourseData(const CourseDataFile& cd_file, u8 layer)
{
    clearBgCourseData(layer);

    const BgUnitFile* files[CD_FILE_ENV_MAX_NUM] = {
        getUnitFile(cd_file.getEnvironment(0)),
        getUnitFile(cd_file.getEnvironment(1)),
        getUnitFile(cd_file.getEnvironment(2)),
        getUnitFile(cd_file.getEnvironment(3))
    };

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

void Bg::clearBgCourseData(u8 layer)
{
    rio::MemUtil::set(mUnitMtx[layer], 0, sizeof(mUnitMtx[layer]));
}
