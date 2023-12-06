#include <action/ActionItemDataChange.h>
#include <action/ActionMgr.h>
#include <graphics/QuadRenderer.h>
#include <item/NextGotoItem.h>

#include <imgui.h>

static const rio::Color4f sColor{
    190 / 255.f,
      0 / 255.f,
      0 / 255.f,
    120 / 255.f
};

NextGotoItem::NextGotoItem(NextGoto& next_goto, u32 index)
    : ItemBase(ITEM_TYPE_NEXT_GOTO, index, next_goto.offset.x, next_goto.offset.y)
    , mNextGoto(next_goto)
{
}

void NextGotoItem::drawOpa()
{
    rio::Vector3f offs { f32(mNextGoto.offset.x + 8), -f32(mNextGoto.offset.y + 8), getZPos_() + 10 };
    rio::Vector2f size { 16.0f, 16.0f };

    QuadRenderer::instance()->drawBox(
        QuadRenderer::Arg(rio::Color4f::cBlack)
            .setItemID(mItemID)
            .setSelection(mIsSelected)
            .setCenter(offs)
            .setSize(size)
    );
}

void NextGotoItem::drawXlu()
{
    rio::Vector3f offs { f32(mNextGoto.offset.x + 8), -f32(mNextGoto.offset.y + 8), getZPos_() };
    rio::Vector2f size { 16.0f, 16.0f };

    QuadRenderer::instance()->drawQuad(
        QuadRenderer::Arg(sColor)
            .setItemID(mItemID)
            .setSelection(mIsSelected)
            .setCenter(offs)
            .setSize(size)
    );
}

void NextGotoItem::drawSelectionUI()
{
    ImGui::Text("Entrance");
    ImGui::Separator();

    ImGui::DragScalar("Id", ImGuiDataType_U8, &mSelectionData.id);
    ImGui::DragScalar("Area", ImGuiDataType_U8, &mSelectionData.area);
    ImGui::DragScalar("Type", ImGuiDataType_U8, &mSelectionData.type);
    ImGui::DragScalar("Dest Id", ImGuiDataType_U8, &mSelectionData.destination.next_goto);
    ImGui::DragScalar("Dest Area", ImGuiDataType_U8, &mSelectionData.destination.file);
    ImGui::DragScalarN("Camera Offset", ImGuiDataType_U16, &mSelectionData.camera_offset, 2);
    ImGui::DragScalar("MP Spawn Flag", ImGuiDataType_U8, &mSelectionData.mp_spawn_flag);
    ImGui::DragScalar("MP Innter Gap", ImGuiDataType_U8, &mSelectionData.mp_inner_gap);
    ImGui::DragScalar("Flags", ImGuiDataType_U16, &mSelectionData.flag, 1.0f, nullptr, nullptr, "%04X");
    ImGui::DragScalar("Baby Yoshi Entrance", ImGuiDataType_U8, &mSelectionData.chibi_yoshi_next_goto);
    ImGui::DragScalar("Coin Edit Priority", ImGuiDataType_U8, &mSelectionData.coin_edit_priority);
    ImGui::DragScalar("Path Info", ImGuiDataType_U8, &mSelectionData.rail.info);
    ImGui::DragScalar("Path Node", ImGuiDataType_U8, &mSelectionData.rail.point);
    ImGui::DragScalar("Transition", ImGuiDataType_U8, &mSelectionData.wipe_type);

    ImGui::Separator();

    if (ImGui::Button("Apply"))
    {
        const bool anything_modified =
            mSelectionData.id                       != mNextGoto.id ||
            mSelectionData.area                     != mNextGoto.area ||
            mSelectionData.type                     != mNextGoto.type ||
            mSelectionData.destination.next_goto    != mNextGoto.destination.next_goto ||
            mSelectionData.destination.file         != mNextGoto.destination.file ||
            mSelectionData.camera_offset.x          != mNextGoto.camera_offset.x ||
            mSelectionData.camera_offset.y          != mNextGoto.camera_offset.y ||
            mSelectionData.mp_spawn_flag            != mNextGoto.mp_spawn_flag ||
            mSelectionData.mp_inner_gap             != mNextGoto.mp_inner_gap ||
            mSelectionData.flag                     != mNextGoto.flag ||
            mSelectionData.chibi_yoshi_next_goto    != mNextGoto.chibi_yoshi_next_goto ||
            mSelectionData.coin_edit_priority       != mNextGoto.coin_edit_priority ||
            mSelectionData.rail.info                != mNextGoto.rail.info ||
            mSelectionData.rail.point               != mNextGoto.rail.point ||
            mSelectionData.wipe_type                != mNextGoto.wipe_type;

        if (anything_modified)
        {
            mSelectionData.offset = mNextGoto.offset; // Copy over stuff not modified by the selection ui.

            ActionItemDataChange::Context context {
                mItemID,
                std::static_pointer_cast<const void>(
                    std::make_shared<const NextGoto>(mNextGoto)
                ),
                std::static_pointer_cast<const void>(
                    std::make_shared<const NextGoto>(mSelectionData)
                )
            };
            ActionMgr::instance()->pushAction<ActionItemDataChange>(&context);
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Discard"))
        mSelectionData = mNextGoto;
}

void NextGotoItem::onSelectionChange_()
{
    if (mIsSelected)
        mSelectionData = mNextGoto;
}
