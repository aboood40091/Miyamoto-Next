#include <resource/SZSCompressor.h>

#include <misc/rio_MemUtil.h>

#include <fastyz.h>

std::span<u8> SZSCompressor::compressFastYZ(std::span<const u8> data)
{
    const u8* const p_src = data.data();
    const std::size_t src_size = data.size();

    u8* const p_dst = static_cast<u8*>(rio::MemUtil::alloc(FASTYZ_BOUND(src_size), 4));

    const std::size_t out_size = yaz0_compress(p_src, src_size, p_dst);

    return { p_dst, out_size };
}
