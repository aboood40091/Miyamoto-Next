#include <course/BgUnitFile.h>
#include <graphics/Texture2DUtil.h>
#include <resource/SharcArchiveRes.h>
#include <resource/SharcWriter.h>

#include <misc/rio_MemUtil.h>

#include <cstring>

namespace {

static inline void initializeSpan(std::span<u8>* p_data_span, const void* data, u32 size)
{
    *p_data_span = std::span(static_cast<u8*>(rio::MemUtil::alloc(size, 4)), size);
    rio::MemUtil::copy(p_data_span->data(), data, size);
}

static inline void destroySpan(std::span<u8>* p_data_span)
{
    if (p_data_span->data())
    {
        rio::MemUtil::free(p_data_span->data());
        *p_data_span = std::span<u8>();
    }
}

}

static const char* const cAnimeFilename[ANIME_TYPE_MAX] = {
    "BG_tex/hatena_anime.gtx",
    "BG_tex/block_anime.gtx",
    "BG_tex/tuka_coin_anime.gtx",
    "BG_tex/belt_conveyor_anime.gtx",
    "BG_tex/hatena_anime_L.gtx",
    "BG_tex/block_anime_L.gtx"
};

BgUnitFile::BgUnitFile(const std::string& name)
    : mName(name)
{
    RIO_ASSERT(!mName.empty());
}

BgUnitFile::~BgUnitFile()
{
    unload();
}

void BgUnitFile::unload()
{
    rio::MemUtil::set(mBgCheck, 0, sizeof(u64) * BG_MAX_PER_UNIT_NUM);

    mObj.clear();

    Texture2DUtil::destroy(&mTextureFile.p_tex);        destroySpan(&mTextureFile.data);
    Texture2DUtil::destroy(&mNormalTextureFile.p_tex);  destroySpan(&mNormalTextureFile.data);

    for (s32 i = 0; i < ANIME_TYPE_MAX; i++)
    {
        Texture2DUtil::destroy(&mAnimeTextureFile[i].p_tex);
        destroySpan(&mAnimeTextureFile[i].data);
    }
}

bool BgUnitFile::load(std::span<const u8> data)
{
    unload();

    const u8* file = data.data();
    u32 filesize = data.size();

    if (!file || !filesize)
    {
        RIO_LOG("\"%s\" does not exist or is empty.\n", mName.c_str());
        return false;
    }

    SharcArchiveRes archive;
    if (!archive.prepareArchive(file))
    {
        RIO_LOG("\"%s\" is not a Sharc file.\n", mName.c_str());
        unload();
        return false;
    }

    const std::string chk_name = "BG_chk/d_bgchk_" + mName + ".bin";        // Bg Check (Collision)

    u32 chk_filesize = 0;
    const void* const chk = archive.getFileConst(chk_name.c_str(), &chk_filesize);

    if (!(chk_filesize >= sizeof(u64) * BG_MAX_PER_UNIT_NUM))
    {
        RIO_LOG("\"%s\" missing collision.\n", mName.c_str());
        unload();
        return false;
    }

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    rio::MemUtil::copy(mBgCheck, chk, sizeof(u64) * BG_MAX_PER_UNIT_NUM);
#else
    {
        const u64* const p_src = static_cast<const u64*>(chk);
        for (s32 i = 0; i < BG_MAX_PER_UNIT_NUM; i++)
            mBgCheck[i] = __builtin_bswap64(p_src[i]);
    }
#endif

    const std::string uhd_name = "BG_unt/"         + mName + "_hd.bin";     // Unit Head Data
    const std::string unt_name = "BG_unt/"         + mName + ".bin";        // Unit Data

    u32 uhd_filesize = 0;
    u32 unt_filesize = 0;

    const void* const uhd = archive.getFileConst(uhd_name.c_str(), &uhd_filesize);
    const void* const unt = archive.getFileConst(unt_name.c_str(), &unt_filesize);

    if (!(uhd && unt))
    {
        RIO_LOG("\"%s\" missing unit data.\n", mName.c_str());
        unload();
        return false;
    }

    {
        u32 size = uhd_filesize;
        RIO_ASSERT(size % sizeof(BgUnitObjHead) == 0);
        u32 count = size / sizeof(BgUnitObjHead);

        mObj.resize(count);

        const BgUnitObjHead* p_src = static_cast<const BgUnitObjHead*>(uhd);

        for (u32 i = 0; i < count; i++)
        {
            const BgUnitObjHead&    src = p_src[i];
            BgUnitObjHead           dst;

            dst.data[0] = CD_FILE_READ_16_BE(src.data[0]);
            dst.data[1] =                    src.data[1];   // Yes, this is a u16 and endianness is not reversed.
            dst.data[2] = CD_FILE_READ_16_BE(src.data[2]);

            mObj[i].load(dst.width, dst.height, dst.random, dst.data_offs, unt, unt_filesize);
        }
    }

    const std::string tex_name = "BG_tex/"         + mName + ".gtx";        // Texture Data
    const std::string nml_name = "BG_tex/"         + mName + "_nml.gtx";    // Normal Map Texture Data

    u32 tex_filesize = 0;
    u32 nml_filesize = 0;

    const void* const tex = archive.getFileConst(tex_name.c_str(), &tex_filesize);
    const void* const nml = archive.getFileConst(nml_name.c_str(), &nml_filesize);

    switch (Texture2DUtil::createFromGTX(std::span<const u8> { (const u8*)tex, tex_filesize }, &mTextureFile.p_tex))
    {
    case Texture2DUtil::GTX_ERROR_OK:
        initializeSpan(&mTextureFile.data, tex, tex_filesize);
        break;
    case Texture2DUtil::GTX_ERROR_SRC_TOO_SHORT:
    case Texture2DUtil::GTX_ERROR_SRC_EMPTY:
        RIO_LOG("\"%s\" texture: missing.\n", mName.c_str());
        unload();
        return false;
    case Texture2DUtil::GTX_ERROR_SRC_INVALID:
        RIO_LOG("\"%s\" texture: invalid GFD texture.\n", mName.c_str());
        unload();
        return false;
    case Texture2DUtil::GTX_ERROR_UNSUPPORTED_FORMAT:
        RIO_LOG("\"%s\" texture: unsupported format.\n", mName.c_str());
        unload();
        return false;
    }

    switch (Texture2DUtil::createFromGTX(std::span<const u8> { (const u8*)nml, nml_filesize }, &mNormalTextureFile.p_tex))
    {
    case Texture2DUtil::GTX_ERROR_OK:
        initializeSpan(&mNormalTextureFile.data, nml, nml_filesize);
        break;
    case Texture2DUtil::GTX_ERROR_SRC_TOO_SHORT:
    case Texture2DUtil::GTX_ERROR_SRC_EMPTY:
        RIO_LOG("\"%s\" normal texture: missing.\n", mName.c_str());
        unload();
        return false;
    case Texture2DUtil::GTX_ERROR_SRC_INVALID:
        RIO_LOG("\"%s\" normal texture: invalid GFD texture.\n", mName.c_str());
        unload();
        return false;
    case Texture2DUtil::GTX_ERROR_UNSUPPORTED_FORMAT:
        RIO_LOG("\"%s\" normal texture: unsupported format.\n", mName.c_str());
        unload();
        return false;
    }

    for (s32 i = 0; i < ANIME_TYPE_MAX; i++)
    {
        u32 anm_filesize = 0;
        const void* const anm = archive.getFileConst(cAnimeFilename[i], &anm_filesize);
        if (Texture2DUtil::createFromGTX(std::span<const u8> { (const u8*)anm, anm_filesize }, &mAnimeTextureFile[i].p_tex) == Texture2DUtil::GTX_ERROR_OK)
        {
            RIO_LOG("\"%s\": loaded: %s\n", mName.c_str(), cAnimeFilename[i]);
            initializeSpan(&mAnimeTextureFile[i].data, anm, anm_filesize);
        }
    }

    return true;
}

