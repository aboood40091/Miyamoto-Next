#pragma once

#include <misc/rio_Types.h>

#include <span>

class SZSCompressor
{
public:
    enum CompressionLevel
    {
        LEVEL_NO_COMPRESSION = 0,
        LEVEL_DEFAULT = 1,
        LEVEL_MAX = 9,
    };

public:
    static std::span<u8> compress(std::span<const u8> data, CompressionLevel level = LEVEL_DEFAULT);
    static std::span<u8> compressFast(std::span<const u8> data);

private:
    static inline std::span<const u8> compressionSearch_(
        const u8* src,
        const u8* src_start,
        const u8* src_end,
        size_t max_len,
        u32 range
    );
};
