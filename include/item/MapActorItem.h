#pragma once

#include <course/CourseDataFile.h>
#include <item/ItemID.h>

#include <gfx/lyr/rio_Drawable.h>

#include <memory>

class MapActorItem
{
public:
    enum DataChangeFlag
    {
        DATA_CHANGE_FLAG_OFFSET         = 1 << 0,
        DATA_CHANGE_FLAG_EVENT_ID       = 1 << 1,
        DATA_CHANGE_FLAG_SETTINGS_0     = 1 << 2,
        DATA_CHANGE_FLAG_SETTINGS_1     = 1 << 3,
        DATA_CHANGE_FLAG_AREA           = 1 << 4,
        DATA_CHANGE_FLAG_LAYER          = 1 << 5,
        DATA_CHANGE_FLAG_MOVEMENT_ID    = 1 << 6,
        DATA_CHANGE_FLAG_LINK_ID        = 1 << 7,
        DATA_CHANGE_FLAG_INIT_STATE     = 1 << 8
    };

    static f32 getDefaultZPos(u8 layer)
    {
        return layer == LAYER_1 ? 2200.0f : -2500.0f; // Only layer 1 and 2
    }

public:
    MapActorItem(MapActorData& map_actor_data, u32 index);
    virtual ~MapActorItem() {}

    MapActorItem(const MapActorItem&) = delete;
    MapActorItem(MapActorItem&&) = delete;
    MapActorItem& operator=(const MapActorItem&) = delete;
    MapActorItem& operator=(MapActorItem&&) = delete;

    MapActorData& getMapActorData() { return mMapActorData; }
    const MapActorData& getMapActorData() const { return mMapActorData; }

    void setIndex(u32 index)
    {
        mItemID.setIndex(index);
        onIndexChange_();
    }

    virtual void setSelection(bool is_selected)
    {
        mIsSelected = is_selected;
        onSelectionChange_();
    }

    virtual void onDataChange(DataChangeFlag flag)
    {
    }

    virtual void onSceneUpdate()
    {
    }

    virtual void scheduleDraw()
    {
    }

    virtual void drawOpa(const rio::lyr::DrawInfo& draw_info);
    virtual void drawXlu(const rio::lyr::DrawInfo& draw_info);

protected:
    virtual bool drawBox_() const
    {
        return true;
    }

    virtual void onIndexChange_() { }
    virtual void onSelectionChange_() { }

protected:
    MapActorData&   mMapActorData;
    ItemID          mItemID;
    bool            mIsSelected;
};

#define MAP_ACTOR_ITEM_CREATE(CLASS)                                                            \
    public:                                                                                     \
        static std::unique_ptr<MapActorItem> create(MapActorData& map_actor_data, u32 index)    \
        {                                                                                       \
            return std::make_unique<CLASS>(map_actor_data, index);                              \
        }
