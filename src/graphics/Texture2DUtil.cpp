#include <graphics/Texture2DUtil.h>

#include <misc/rio_MemUtil.h>

#include <cstring>

#if RIO_IS_CAFE
#include <gfd.h>
#include <gx2/mem.h>
#elif RIO_IS_DESKTOP
#include <ninTexUtils/gfd/gfdStruct.h>
#endif

Texture2DUtil::GTXError Texture2DUtil::createFromGTX(std::span<const u8> file, std::unique_ptr<rio::Texture2D>* pp_texture)
{
    if (file.data() == nullptr || file.size() < sizeof(GFDHeader))
        return GTX_ERROR_SRC_TOO_SHORT;

    return createFromGTX(file.data(), pp_texture);
}

Texture2DUtil::GTXError Texture2DUtil::createFromGTX(const u8* file_data, std::unique_ptr<rio::Texture2D>* pp_texture)
{
    RIO_ASSERT(pp_texture);
    std::unique_ptr<rio::Texture2D>& p_texture = *pp_texture;

    if (file_data == nullptr)
        return GTX_ERROR_SRC_TOO_SHORT;

    if (std::strncmp((char*)file_data, "Gfx2", 4) != 0)
        return GTX_ERROR_SRC_INVALID;

    rio::NativeTexture2D native_texture;

#if RIO_IS_CAFE
    u32 alignment = GFDGetTextureAlignmentSize(0, file_data);

    u32 imageSize = GFDGetTextureImageSize(0, file_data);
    void* image = imageSize ? rio::MemUtil::alloc(imageSize, alignment) : nullptr;

    u32 mipSize = GFDGetTextureMipImageSize(0, file_data);
    void* mipmaps = mipSize ? rio::MemUtil::alloc(mipSize, alignment) : nullptr;

    GFDGetTexture(&native_texture,
                  image,
                  mipmaps,
                  0,
                  file_data);

    RIO_ASSERT(native_texture.surface.imageSize == imageSize);
    if (imageSize)
    {
        RIO_ASSERT(image);
        RIO_ASSERT((uintptr_t)image % alignment == 0);

        GX2Invalidate(GX2_INVALIDATE_MODE_CPU_TEXTURE, image, imageSize);
    }

    RIO_ASSERT(native_texture.surface.mipmapSize == mipSize);
    if (mipSize)
    {
        RIO_ASSERT(mipmaps);
        RIO_ASSERT((uintptr_t)mipmaps % alignment == 0);

        GX2Invalidate(GX2_INVALIDATE_MODE_CPU_TEXTURE, mipmaps, mipSize);
    }

    native_texture.surface.image = image;
    native_texture.surface.mipmaps = mipmaps;

    GX2CalcSurfaceSizeAndAlignment(&native_texture.surface);
    GX2InitTextureRegs(&native_texture);
#elif RIO_IS_DESKTOP
    GFDFile gfd;
    gfd.load(file_data);

    if (gfd.mTextures.size() < 1)
        return GTX_ERROR_SRC_EMPTY;

    const GX2Texture& gx2Texture = gfd.mTextures[0];

    native_texture.surface.format = rio::TextureFormat(gx2Texture.surface.format);
    if (!rio::TextureFormatUtil::getNativeTextureFormat(native_texture.surface.nativeFormat, native_texture.surface.format))
        return GTX_ERROR_UNSUPPORTED_FORMAT;

    native_texture.compMap = gx2Texture.compSel;
    {
        native_texture._footer.magic = 0x5101382D;
        native_texture._footer.version = 0x01000000;
    }

    RIO_ASSERT(gx2Texture.surface.dim == GX2_SURFACE_DIM_2D);
    RIO_ASSERT(gx2Texture.surface.depth <= 1);

    GX2Surface linear_surface = gx2Texture.surface;
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
        GX2CopySurface(&gx2Texture.surface, i, 0, &linear_surface, i, 0);

    native_texture.surface.width = linear_surface.width;
    native_texture.surface.height = linear_surface.height;
    native_texture.surface.mipLevels = linear_surface.numMips;
    native_texture.surface.imageSize = linear_surface.imageSize;
    native_texture.surface.image = linear_surface.imagePtr;
    native_texture.surface.mipmapSize = linear_surface.mipSize;
    native_texture.surface.mipmaps = linear_surface.mipPtr;

    rio::MemUtil::copy(native_texture.surface.mipLevelOffset, linear_surface.mipOffset, 13 * sizeof(u32));
    native_texture.surface.mipLevelOffset[0] = 0;
#endif

    p_texture = std::make_unique<rio::Texture2D>(native_texture);
    return GTX_ERROR_OK;
}

void Texture2DUtil::destroy(std::unique_ptr<rio::Texture2D>* pp_texture)
{
    RIO_ASSERT(pp_texture);
    std::unique_ptr<rio::Texture2D>& p_texture = *pp_texture;

    if (p_texture)
    {
        const rio::NativeSurface2D& native_surface = p_texture->getNativeTexture().surface;
        rio::MemUtil::free(native_surface.image);
        if (native_surface.mipmaps)
            rio::MemUtil::free(native_surface.mipmaps);

        p_texture.reset();
    }
}
