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
    bool pushed_any_object = false;

    for (const Item& item : mItems)
    {
        pushed_any_object |= item.item_type == ITEM_TYPE_BG_UNIT_OBJ;
        CourseView::instance()->pushBackItem(item.item_type, item.data.get(), item.extra.get());
    }

    if (pushed_any_object)
    {
        Bg::instance()->processBgCourseData(*CourseView::instance()->getCourseDataFile());
        BgRenderer::instance()->createVertexBuffer();
    }

    return true;
}

void ActionItemPushBack::unapply() const
{
    bool popped_any_object = false;

    for (const Item& item : mItems)
    {
        popped_any_object |= item.item_type == ITEM_TYPE_BG_UNIT_OBJ;
        CourseView::instance()->popBackItem(item.item_type, item.extra.get());
    }

    if (popped_any_object)
    {
        Bg::instance()->processBgCourseData(*CourseView::instance()->getCourseDataFile());
        BgRenderer::instance()->createVertexBuffer();
    }
}

ActionItemPushBack::Context::~Context() = default;
