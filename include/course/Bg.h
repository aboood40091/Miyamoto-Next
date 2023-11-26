#pragma once

#include <course/BgUnit.h>
#include <course/Constants.h>

#include <string>
#include <unordered_map>

struct BgCourseData;
class  BgUnitFile;
class  CourseDataFile;
class  SharcArchiveRes;

class Bg
{
public:
  //typedef std::array<u16, BG_MAX_UNIT_X>                          LayerBlockUnitRow;
  //typedef std::array<LayerBlockUnitRow, BG_MAX_UNIT_Y>            LayerBlockUnitArray;
  //typedef std::array<LayerBlockUnitArray, CD_FILE_LAYER_MAX_NUM>  BlockUntArray;

    using BgUnitFileMap = std::unordered_map<std::string, BgUnitFile* const>;
    using BlockUntArray = u16[CD_FILE_LAYER_MAX_NUM][BG_MAX_UNIT_Y][BG_MAX_UNIT_X];

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
            auto it = mpBgUnitFile.find(name);
            if (it != mpBgUnitFile.end())
                return it->second;
        }

        return nullptr;
    }

    const BgUnitFileMap& getUnitFileMap() const
    {
        return mpBgUnitFile;
    }

public:
    void processBgCourseData(const CourseDataFile& cd_file);
    void clearBgCourseData();

private:
    void processRow_(u8 layer, u32 y, const BgUnit::Row& row, const BgCourseData& obj);
    void putObjectArray_(u8 layer, s32 xS, s32 yS, const std::vector<BgUnit::Row>& rows, const BgCourseData& obj);

    void processBgUnit_(const BgUnit& bg_unit, const BgCourseData& obj, u8 layer);
    void processDiagonalBgUnit_(const BgUnit& bg_unit, const BgCourseData& obj, u8 layer);

public:
    u16 getUnitNumber(u16 x, u16 y, u8 layer) const
    {
        RIO_ASSERT(x < BG_MAX_X);
        RIO_ASSERT(y < BG_MAX_Y);
        RIO_ASSERT(layer < CD_FILE_LAYER_MAX_NUM);
        return mBlockUnitNumber[layer][y >> 4][x >> 4]; // x >> 4 = x / 16
    }

    BlockUntArray& getUnitNumberArray() { return mBlockUnitNumber; }
    const BlockUntArray& getUnitNumberArray() const { return mBlockUnitNumber; }

private:
    BgUnitFileMap   mpBgUnitFile;
    BlockUntArray   mBlockUnitNumber;
};
