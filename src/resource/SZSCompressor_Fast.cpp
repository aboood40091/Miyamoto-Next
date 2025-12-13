#include <resource/SZSCompressor.h>

#include <misc/rio_MemUtil.h>

#include <algorithm>

namespace {

enum
{
    cSearchWindowSize = 0x1000,
    cMatchLenMax = 0x111,

    cPosTempBufferNum = 0x8000,
    cSearchPosBufferNum = cSearchWindowSize,

    cDataBufferSize = 0x2000,
    cPosTempBufferSize = cPosTempBufferNum * sizeof(s32),
    cSearchPosBufferSize = cSearchPosBufferNum * sizeof(s32),

    cWorkSize = cDataBufferSize + cPosTempBufferSize + cSearchPosBufferSize
};

struct Work
{
    u8  data_buffer[cDataBufferSize];
    s32 pos_temp_buffer[cPosTempBufferNum];
    s32 search_pos_buffer[cSearchPosBufferNum];
};
static_assert(sizeof(Work) == cWorkSize);

struct Match
{
    s32 len;
    s32 pos;
};

class PosTempBufferIndex
{
public:
    PosTempBufferIndex()
        : mValue(0)
    {
    }

    void pushBack(u32 value)
    {
        mValue = ((mValue << 5) ^ value) % cPosTempBufferNum;
    }

    u32 value() const
    {
        return mValue;
    }

private:
    u32 mValue;
};

static Work sWork;

static inline bool search(Match& match, s32 search_pos, const u32 data_pos, const s32 data_buffer_size)
{
    const u8* cmp2 = sWork.data_buffer + data_pos;

    s32 search_pos_min =
        data_pos > cSearchWindowSize
            ? s32(data_pos - cSearchWindowSize)
            : -1;

    s32 match_len = 2;
    match.len = match_len;

    if (data_pos - search_pos <= cSearchWindowSize)
    {
        for (u32 i = 0; i < cSearchWindowSize; i++)
        {
            const u8* cmp1 = sWork.data_buffer + search_pos;
            if (cmp1[0] == cmp2[0] && cmp1[1] == cmp2[1] && cmp1[match_len] == cmp2[match_len])
            {
                s32 len_local;

                for (len_local = 2; len_local < cMatchLenMax; len_local++)
                    if (cmp1[len_local] != cmp2[len_local])
                        break;

                if (len_local > match_len)
                {
                    match.len = len_local;
                    match.pos = cmp2 - cmp1;

                    match_len = data_buffer_size;
                    if (match.len <= match_len)
                        match_len = match.len;
                    else
                        match.len = match_len;

                    if (len_local >= cMatchLenMax)
                        break;
                }
            }

            search_pos = sWork.search_pos_buffer[search_pos % cSearchPosBufferNum];
            if (search_pos <= search_pos_min)
                break;
        }

        if (match_len >= 3)
            return true;
    }

    return false;
}

}

extern "C" int yaz0_compress(const void *input, int length, void *output);

std::span<u8> SZSCompressor::compressFast(std::span<const u8> data)
{
    const u8* const p_src = data.data();
    const u32 src_size = data.size();
    u8* const p_dst = static_cast<u8*>(rio::MemUtil::alloc(0x10 + src_size + (src_size + 8) / 8, 4));

    std::size_t out_size = yaz0_compress(p_src, src_size, p_dst);

    return { p_dst, out_size };
}
