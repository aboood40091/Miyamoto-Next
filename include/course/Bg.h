#pragma once

#include <course/BgUnitObj.h>
#include <course/Constants.h>
#include <course/UnitID.h>

#include <string>
#include <unordered_map>

struct BgCourseData;
class  BgUnitFile;
class  CourseDataFile;
class  SharcArchiveRes;

class Bg
{
public:
    struct Unit
    {
        UnitID  value;
        u32     obj_index;
    };

  //typedef std::array<Unit, BG_MAX_UNIT_X>                 LayerUnitRow;
  //typedef std::array<LayerUnitRow, BG_MAX_UNIT_Y>         LayerUnitMtx;
  //typedef std::array<LayerUnitMtx, CD_FILE_LAYER_MAX_NUM> UnitMtx;

    using UnitFileMap = std::unordered_map<std::string, BgUnitFile* const>;
    using UnitMtx = Unit[CD_FILE_LAYER_MAX_NUM][BG_MAX_UNIT_Y][BG_MAX_UNIT_X];

public:
    static bool createSingleton();
    static void destroySingleton();
    static Bg* instance() { return sInstance; }

private:
    static Bg* sInstance;

    Bg();
    ~Bg();

    Bg(const Bg&);
    Bg& operator=(const Bg&);

public:
    bool loadUnit(const SharcArchiveRes& pack_arc, const std::string& name);
    void clear();

    const BgUnitFile* getUnitFile(const std::string& name) const
    {
        if (!name.empty())
        {
            auto it = mUnitFileMap.find(name);
            if (it != mUnitFileMap.end())
                return it->second;
        }

        return nullptr;
    }

    const UnitFileMap& getUnitFileMap() const
    {
        return mUnitFileMap;
    }

public:
    void processBgCourseData(const CourseDataFile& cd_file);
    void clearBgCourseData();

private:
    void processBgUnitObj_(const BgUnitObj& bg_unit_obj, const BgCourseData& obj_instance, u32 obj_index, u8 layer);

public:
    UnitID getUnitID(u16 x, u16 y, u8 layer) const
    {
        RIO_ASSERT(x < BG_MAX_X);
        RIO_ASSERT(y < BG_MAX_Y);
        RIO_ASSERT(layer < CD_FILE_LAYER_MAX_NUM);
        return mUnitMtx[layer][y >> 4][x >> 4].value; // x >> 4 = x / 16
    }

    UnitMtx& getUnitMtx() { return mUnitMtx; }
    const UnitMtx& getUnitMtx() const { return mUnitMtx; }

private:
    UnitFileMap     mUnitFileMap;
    UnitMtx         mUnitMtx;
};