std::span<u8> BgUnitFile::save() const
{
    if (!mTextureFile.p_tex)
        return std::span<u8>();

    SharcWriter<0x65> archive;

    const std::string chk_name = "BG_chk/d_bgchk_" + mName + ".bin";        // Bg Check (Collision)
    const std::string uhd_name = "BG_unt/"         + mName + "_hd.bin";     // Unit Head Data
    const std::string unt_name = "BG_unt/"         + mName + ".bin";        // Unit Data
    const std::string tex_name = "BG_tex/"         + mName + ".gtx";        // Texture Data
    const std::string nml_name = "BG_tex/"         + mName + "_nml.gtx";    // Normal Map Texture Data

    constexpr size_t chk_filesize = sizeof(u64) * BG_MAX_PER_UNIT_NUM;
    void* const chk = rio::MemUtil::alloc(chk_filesize, 4);

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    rio::MemUtil::copy(chk, mBgCheck, sizeof(u64) * BG_MAX_PER_UNIT_NUM);
#else
    {
        u64* const p_dst = static_cast<u64*>(chk);
        for (s32 i = 0; i < BG_MAX_PER_UNIT_NUM; i++)
            p_dst[i] = __builtin_bswap64(mBgCheck[i]);
    }
#endif

    archive.addFile(chk_name, { (u8*)chk, chk_filesize });

    const size_t uhd_filesize = sizeof(BgUnitObjHead) * mObj.size();
    void* const uhd = rio::MemUtil::alloc(uhd_filesize, 4);

    u32 unt_filesize = 0;
    {
        BgUnitObjHead* p_dst = static_cast<BgUnitObjHead*>(uhd);

        for (const BgUnitObj& src : mObj)
        {
            BgUnitObjHead& dst = *p_dst++;

            dst.data_offs   = CD_FILE_READ_16_BE(u16(unt_filesize));
            dst.width       = src.getWidth();
            dst.height      = src.getHeight();
            dst.random      = CD_FILE_READ_16_BE(src.getRandom());

            unt_filesize += src.calcRowsByteSize();
        }
    }
    RIO_ASSERT(unt_filesize <= 0xffff);
    void* const unt = rio::MemUtil::alloc(unt_filesize, 4);
    {
        u8* p_dst = static_cast<u8*>(unt);

        for (const BgUnitObj& src : mObj)
            p_dst += src.saveRows(p_dst);

        RIO_ASSERT(unt_filesize == (uintptr_t(p_dst) - uintptr_t(unt)));
    }

    archive.addFile(uhd_name, { (u8*)uhd, uhd_filesize });
    archive.addFile(unt_name, { (u8*)unt, unt_filesize });

    archive.addFile(tex_name, mTextureFile.data);
    archive.addFile(nml_name, mNormalTextureFile.data);

    for (s32 i = 0; i < ANIME_TYPE_MAX; i++)
        if (mAnimeTextureFile[i].p_tex)
            archive.addFile(cAnimeFilename[i], mAnimeTextureFile[i].data);

    const auto& ret = archive.save(true);

    rio::MemUtil::free(chk);
    rio::MemUtil::free(uhd);
    rio::MemUtil::free(unt);

    return ret;
}
