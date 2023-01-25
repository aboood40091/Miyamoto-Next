#pragma once

#include <misc/rio_Types.h>

inline u32 sharcCalcHash32(const char* str, u32 key)
{
    u32 ret = 0;
    for (s32 i = 0; str[i] != '\0'; i++)
        ret = ret * key + str[i];

    return ret;
}
