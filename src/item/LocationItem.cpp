#include <CourseView.h>
#include <action/ActionItemDataChange.h>
#include <action/ActionMgr.h>
#include <graphics/QuadRenderer.h>
#include <item/LocationItem.h>

#include <imgui.h>

static const rio::Color4f sColor{
    114 / 255.f,
     42 / 255.f,
    188 / 255.f,
     70 / 255.f
};

LocationItem::LocationItem(const Location& location, u32 index)
    : ItemBase(ITEM_TYPE_LOCATION, index, location.offset.x, location.offset.y)
{
}

void LocationItem::move(s16 dx, s16 dy, bool commit)
{
    Location& location = CourseView::instance()->getCourseDataFile()->getLocation()[mItemID.getIndex()];

    location.offset.x = mBasePosition.x + dx;
    location.offset.y = mBasePosition.y + dy;
    if (commit)
    {
        mBasePosition.x = location.offset.x;
        mBasePosition.y = location.offset.y;
    }
}

void LocationItem::drawOpa()
{
    const Location& location = CourseView::instance()->getCourseDataFile()->getLocation()[mItemID.getIndex()];

    rio::Vector3f offs { f32(location.offset.x), -f32(location.offset.y + location.size.y), getZPos_() + 10 };
    rio::Vector2f size { f32(location.size.x), f32(location.size.y) };

    QuadRenderer::instance()->drawBox(
        QuadRenderer::Arg(rio::Color4f::cBlack)
            .setItemID(mItemID)
            .setSelection(mIsSelected)
            .setCornerAndSize(offs, size)
    );
}

void LocationItem::drawXlu()
{
    const Location& location = CourseView::instance()->getCourseDataFile()->getLocation()[mItemID.getIndex()];

    rio::Vector3f offs { f32(location.offset.x), -f32(location.offset.y + location.size.y), getZPos_() };
    rio::Vector2f size { f32(location.size.x), f32(location.size.y) };

    QuadRenderer::instance()->drawQuad(
        QuadRenderer::Arg(sColor)
            .setItemID(mItemID)
            .setSelection(mIsSelected)
            .setCornerAndSize(offs, size)
    );
}

void LocationItem::onSelectionChange_()
{
    if (mIsSelected)
        mSelectionData = CourseView::instance()->getCourseDataFile()->getLocation()[mItemID.getIndex()];
}

void LocationItem::drawSelectionUI()
{
    const Location& location = CourseView::instance()->getCourseDataFile()->getLocation()[mItemID.getIndex()];

    ImGui::Text("Location");
    ImGui::Separator();

    const u8 single_step = 1; //Needed for +/- buttons to appear.

    ImGui::InputScalar("Id", ImGuiDataType_U8, &mSelectionData.id, &single_step);
    ImGui::DragScalarN("Size", ImGuiDataType_U16, &mSelectionData.size, 2);

    ImGui::Separator();

    if (ImGui::Button("Apply"))
    {
        const bool anything_modified =
            mSelectionData.id       != location.id ||
            mSelectionData.size.x   != location.size.x ||
            mSelectionData.size.y   != location.size.y;

        if (anything_modified)
        {
            mSelectionData.offset = location.offset; // Copy over stuff not modified by the selection ui.

            ActionItemDataChange::Context context {
                mItemID,
                std::static_pointer_cast<const void>(
                    std::make_shared<const Location>(location)
                ),
                std::static_pointer_cast<const void>(
                    std::make_shared<const Location>(mSelectionData)
                )
            };
            ActionMgr::instance()->pushAction<ActionItemDataChange>(&context);
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Discard"))
        mSelectionData = location;
}
