#pragma once

#include <misc/rio_Types.h>

enum ItemType : u8
{
    ITEM_TYPE_BG_UNIT_OBJ   = 0,
    ITEM_TYPE_MAP_ACTOR,
    ITEM_TYPE_NEXT_GOTO,
    ITEM_TYPE_LOCATION,
    ITEM_TYPE_AREA,
    ITEM_TYPE_MAX_NUM
};
