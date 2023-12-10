#pragma once

#include <course/CourseDataFile.h>
#include <item/ItemBase.h>

#include <gfx/lyr/rio_Drawable.h>

#include <memory>

class MapActorItem : public ItemBase
{
public:
    enum DataChangeFlag
    {
        DATA_CHANGE_FLAG_NONE           = 0,

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

    friend DataChangeFlag operator|(const DataChangeFlag& lhs, const DataChangeFlag& rhs)
    {
        return (DataChangeFlag)((u32)lhs | (u32)rhs);
    }

    friend DataChangeFlag& operator|=(DataChangeFlag& lhs, const DataChangeFlag& rhs)
    {
        lhs = lhs | rhs;
        return lhs;
    }

    static f32 getDefaultZPos(u8 layer)
    {
        return layer == LAYER_1 ? 2200.0f : -2500.0f; // Only layer 1 and 2
    }

public:
    MapActorItem(const MapActorData& map_actor_data, u32 index);
    virtual ~MapActorItem() {}

    MapActorItem(const MapActorItem&) = delete;
    MapActorItem(MapActorItem&&) = delete;
    MapActorItem& operator=(const MapActorItem&) = delete;
    MapActorItem& operator=(MapActorItem&&) = delete;

    void move(s16 dx, s16 dy, bool commit) override;
    void drawSelectionUI() override;

    virtual void onDataChange(const MapActorData& map_actor_data, DataChangeFlag flag)
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

    void onSelectionChange_() override;

protected:
    MapActorData    mSelectionData;
};

#define MAP_ACTOR_ITEM_CREATE(CLASS)                                                                \
    public:                                                                                         \
        static std::unique_ptr<MapActorItem> create(const MapActorData& map_actor_data, u32 index)  \
        {                                                                                           \
            return std::make_unique<CLASS>(map_actor_data, index);                                  \
        }
