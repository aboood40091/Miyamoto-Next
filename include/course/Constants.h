#pragma once

#include <misc/rio_Types.h>

enum
{
    CD_FILE_MAX_NUM         = 4,
    CD_FILE_AREA_MAX_NUM    = 64,
    CD_FILE_TS_NAME_MAX_LEN = 32,
    CD_FILE_ENV_MAX_NUM     = 4,
    CD_FILE_DV_NAME_MAX_LEN = 16,

    CD_FILE_LAYER_MAX_NUM   = 3,

    CD_FILE_BLOCK_ENVIRONMENT       =   1 - 1,
    CD_FILE_BLOCK_OPTIONS           =   2 - 1,
    CD_FILE_BLOCK_SCROLL_DATA       =   3 - 1,
                                    //  4
    CD_FILE_BLOCK_DISTANT_VIEW_DATA =   5 - 1,
                                    //  6
    CD_FILE_BLOCK_NEXT_GOTO         =   7 - 1,
    CD_FILE_BLOCK_MAP_ACTOR_DATA    =   8 - 1,
    CD_FILE_BLOCK_MAP_ACTOR_RES     =   9 - 1,
    CD_FILE_BLOCK_AREA_DATA         =  10 - 1,
    CD_FILE_BLOCK_LOCATION          =  11 - 1,
                                    // 12
                                    // 13
    CD_FILE_BLOCK_RAIL_INFO         =  14 - 1,
    CD_FILE_BLOCK_RAIL_POINT        =  15 - 1,
    CD_FILE_BLOCK_NUM,
};

enum
{
    BG_MAX_PER_UNIT_NUM = 256,
    BG_MAX_UNIT_NUM = BG_MAX_PER_UNIT_NUM * CD_FILE_ENV_MAX_NUM,

    BG_MAX_UNIT_X   = 1024,
    BG_MAX_UNIT_Y   = 512,

    BG_MAX_X        = BG_MAX_UNIT_X * 16,
    BG_MAX_Y        = BG_MAX_UNIT_Y * 16,
};

enum
{
    LAYER_1         = 0,
    LAYER_2,
    LAYER_0,

    // This is a special value
    LAYER_0_ACTOR,
};
static_assert(s32(LAYER_0_ACTOR) == s32(CD_FILE_LAYER_MAX_NUM));

enum AnimeType
{
    ANIME_TYPE_HATENA = 0,
    ANIME_TYPE_BLOCK,
    ANIME_TYPE_TUKA_COIN,
    ANIME_TYPE_BELT_CONVEYOR,
    ANIME_TYPE_HATENA_L,
    ANIME_TYPE_BLOCK_L,
    ANIME_TYPE_MAX
};
static_assert(ANIME_TYPE_MAX == 6);

static inline s16 CD_FILE_READ_16_BE(s16 val)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    return __builtin_bswap16(val);
#else
    return val;
#endif
}

static inline u16 CD_FILE_READ_16_BE(u16 val)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    return __builtin_bswap16(val);
#else
    return val;
#endif
}

static inline s32 CD_FILE_READ_32_BE(s32 val)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    return __builtin_bswap32(val);
#else
    return val;
#endif
}

static inline u32 CD_FILE_READ_32_BE(u32 val)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    return __builtin_bswap32(val);
#else
    return val;
#endif
}

static inline void CD_FILE_WRITE_16_BE(s16& dst, s16 src)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    dst = __builtin_bswap16(src);
#else
    dst = src;
#endif
}

static inline void CD_FILE_WRITE_16_BE(u16& dst, u16 src)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    dst = __builtin_bswap16(src);
#else
    dst = src;
#endif
}

static inline void CD_FILE_WRITE_32_BE(s32& dst, s32 src)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    dst = __builtin_bswap32(src);
#else
    dst = src;
#endif
}

static inline void CD_FILE_WRITE_32_BE(u32& dst, u32 src)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    dst = __builtin_bswap32(src);
#else
    dst = src;
#endif
}
