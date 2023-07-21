#include <course/BgUnitFile.h>
#include <resource/SharcArchiveRes.h>
#include <resource/SharcWriter.h>

#include <misc/rio_MemUtil.h>

#include <cstring>

#if RIO_IS_CAFE

#include <gfd.h>
#include <gx2/mem.h>

#elif RIO_IS_WIN

#include <ninTexUtils/gfd/gfdStruct.h>

static inline bool RIOTexFormatToNativeTextureFormat(rio::NativeSurface2D& surface)
{
    switch (surface.format)
    {
    case rio::TEXTURE_FORMAT_R8_UNORM:
        surface.nativeFormat.internalformat = GL_R8;
        surface.nativeFormat.format = GL_RED;
        surface.nativeFormat.type = GL_UNSIGNED_BYTE;
        return true;

    case rio::TEXTURE_FORMAT_R8_UINT:
        surface.nativeFormat.internalformat = GL_R8UI;
        surface.nativeFormat.format = GL_RED_INTEGER;
        surface.nativeFormat.type = GL_UNSIGNED_BYTE;
        return true;

    case rio::TEXTURE_FORMAT_R8_SNORM:
        surface.nativeFormat.internalformat = GL_R8_SNORM;
        surface.nativeFormat.format = GL_RED;
        surface.nativeFormat.type = GL_BYTE;
        return true;

    case rio::TEXTURE_FORMAT_R8_SINT:
        surface.nativeFormat.internalformat = GL_R8I;
        surface.nativeFormat.format = GL_RED_INTEGER;
        surface.nativeFormat.type = GL_BYTE;
        return true;

    case rio::TEXTURE_FORMAT_R8_G8_UNORM:
        surface.nativeFormat.internalformat = GL_RG8;
        surface.nativeFormat.format = GL_RG;
        surface.nativeFormat.type = GL_UNSIGNED_BYTE;
        return true;

    case rio::TEXTURE_FORMAT_R8_G8_UINT:
        surface.nativeFormat.internalformat = GL_RG8UI;
        surface.nativeFormat.format = GL_RG_INTEGER;
        surface.nativeFormat.type = GL_UNSIGNED_BYTE;
        return true;

    case rio::TEXTURE_FORMAT_R8_G8_SNORM:
        surface.nativeFormat.internalformat = GL_RG8_SNORM;
        surface.nativeFormat.format = GL_RG;
        surface.nativeFormat.type = GL_BYTE;
        return true;

    case rio::TEXTURE_FORMAT_R8_G8_SINT:
        surface.nativeFormat.internalformat = GL_RG8I;
        surface.nativeFormat.format = GL_RG_INTEGER;
        surface.nativeFormat.type = GL_BYTE;
        return true;

    case rio::TEXTURE_FORMAT_R5_G6_B5_UNORM:
        surface.nativeFormat.internalformat = GL_RGB565;
        surface.nativeFormat.format = GL_RGB;
        surface.nativeFormat.type = GL_UNSIGNED_SHORT_5_6_5;
        return true;

    case rio::TEXTURE_FORMAT_R5_G5_B5_A1_UNORM:
        surface.nativeFormat.internalformat = GL_RGB5_A1;
        surface.nativeFormat.format = GL_RGBA;
        surface.nativeFormat.type = GL_UNSIGNED_SHORT_5_5_5_1;
        return true;

    case rio::TEXTURE_FORMAT_R4_G4_B4_A4_UNORM:
        surface.nativeFormat.internalformat = GL_RGBA4;
        surface.nativeFormat.format = GL_RGBA;
        surface.nativeFormat.type = GL_UNSIGNED_SHORT_4_4_4_4;
        return true;

    case rio::TEXTURE_FORMAT_R8_G8_B8_A8_UNORM:
        surface.nativeFormat.internalformat = GL_RGBA8;
        surface.nativeFormat.format = GL_RGBA;
        surface.nativeFormat.type = GL_UNSIGNED_BYTE;
        return true;

    case rio::TEXTURE_FORMAT_R8_G8_B8_A8_UINT:
        surface.nativeFormat.internalformat = GL_RGBA8UI;
        surface.nativeFormat.format = GL_RGBA_INTEGER;
        surface.nativeFormat.type = GL_UNSIGNED_BYTE;
        return true;

    case rio::TEXTURE_FORMAT_R8_G8_B8_A8_SNORM:
        surface.nativeFormat.internalformat = GL_RGBA8_SNORM;
        surface.nativeFormat.format = GL_RGBA;
        surface.nativeFormat.type = GL_BYTE;
        return true;

    case rio::TEXTURE_FORMAT_R8_G8_B8_A8_SINT:
        surface.nativeFormat.internalformat = GL_RGBA8I;
        surface.nativeFormat.format = GL_RGBA_INTEGER;
        surface.nativeFormat.type = GL_BYTE;
        return true;

    case rio::TEXTURE_FORMAT_R8_G8_B8_A8_SRGB:
        surface.nativeFormat.internalformat = GL_SRGB8_ALPHA8;
        surface.nativeFormat.format = GL_RGBA;
        surface.nativeFormat.type = GL_UNSIGNED_BYTE;
        return true;

    case rio::TEXTURE_FORMAT_R10_G10_B10_A2_UNORM:
        surface.nativeFormat.internalformat = GL_RGB10_A2;
        surface.nativeFormat.format = GL_RGBA;
        surface.nativeFormat.type = GL_UNSIGNED_INT_2_10_10_10_REV;
        return true;

    case rio::TEXTURE_FORMAT_R10_G10_B10_A2_UINT:
        surface.nativeFormat.internalformat = GL_RGB10_A2UI;
        surface.nativeFormat.format = GL_RGBA_INTEGER;
        surface.nativeFormat.type = GL_UNSIGNED_INT_2_10_10_10_REV;
        return true;

    case rio::TEXTURE_FORMAT_BC1_UNORM:
        surface.nativeFormat.internalformat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        surface.nativeFormat.format = 0;
        surface.nativeFormat.type = 0;
        return true;

    case rio::TEXTURE_FORMAT_BC1_SRGB:
        surface.nativeFormat.internalformat = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT;
        surface.nativeFormat.format = 0;
        surface.nativeFormat.type = 0;
        return true;

    case rio::TEXTURE_FORMAT_BC2_UNORM:
        surface.nativeFormat.internalformat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        surface.nativeFormat.format = 0;
        surface.nativeFormat.type = 0;
        return true;

    case rio::TEXTURE_FORMAT_BC2_SRGB:
        surface.nativeFormat.internalformat = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT;
        surface.nativeFormat.format = 0;
        surface.nativeFormat.type = 0;
        return true;

    case rio::TEXTURE_FORMAT_BC3_UNORM:
        surface.nativeFormat.internalformat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        surface.nativeFormat.format = 0;
        surface.nativeFormat.type = 0;
        return true;

    case rio::TEXTURE_FORMAT_BC3_SRGB:
        surface.nativeFormat.internalformat = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT;
        surface.nativeFormat.format = 0;
        surface.nativeFormat.type = 0;
        return true;

    case rio::TEXTURE_FORMAT_BC4_UNORM:
        surface.nativeFormat.internalformat = GL_COMPRESSED_RED_RGTC1;
        surface.nativeFormat.format = 0;
        surface.nativeFormat.type = 0;
        return true;

    case rio::TEXTURE_FORMAT_BC4_SNORM:
        surface.nativeFormat.internalformat = GL_COMPRESSED_SIGNED_RED_RGTC1;
        surface.nativeFormat.format = 0;
        surface.nativeFormat.type = 0;
        return true;

    case rio::TEXTURE_FORMAT_BC5_UNORM:
        surface.nativeFormat.internalformat = GL_COMPRESSED_RG_RGTC2;
        surface.nativeFormat.format = 0;
        surface.nativeFormat.type = 0;
        return true;

    case rio::TEXTURE_FORMAT_BC5_SNORM:
        surface.nativeFormat.internalformat = GL_COMPRESSED_SIGNED_RG_RGTC2;
        surface.nativeFormat.format = 0;
        surface.nativeFormat.type = 0;
        return true;

    default:
        return false;
    }
}

