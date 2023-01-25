#include <resource/SZSCompressor.h>

#include <misc/rio_MemUtil.h>

#include <cstring>

gsl::span<const u8> SZSCompressor::compressionSearch_(
    const u8* src,
    const u8* src_start,
    const u8* src_end,
    size_t max_len,
    u32 range
)
{
    if (src + 2 >= src_end)
        return gsl::span<u8>();

    const u8* found = nullptr;
    size_t found_len = 0;

    const u8* const cmp_start = std::max(src - range,     src_start);
    const u8* const cmp_end   = std::min(src + max_len,   src_end);

    const u8* search = cmp_start;

    u8 c = *src;
    while (search < src)
    {
        search = static_cast<u8*>(std::memchr(search, c, uintptr_t(src) - uintptr_t(search)));
        if (!search)
            break;

        const u8* cmp1 = search + 1;
        const u8* cmp2 = src + 1;

        while (cmp2 < cmp_end && *cmp1 == *cmp2)
        {
            cmp1++;
            cmp2++;
        }

        const size_t len = uintptr_t(cmp2) - uintptr_t(src);
        if (found_len < len)
        {
            found_len = std::min(len, max_len);
            found = search;
            if (found_len == max_len)
                break;
        }

        search++;
    }

    return { found, found_len};
}

gsl::span<u8> SZSCompressor::compress(const gsl::span<const u8>& data, CompressionLevel level)
{
    RIO_ASSERT(LEVEL_NO_COMPRESSION <= level && level <= LEVEL_MAX);

    const u32 range = (level == LEVEL_NO_COMPRESSION) ? 0
                                                      : (0x10e0 / LEVEL_MAX) * u32(level) - 0x0e0;

    const size_t src_size = data.size();

    const u8* const src_start = data.data();
    const u8* const src_end = src_start + src_size;
    const u8* src = src_start;

    u8* const dst_start = static_cast<u8*>(rio::MemUtil::alloc(0x10 + src_size + (src_size + 8) / 8, 4));
    u8* dst = dst_start;

    *(u32*)dst =
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        __builtin_bswap32(0x59617A30);
#else
        0x59617A30;
#endif

    *(u32*)(dst + 4) =
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        __builtin_bswap32(src_size);
#else
        src_size;
#endif

    *(u64*)(dst + 8) = 0;

    dst += 0x10;

    constexpr size_t max_len = 0x111;

    while (src < src_end)
    {
        u8* const code_byte = dst++;
        *code_byte = 0;

        for (s32 i = 0; i < 8; i++)
        {
            if (src >= src_end)
                break;

            const gsl::span<const u8>& found = (range > 0) ? compressionSearch_(src, src_start, src_end, max_len, range)
                                                           : gsl::span<u8>();
            if (found.size() > 2)
            {
                u16 delta = uintptr_t(src) - uintptr_t(found.data()) - 1;
                if (found.size() >= 0x12)
                {
                    *dst++ = delta >> 8;
                    *dst++ = delta & 0xFF;
                    *dst++ = found.size() - 0x12;
                }
                else
                {
                    *dst++ = delta >> 8 | (found.size() - 2) << 4;
                    *dst++ = delta & 0xFF;
                }
                src += found.size();
            }
            else
            {
                *code_byte |= 1 << (7 - i);
                *dst++ = *src++;
            }
        }
    }

    return { dst_start, uintptr_t(dst) - uintptr_t(dst_start) };
}
