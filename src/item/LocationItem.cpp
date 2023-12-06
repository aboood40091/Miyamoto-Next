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

LocationItem::LocationItem(Location& location, u32 index)
    : ItemBase(ITEM_TYPE_LOCATION, index, location.offset.x, location.offset.y)
    , mLocation(location)
{
}

void LocationItem::drawOpa()
{
    rio::Vector3f offs { f32(mLocation.offset.x), -f32(mLocation.offset.y + mLocation.size.y), getZPos_() + 10 };
    rio::Vector2f size { f32(mLocation.size.x), f32(mLocation.size.y) };

    QuadRenderer::instance()->drawBox(
        QuadRenderer::Arg(rio::Color4f::cBlack)
            .setItemID(mItemID)
            .setSelection(mIsSelected)
            .setCornerAndSize(offs, size)
    );
}

void LocationItem::drawXlu()
{
    rio::Vector3f offs { f32(mLocation.offset.x), -f32(mLocation.offset.y + mLocation.size.y), getZPos_() };
    rio::Vector2f size { f32(mLocation.size.x), f32(mLocation.size.y) };

    QuadRenderer::instance()->drawQuad(
        QuadRenderer::Arg(sColor)
            .setItemID(mItemID)
            .setSelection(mIsSelected)
            .setCornerAndSize(offs, size)
    );
}

void LocationItem::drawSelectionUI()
{
    ImGui::Text("Location");
    ImGui::Separator();

    ImGui::DragScalar("Id", ImGuiDataType_U8, &mSelectionData.id);
    ImGui::DragScalarN("Size", ImGuiDataType_U16, &mSelectionData.size, 2);

    ImGui::Separator();

    if (ImGui::Button("Apply"))
    {
        const bool anything_modified =
            mSelectionData.id       != mLocation.id ||
            mSelectionData.size.x   != mLocation.size.x ||
            mSelectionData.size.y   != mLocation.size.y;

        if (anything_modified)
        {
            mSelectionData.offset = mLocation.offset; // Copy over stuff not modified by the selection ui.

            ActionItemDataChange::Context context {
                mItemID,
                std::static_pointer_cast<const void>(
                    std::make_shared<const Location>(mLocation)
                ),
                std::static_pointer_cast<const void>(
                    std::make_shared<const Location>(mSelectionData)
                )
            };
            ActionMgr::instance()->pushAction<ActionItemDataChange>(&context);
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Revert"))
        mSelectionData = mLocation;
}

void LocationItem::onSelectionChange_()
{
    if (mIsSelected)
        mSelectionData = mLocation;
}
