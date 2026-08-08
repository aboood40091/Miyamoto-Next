#pragma once

#include <misc/rio_Types.h>

#include <string>

enum ItemType : u8
{
    ITEM_TYPE_BG_UNIT_OBJ   = 0,
    ITEM_TYPE_MAP_ACTOR,
    ITEM_TYPE_NEXT_GOTO,
    ITEM_TYPE_LOCATION,
    ITEM_TYPE_AREA,
    ITEM_TYPE_MAX_NUM
};

#define ITEM_NAME_BG_UNIT_OBJ   "Bg Unit Object"
#define ITEM_NAME_MAP_ACTOR     "Actor"
#define ITEM_NAME_NEXT_GOTO     "NextGoto"
#define ITEM_NAME_LOCATION      "Location"
#define ITEM_NAME_AREA          "Area"
#define ITEM_NAME_GENERIC       "Item"

inline const char* getItemTypeName(ItemType item_type, bool plural = false)
{
    switch (item_type)
    {
    case ITEM_TYPE_BG_UNIT_OBJ: return plural ? ITEM_NAME_BG_UNIT_OBJ   "s" : ITEM_NAME_BG_UNIT_OBJ;
    case ITEM_TYPE_MAP_ACTOR:   return plural ? ITEM_NAME_MAP_ACTOR     "s" : ITEM_NAME_MAP_ACTOR;
    case ITEM_TYPE_NEXT_GOTO:   return plural ? ITEM_NAME_NEXT_GOTO     "s" : ITEM_NAME_NEXT_GOTO;
    case ITEM_TYPE_LOCATION:    return plural ? ITEM_NAME_LOCATION      "s" : ITEM_NAME_LOCATION;
    case ITEM_TYPE_AREA:        return plural ? ITEM_NAME_AREA          "s" : ITEM_NAME_AREA;
    default:                    return plural ? ITEM_NAME_GENERIC       "s" : ITEM_NAME_GENERIC;
    }
}

inline std::string getItemCountText(u32 count, ItemType item_type)
{
    return std::to_string(count) + ' ' + getItemTypeName(item_type, count != 1);
}

inline std::string getItemCountText(u32 count)
{
    return std::to_string(count) + (count == 1 ? " " ITEM_NAME_GENERIC : " " ITEM_NAME_GENERIC "s");
}
