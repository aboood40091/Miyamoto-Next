#include <CourseView.h>
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

NextGotoItem::NextGotoItem(const NextGoto& next_goto, u32 index)
    : ItemBase(ITEM_TYPE_NEXT_GOTO, index, next_goto.offset.x, next_goto.offset.y)
{
}

void NextGotoItem::move(s16 dx, s16 dy, bool commit)
{
    NextGoto& next_goto = CourseView::instance()->getCourseDataFile()->getNextGoto()[mItemID.getIndex()];

    next_goto.offset.x = mBasePosition.x + dx;
    next_goto.offset.y = mBasePosition.y + dy;
    if (commit)
    {
        mBasePosition.x = next_goto.offset.x;
        mBasePosition.y = next_goto.offset.y;
    }
}

void NextGotoItem::drawOpa()
{
    const NextGoto& next_goto = CourseView::instance()->getCourseDataFile()->getNextGoto()[mItemID.getIndex()];

    rio::Vector3f offs { f32(next_goto.offset.x + 8), -f32(next_goto.offset.y + 8), getZPos_() + 10 };
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
    const NextGoto& next_goto = CourseView::instance()->getCourseDataFile()->getNextGoto()[mItemID.getIndex()];

    rio::Vector3f offs { f32(next_goto.offset.x + 8), -f32(next_goto.offset.y + 8), getZPos_() };
    rio::Vector2f size { 16.0f, 16.0f };

    QuadRenderer::instance()->drawQuad(
        QuadRenderer::Arg(sColor)
            .setItemID(mItemID)
            .setSelection(mIsSelected)
            .setCenter(offs)
            .setSize(size)
    );
}

void NextGotoItem::onSelectionChange_()
{
    if (mIsSelected)
        mSelectionData = CourseView::instance()->getCourseDataFile()->getNextGoto()[mItemID.getIndex()];
}

void NextGotoItem::drawSelectionUI()
{
    const NextGoto& next_goto = CourseView::instance()->getCourseDataFile()->getNextGoto()[mItemID.getIndex()];

    ImGui::Text("Entrance");
    ImGui::Separator();

    const u8 single_step = 1; //Needed for +/- buttons to appear.

    ImGui::InputScalar("Id", ImGuiDataType_U8, &mSelectionData.id, &single_step);
    ImGui::InputScalar("Area", ImGuiDataType_U8, &mSelectionData.area, &single_step);
    ImGui::InputScalar("Type", ImGuiDataType_U8, &mSelectionData.type);
    ImGui::InputScalar("Dest Id", ImGuiDataType_U8, &mSelectionData.destination.next_goto, &single_step);
    ImGui::InputScalar("Dest Area", ImGuiDataType_U8, &mSelectionData.destination.file, &single_step);
    ImGui::DragScalarN("Camera Offset", ImGuiDataType_U16, &mSelectionData.camera_offset, 2);
    ImGui::InputScalar("MP Spawn Flag", ImGuiDataType_U8, &mSelectionData.mp_spawn_flag);
    ImGui::InputScalar("MP Inner Gap", ImGuiDataType_U8, &mSelectionData.mp_inner_gap);
    ImGui::InputScalar("Flags", ImGuiDataType_U16, &mSelectionData.flag, nullptr, nullptr, "%04X");
    ImGui::InputScalar("Baby Yoshi Entrance", ImGuiDataType_U8, &mSelectionData.chibi_yoshi_next_goto, &single_step);
    ImGui::InputScalar("Coin Edit Priority", ImGuiDataType_U8, &mSelectionData.coin_edit_priority, &single_step);
    ImGui::InputScalar("Path Info", ImGuiDataType_U8, &mSelectionData.rail.info, &single_step);
    ImGui::InputScalar("Path Node", ImGuiDataType_U8, &mSelectionData.rail.point, &single_step);
    ImGui::InputScalar("Transition", ImGuiDataType_U8, &mSelectionData.wipe_type);

    ImGui::Separator();

    if (ImGui::Button("Apply"))
    {
        const bool anything_modified =
            mSelectionData.id                       != next_goto.id ||
            mSelectionData.area                     != next_goto.area ||
            mSelectionData.type                     != next_goto.type ||
            mSelectionData.destination.next_goto    != next_goto.destination.next_goto ||
            mSelectionData.destination.file         != next_goto.destination.file ||
            mSelectionData.camera_offset.x          != next_goto.camera_offset.x ||
            mSelectionData.camera_offset.y          != next_goto.camera_offset.y ||
            mSelectionData.mp_spawn_flag            != next_goto.mp_spawn_flag ||
            mSelectionData.mp_inner_gap             != next_goto.mp_inner_gap ||
            mSelectionData.flag                     != next_goto.flag ||
            mSelectionData.chibi_yoshi_next_goto    != next_goto.chibi_yoshi_next_goto ||
            mSelectionData.coin_edit_priority       != next_goto.coin_edit_priority ||
            mSelectionData.rail.info                != next_goto.rail.info ||
            mSelectionData.rail.point               != next_goto.rail.point ||
            mSelectionData.wipe_type                != next_goto.wipe_type;

        if (anything_modified)
        {
            mSelectionData.offset = next_goto.offset; // Copy over stuff not modified by the selection ui.

            ActionItemDataChange::Context context {
                mItemID,
                std::static_pointer_cast<const void>(
                    std::make_shared<const NextGoto>(next_goto)
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
        mSelectionData = next_goto;
}
