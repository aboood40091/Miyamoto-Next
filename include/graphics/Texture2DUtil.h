#pragma once

#include <gpu/rio_Texture.h>

#include <span>

class Texture2DUtil
{
public:
    enum GTXError
    {
        GTX_ERROR_OK = 0,
        GTX_ERROR_SRC_TOO_SHORT,
        GTX_ERROR_SRC_INVALID,
        GTX_ERROR_SRC_EMPTY,
        GTX_ERROR_UNSUPPORTED_FORMAT
    };
public:
    static GTXError createFromGTX(std::span<const u8> file, rio::Texture2D** pp_texture);
    static GTXError createFromGTX(const u8* file_data, rio::Texture2D** pp_texture);
    static void destroy(rio::Texture2D** pp_texture);
};
