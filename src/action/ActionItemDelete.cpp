#include <CourseView.h>
#include <action/ActionItemDelete.h>
#include <course/Bg.h>
#include <course/BgRenderer.h>

#include <ranges>

ActionItemDelete::ActionItemDelete(const void* context)
    : IAction(context)
{
    for (const Item& item : static_cast<const Context*>(context)->items)
        mItems[item.item_id.getType()].emplace(item);

    u32 total = 0;
    u32 type_num = 0;
    ItemType last_type = ITEM_TYPE_MAX_NUM;

    for (u32 i = 0; i < ITEM_TYPE_MAX_NUM; i++)
    {
        if (mItems[i].empty())
            continue;

        total += u32(mItems[i].size());
        type_num++;
        last_type = ItemType(i);
    }

    mDescription = (
        "Delete " + (
            type_num == 1
                ? getItemCountText(total, last_type)
                : getItemCountText(total)
        )
    );
}

bool ActionItemDelete::apply() const
{
    for (u32 type = 0; type < ITEM_TYPE_MAX_NUM; type++)
        for (const Item& item : mItems[type] | std::views::reverse)
            CourseView::instance()->eraseItem(item.item_id);

    if (!mItems[ITEM_TYPE_BG_UNIT_OBJ].empty())
    {
        Bg::instance()->processBgCourseData(CourseView::instance()->getCourseDataFile());
        BgRenderer::instance()->createVertexBuffer();
    }

    return true;
}

void ActionItemDelete::unapply() const
{
    for (u32 type = 0; type < ITEM_TYPE_MAX_NUM; type++)
        for (const Item& item : mItems[type])
            CourseView::instance()->insertItem(item.item_id, item.data.get());

    if (!mItems[ITEM_TYPE_BG_UNIT_OBJ].empty())
    {
        Bg::instance()->processBgCourseData(CourseView::instance()->getCourseDataFile());
        BgRenderer::instance()->createVertexBuffer();
    }
}

ActionItemDelete::Context::~Context() = default;
