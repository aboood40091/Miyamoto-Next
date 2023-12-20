#pragma once

#include <course/BgUnitObj.h>
#include <course/Constants.h>

#include <gpu/rio_Texture.h>

#include <span>
#include <string>

class BgUnitFile
{
    struct TextureFile
    {
        rio::Texture2D* p_tex = nullptr;
        std::span<u8>   data;
    };

public:
    BgUnitFile(const std::string& name);
    ~BgUnitFile();

    bool load(std::span<const u8> data);
    void unload();

    std::span<u8> save() const;

    const std::string& getName() const
    {
        return mName;
    }

    u64 getBgCheck(s32 index) const
    {
        RIO_ASSERT(index < BG_MAX_PER_UNIT_NUM);
        return mBgCheck[index];
    }

    size_t getObjCount() const
    {
        return mObj.size();
    }

    const BgUnitObj& getObj(u32 index) const
    {
        RIO_ASSERT(index < mObj.size());
        return mObj[index];
    }

    const rio::Texture2D* getTexture() const
    {
        return mTextureFile.p_tex;
    }

    const rio::Texture2D* getNormalTexture() const
    {
        return mNormalTextureFile.p_tex;
    }

    const rio::Texture2D* getAnimeTexture(AnimeType type) const
    {
        return mAnimeTextureFile[type].p_tex;
    }

private:
    std::string             mName;

    u64                     mBgCheck[BG_MAX_PER_UNIT_NUM];

    std::vector<BgUnitObj>  mObj;

    TextureFile             mTextureFile;
    TextureFile             mNormalTextureFile;
    TextureFile             mAnimeTextureFile[ANIME_TYPE_MAX];
};
