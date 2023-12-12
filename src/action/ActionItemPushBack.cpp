#include <CourseView.h>
#include <action/ActionItemPushBack.h>
#include <course/Bg.h>
#include <course/BgRenderer.h>

ActionItemPushBack::ActionItemPushBack(const void* context)
    : IAction(context)
    , mItems(static_cast<const Context*>(context)->items)
{
}

bool ActionItemPushBack::apply() const
{
    bool layers_changed[CD_FILE_LAYER_MAX_NUM] = {
        false, false, false
    };

    for (const Item& item : mItems)
    {
        CourseView::instance()->pushBackItem(item.item_type, item.data.get(), item.extra.get());
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

        Bg::instance()->processBgCourseData(*CourseView::instance()->getCourseDataFile(), layer);
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

        Bg::instance()->processBgCourseData(*CourseView::instance()->getCourseDataFile(), layer);
        BgRenderer::instance()->createVertexBuffer(layer);
    }
}

ActionItemPushBack::Context::~Context() = default;
