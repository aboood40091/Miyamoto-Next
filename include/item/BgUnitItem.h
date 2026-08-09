#pragma once

#include <course/CourseDataFile.h>
#include <item/ItemBase.h>

class BgUnitItem : public ItemBase
{
public:
    static bool checkType(u32 item_id)
    {
        return ItemID::getType(item_id) == ITEM_TYPE_BG_UNIT_OBJ;
    }

    static u32 getLayerFromItemIndex(u32 index)
    {
        return index >> 22;
    }

    static u32 getLayer(u32 item_id)
    {
        RIO_ASSERT(checkType(item_id));
        return getLayerFromItemIndex(ItemID::getIndex(item_id));
    }

    static u32 getIndexFromItemIndex(u32 index)
    {
        return index & 0x003FFFFF;
    }

    static u32 getIndex(u32 item_id)
    {
        RIO_ASSERT(checkType(item_id));
        return getIndexFromItemIndex(ItemID::getIndex(item_id));
    }

    static u32 makeItemIndex(u8 layer, u32 obj_index)
    {
        RIO_ASSERT(layer < CD_FILE_LAYER_MAX_NUM);
        RIO_ASSERT(obj_index <= 0x003FFFFF);
        return layer << 22 | obj_index;
    }

    static ItemID makeItemID(u8 layer, u32 obj_index)
    {
        return ItemID(ITEM_TYPE_BG_UNIT_OBJ, makeItemIndex(layer, obj_index));
    }

public:
    BgUnitItem(const BgCourseData& data, u32 index);

    void move(s16 dx, s16 dy, bool commit) override;
    void drawSelectionUI() override;

private:
    void onSelectionChange_() override;

private:
    BgCourseData mSelectionData;
};
