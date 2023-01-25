#pragma once

#include <misc/rio_Types.h>

#include <gsl/span>

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
    static gsl::span<u8> compress(const gsl::span<const u8>& data, CompressionLevel level = LEVEL_DEFAULT);

private:
    static inline gsl::span<const u8> compressionSearch_(
        const u8* src,
        const u8* src_start,
        const u8* src_end,
        size_t max_len,
        u32 range
    );
};
