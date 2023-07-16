#pragma once

#include <course/BgUnit.h>
#include <course/Constants.h>

#include <gpu/rio_Texture.h>

#include <span>
#include <string>

class BgUnitFile
{
public:
    BgUnitFile(const std::string& name);
    ~BgUnitFile();

    bool load(std::span<const u8> data);
    void unload();

    bool save();

    const std::string& getName() const
    {
        return mName;
    }

    std::span<const u8> getData() const
    {
        return mData;
    }

    u64 getBgCheck(s32 index) const
    {
        RIO_ASSERT(index < BG_MAX_PER_UNIT_NUM);
        return mBgCheck[index];
    }

    size_t getBgUnitCount() const
    {
        return mBgUnit.size();
    }

    const BgUnit& getBgUnit(u32 index) const
    {
        RIO_ASSERT(index < mBgUnit.size());
        return mBgUnit[index];
    }

    const rio::Texture2D* getTexture() const
    {
        return mpTexture;
    }

    const rio::Texture2D* getNormalTexture() const
    {
        return mpNormalTexture;
    }

private:
    std::string         mName;
    std::span<u8>       mData;

    u64                 mBgCheck[BG_MAX_PER_UNIT_NUM];

    std::vector<BgUnit> mBgUnit;

    rio::Texture2D*     mpTexture;
    rio::Texture2D*     mpNormalTexture;

    friend class Bg;
};
