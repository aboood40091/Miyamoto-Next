#include <resource/SZSCompressor.h>

#include <misc/rio_MemUtil.h>

extern "C" int yaz0_compress(const void *input, int length, void *output);

std::span<u8> SZSCompressor::compressFast(std::span<const u8> data)
{
    const u8* const p_src = data.data();
    const u32 src_size = data.size();
    u8* const p_dst = static_cast<u8*>(rio::MemUtil::alloc(0x10 + src_size + (src_size + 8) / 8, 4));

    std::size_t out_size = yaz0_compress(p_src, src_size, p_dst);

    return { p_dst, out_size };
}
