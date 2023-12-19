#include <CourseView.h>
#include <action/ActionItemPushBack.h>
#include <course/Bg.h>
#include <course/BgRenderer.h>

ActionItemPushBack::ActionItemPushBack(const void* context)
    : IAction(context)
    , mItems(static_cast<const Context*>(context)->items)
    , mTransform(static_cast<const Context*>(context)->transform)
    , mCenterUnitX(static_cast<const Context*>(context)->center_unit_x)
    , mCenterUnitY(static_cast<const Context*>(context)->center_unit_y)
{
}

bool ActionItemPushBack::apply() const
{
    bool layers_changed[CD_FILE_LAYER_MAX_NUM] = {
        false, false, false
    };

    if (mTransform)
    {
        const rio::BaseVec2f& center_pos = CourseView::instance()->getCenterWorldPos();
        s32 center_unit_x =  center_pos.x / 16;
        s32 center_unit_y = -center_pos.y / 16;

        s32 dx = center_unit_x - mCenterUnitX;
        s32 dy = center_unit_y - mCenterUnitY;

        for (const Item& item : mItems)
        {
            CourseView::instance()->pushBackItemWithTransform(dx, dy, item.item_type, item.data.get(), item.extra.get());
            if (item.item_type == ITEM_TYPE_BG_UNIT_OBJ)
            {
                u8 layer = *static_cast<const u8*>(item.extra.get());
                layers_changed[layer] = true;
            }
        }
    }
    else
    {
        for (const Item& item : mItems)
        {
            CourseView::instance()->pushBackItem(item.item_type, item.data.get(), item.extra.get());
            if (item.item_type == ITEM_TYPE_BG_UNIT_OBJ)
            {
                u8 layer = *static_cast<const u8*>(item.extra.get());
                layers_changed[layer] = true;
            }
        }
    }

    for (u8 layer = 0; layer < CD_FILE_LAYER_MAX_NUM; layer++)
    {
        if (!layers_changed[layer])
            continue;

        Bg::instance()->processBgCourseData(CourseView::instance()->getCourseDataFile(), layer);
        BgRenderer::instance()->createVertexBuffer(layer);
    }

    return true;
}

void ActionItemPushBack::unapply() const
{
    bool layers_changed[CD_FILE_LAYER_MAX_NUM] = {
        false, false, false
    };

    for (const Item& item : mItems)
    {
        CourseView::instance()->popBackItem(item.item_type, item.extra.get());
        if (item.item_type == ITEM_TYPE_BG_UNIT_OBJ)
        {
            u8 layer = *static_cast<const u8*>(item.extra.get());
            layers_changed[layer] = true;
        }
    }

    for (u8 layer = 0; layer < CD_FILE_LAYER_MAX_NUM; layer++)
    {
        if (!layers_changed[layer])
            continue;

        Bg::instance()->processBgCourseData(CourseView::instance()->getCourseDataFile(), layer);
        BgRenderer::instance()->createVertexBuffer(layer);
    }
}

ActionItemPushBack::Context::~Context() = default;
