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
    , mDestUnitX(static_cast<const Context*>(context)->dest_unit_x)
    , mDestUnitY(static_cast<const Context*>(context)->dest_unit_y)
{
    const char* verb;
    switch (static_cast<const Context*>(context)->action_name)
    {
    default:
    case cActionName_Add:       verb = "Add ";          break;
    case cActionName_Paste:     verb = "Paste ";        break;
    case cActionName_Duplicate: verb = "Duplicate ";    break;
    };

    RIO_ASSERT(!mItems.empty());

    const ItemType first_type = mItems.front().item_type;
    bool same_type = true;
    for (const Item& item : mItems)
    {
        if (item.item_type != first_type)
        {
            same_type = false;
            break;
        }
    }

    mDescription = (
        std::string(verb) + (
            same_type
                ? getItemCountText(u32(mItems.size()), first_type)
                : getItemCountText(u32(mItems.size()))
        )
    );
}

bool ActionItemPushBack::apply() const
{
    bool layers_changed[CD_FILE_LAYER_MAX_NUM] = {
        false, false, false
    };

    if (mTransform)
    {
        const s32 dx = mDestUnitX - mCenterUnitX;
        const s32 dy = mDestUnitY - mCenterUnitY;

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