#endif

BgUnitFile::BgUnitFile(const std::string& name)
    : mName(name)
    , mData()
    , mpTexture(nullptr)
    , mpNormalTexture(nullptr)
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

    mBgUnit.clear();

    if (mpTexture)
    {
        const rio::NativeSurface2D& tex_surf = mpTexture->getNativeTexture().surface;
        rio::MemUtil::free(tex_surf.image);
        if (tex_surf.mipmaps)
            rio::MemUtil::free(tex_surf.mipmaps);

        delete mpTexture;
        mpTexture = nullptr;
    }

    if (mpNormalTexture)
    {
        const rio::NativeSurface2D& nml_surf = mpNormalTexture->getNativeTexture().surface;
        rio::MemUtil::free(nml_surf.image);
        if (nml_surf.mipmaps)
            rio::MemUtil::free(nml_surf.mipmaps);

        delete mpNormalTexture;
        mpNormalTexture = nullptr;
    }

    if (mData.data())
    {
        rio::MemUtil::free(mData.data());
        mData = std::span<u8>();
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

    u8* file_new = static_cast<u8*>(rio::MemUtil::alloc(filesize, 4));
    RIO_ASSERT(file_new);
    rio::MemUtil::copy(file_new, file, filesize);

    mData = std::span(file_new, filesize);

    SharcArchiveRes archive;
    if (!archive.prepareArchive(file))
    {
        RIO_LOG("\"%s\" is not a Sharc file.\n", mName.c_str());
        unload();
        return false;
    }

    const std::string chk_name = "BG_chk/d_bgchk_" + mName + ".bin";        // Bg Check (Collision)

    u32 chk_filesize = 0;
    void* const chk = archive.getFile(chk_name.c_str(), &chk_filesize);

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

    void* uhd = archive.getFile(uhd_name.c_str(), &uhd_filesize);
    void* unt = archive.getFile(unt_name.c_str(), &unt_filesize);

    if (!(uhd && unt))
    {
        RIO_LOG("\"%s\" missing unit data.\n", mName.c_str());
        unload();
        return false;
    }

    {
        u32 size = uhd_filesize;
        RIO_ASSERT(size % sizeof(BgUnitHead) == 0);
        u32 count = size / sizeof(BgUnitHead);

        mBgUnit.resize(count);

        const BgUnitHead* p_src = static_cast<const BgUnitHead*>(uhd);

        for (u32 i = 0; i < count; i++)
        {
            const BgUnitHead&   src = p_src[i];
            BgUnitHead          dst;

            dst.data[0] = CD_FILE_READ_16_BE(src.data[0]);
            dst.data[1] =                    src.data[1];   // Yes, this is a u16 and endianness is not reversed.
            dst.data[2] = CD_FILE_READ_16_BE(src.data[2]);

            mBgUnit[i].load(dst.width, dst.height, dst.random, dst.data_offs, unt, unt_filesize);
        }
    }

    const std::string tex_name = "BG_tex/"         + mName + ".gtx";        // Texture Data
    const std::string nml_name = "BG_tex/"         + mName + "_nml.gtx";    // Normal Map Texture Data

    u32 tex_filesize = 0;
    u32 nml_filesize = 0;

    void* tex = archive.getFile(tex_name.c_str(), &tex_filesize);
    void* nml = archive.getFile(nml_name.c_str(), &nml_filesize);

    if (!(tex_filesize >= sizeof(GFDHeader) && nml_filesize >= sizeof(GFDHeader)))
    {
        RIO_LOG("\"%s\" missing textures.\n", mName.c_str());
        unload();
        return false;
    }

    if (std::strncmp((char*)tex, "Gfx2", 4) != 0 ||
        std::strncmp((char*)nml, "Gfx2", 4) != 0)
    {
        RIO_LOG("\"%s\" invalid GFD textures.\n", mName.c_str());
        unload();
        return false;
    }

    if (mName == "Pa0_jyotyu")
    {
        mpTexture       = new rio::Texture2D("Pa0_jyotyu");
        mpNormalTexture = nullptr;
    }
    else if (mName == "Pa0_jyotyu_chika")
    {
        mpTexture       = new rio::Texture2D("Pa0_jyotyu_chika");
        mpNormalTexture = nullptr;
    }
    else if (mName == "Pa0_jyotyu_yougan")
    {
        mpTexture       = new rio::Texture2D("Pa0_jyotyu_yougan");
        mpNormalTexture = nullptr;
    }
    else if (mName == "Pa0_jyotyu_yougan2")
    {
        mpTexture       = new rio::Texture2D("Pa0_jyotyu_yougan2");
        mpNormalTexture = nullptr;
    }
    else
    {
        rio::NativeTexture2D tex_native;
        rio::NativeTexture2D nml_native;

#if RIO_IS_CAFE
        // Texture
        {
            u32 alignment = GFDGetTextureAlignmentSize(0, tex);

            u32 imageSize = GFDGetTextureImageSize(0, tex);
            void* image = imageSize ? rio::MemUtil::alloc(imageSize, alignment) : nullptr;

            u32 mipSize = GFDGetTextureMipImageSize(0, tex);
            void* mipmaps = mipSize ? rio::MemUtil::alloc(mipSize, alignment) : nullptr;

            GFDGetTexture(&tex_native,
                          image,
                          mipmaps,
                          0,
                          tex);

            RIO_ASSERT(tex_native.surface.imageSize == imageSize);
            if (imageSize)
            {
                RIO_ASSERT(image);
                RIO_ASSERT((uintptr_t)image % alignment == 0);

                GX2Invalidate(GX2_INVALIDATE_MODE_CPU_TEXTURE, image, imageSize);
            }

            RIO_ASSERT(tex_native.surface.mipmapSize == mipSize);
            if (mipSize)
            {
                RIO_ASSERT(mipmaps);
                RIO_ASSERT((uintptr_t)mipmaps % alignment == 0);

                GX2Invalidate(GX2_INVALIDATE_MODE_CPU_TEXTURE, mipmaps, mipSize);
            }

            tex_native.surface.image = image;
            tex_native.surface.mipmaps = mipmaps;

            GX2CalcSurfaceSizeAndAlignment(&tex_native.surface);
            GX2InitTextureRegs(&tex_native);
        }
        // Normal texture
        {
            u32 alignment = GFDGetTextureAlignmentSize(0, nml);

            u32 imageSize = GFDGetTextureImageSize(0, nml);
            void* image = imageSize ? rio::MemUtil::alloc(imageSize, alignment) : nullptr;

            u32 mipSize = GFDGetTextureMipImageSize(0, nml);
            void* mipmaps = mipSize ? rio::MemUtil::alloc(mipSize, alignment) : nullptr;

            GFDGetTexture(&nml_native,
                          image,
                          mipmaps,
                          0,
                          nml);

            RIO_ASSERT(nml_native.surface.imageSize == imageSize);
            if (imageSize)
            {
                RIO_ASSERT(image);
                RIO_ASSERT((uintptr_t)image % alignment == 0);

                GX2Invalidate(GX2_INVALIDATE_MODE_CPU_TEXTURE, image, imageSize);
            }

            RIO_ASSERT(nml_native.surface.mipmapSize == mipSize);
            if (mipSize)
            {
                RIO_ASSERT(mipmaps);
                RIO_ASSERT((uintptr_t)mipmaps % alignment == 0);

                GX2Invalidate(GX2_INVALIDATE_MODE_CPU_TEXTURE, mipmaps, mipSize);
            }

            nml_native.surface.image = image;
            nml_native.surface.mipmaps = mipmaps;

            GX2CalcSurfaceSizeAndAlignment(&nml_native.surface);
            GX2InitTextureRegs(&nml_native);
        }
#elif RIO_IS_WIN
        GFDFile tex_gfd;
        tex_gfd.load(tex);

        if (tex_gfd.mTextures.size() < 1)
        {
            RIO_LOG("\"%s\" missing main texture.\n", mName.c_str());
            unload();
            return false;
        }

        GFDFile nml_gfd;
        nml_gfd.load(nml);

        if (nml_gfd.mTextures.size() < 1)
        {
            RIO_LOG("\"%s\" missing normal texture.\n", mName.c_str());
            unload();
            return false;
        }

        const GX2Texture& tex_gx2 = tex_gfd.mTextures[0];
        const GX2Texture& nml_gx2 = nml_gfd.mTextures[0];

        tex_native.surface.format = rio::TextureFormat(tex_gx2.surface.format);
        if (!RIOTexFormatToNativeTextureFormat(tex_native.surface))
        {
            RIO_LOG("\"%s\" unsupported texture format.\n", mName.c_str());
            unload();
            return false;
        }
        tex_native.compMap = tex_gx2.compSel;

        nml_native.surface.format = rio::TextureFormat(nml_gx2.surface.format);
        if (!RIOTexFormatToNativeTextureFormat(nml_native.surface))
        {
            RIO_LOG("\"%s\" unsupported normal texture format.\n", mName.c_str());
            unload();
            return false;
        }
        nml_native.compMap = nml_gx2.compSel;

        // Texture
        {
            RIO_ASSERT(tex_gx2.surface.dim == GX2_SURFACE_DIM_2D);
            RIO_ASSERT(tex_gx2.surface.depth <= 1);

            GX2Surface linear_surface = tex_gx2.surface;
            linear_surface.depth = 1;
            linear_surface.numMips = std::max(linear_surface.numMips, 1u);
            linear_surface.use = GX2_SURFACE_USE_TEXTURE;
            linear_surface.tileMode = GX2_TILE_MODE_LINEAR_SPECIAL;
            linear_surface.swizzle = 0;
            GX2CalcSurfaceSizeAndAlignment(&linear_surface);

            linear_surface.imagePtr = rio::MemUtil::alloc(linear_surface.imageSize, linear_surface.alignment);
            if (linear_surface.mipSize)
                linear_surface.mipPtr = rio::MemUtil::alloc(linear_surface.mipSize, linear_surface.alignment);

            for (u32 i = 0; i < linear_surface.numMips; i++)
                GX2CopySurface(&tex_gx2.surface, i, 0, &linear_surface, i, 0);

            tex_native.surface.width = linear_surface.width;
            tex_native.surface.height = linear_surface.height;
            tex_native.surface.mipLevels = linear_surface.numMips;
            tex_native.surface.imageSize = linear_surface.imageSize;
            tex_native.surface.image = linear_surface.imagePtr;
            tex_native.surface.mipmapSize = linear_surface.mipSize;
            tex_native.surface.mipmaps = linear_surface.mipPtr;

            rio::MemUtil::copy(tex_native.surface.mipLevelOffset, linear_surface.mipOffset, 13 * sizeof(u32));
            tex_native.surface.mipLevelOffset[0] = 0;
        }
        // Normal texture
        {
            RIO_ASSERT(nml_gx2.surface.dim == GX2_SURFACE_DIM_2D);
            RIO_ASSERT(nml_gx2.surface.depth <= 1);

            GX2Surface linear_surface = nml_gx2.surface;
            linear_surface.depth = 1;
            linear_surface.numMips = std::max(linear_surface.numMips, 1u);
            linear_surface.use = GX2_SURFACE_USE_TEXTURE;
            linear_surface.tileMode = GX2_TILE_MODE_LINEAR_SPECIAL;
            linear_surface.swizzle = 0;
            GX2CalcSurfaceSizeAndAlignment(&linear_surface);

            linear_surface.imagePtr = rio::MemUtil::alloc(linear_surface.imageSize, linear_surface.alignment);
            if (linear_surface.mipSize)
                linear_surface.mipPtr = rio::MemUtil::alloc(linear_surface.mipSize, linear_surface.alignment);

            for (u32 i = 0; i < linear_surface.numMips; i++)
                GX2CopySurface(&nml_gx2.surface, i, 0, &linear_surface, i, 0);

            nml_native.surface.width = linear_surface.width;
            nml_native.surface.height = linear_surface.height;
            nml_native.surface.mipLevels = linear_surface.numMips;
            nml_native.surface.imageSize = linear_surface.imageSize;
            nml_native.surface.image = linear_surface.imagePtr;
            nml_native.surface.mipmapSize = linear_surface.mipSize;
            nml_native.surface.mipmaps = linear_surface.mipPtr;

            rio::MemUtil::copy(nml_native.surface.mipLevelOffset, linear_surface.mipOffset, 13 * sizeof(u32));
            nml_native.surface.mipLevelOffset[0] = 0;
        }
#endif

        mpTexture       = new rio::Texture2D(tex_native);
        mpNormalTexture = new rio::Texture2D(nml_native);
    }

    return true;
}

bool BgUnitFile::save()
{
    if (!mpTexture)
        return false;

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

    const size_t uhd_filesize = sizeof(BgUnitHead) * mBgUnit.size();
    void* const uhd = rio::MemUtil::alloc(uhd_filesize, 4);

    u32 unt_filesize = 0;
    {
        BgUnitHead* p_dst = static_cast<BgUnitHead*>(uhd);

        for (const BgUnit& src : mBgUnit)
        {
            BgUnitHead& dst = *p_dst++;

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

        for (const BgUnit& src : mBgUnit)
            p_dst += src.saveRows(p_dst);

        RIO_ASSERT(unt_filesize == (uintptr_t(p_dst) - uintptr_t(unt)));
    }

    archive.addFile(uhd_name, { (u8*)uhd, uhd_filesize });
    archive.addFile(unt_name, { (u8*)unt, unt_filesize });

    // TODO: Texture

    if (mData.data())
        rio::MemUtil::free(mData.data());

    mData = archive.save(true);

    return true;
}
