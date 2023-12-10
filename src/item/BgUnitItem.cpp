#include <CourseView.h>
#include <action/ActionItemDataChange.h>
#include <action/ActionMgr.h>
#include <course/Bg.h>
#include <course/BgRenderer.h>
#include <course/BgUnitFile.h>
#include <item/BgUnitItem.h>

#include <rio.h>

#include <imgui.h>

BgUnitItem::BgUnitItem(BgCourseData& data, u32 index)
    : ItemBase(ITEM_TYPE_BG_UNIT_OBJ, index, data.offset.x, data.offset.y)
{
}

void BgUnitItem::move(s16 dx, s16 dy, bool commit)
{
    dx /= 16;
    dy /= 16;

    BgCourseData& data = CourseView::instance()->getCourseDataFile()->getBgData(mItemID.getIndex() >> 22)[mItemID.getIndex() & 0x003FFFFF];

    if (dx == 0 && dy == 0)
    {
        if (data.offset.x == mBasePosition.x && data.offset.y == mBasePosition.y)
            return;

        data.offset.x = mBasePosition.x;
        data.offset.y = mBasePosition.y;
    }
    else
    {
        data.offset.x = mBasePosition.x + dx;
        data.offset.y = mBasePosition.y + dy;
        if (commit)
        {
            mBasePosition.x = data.offset.x;
            mBasePosition.y = data.offset.y;
        }
    }
}

void BgUnitItem::onSelectionChange_()
{
    if (mIsSelected)
        mSelectionData = CourseView::instance()->getCourseDataFile()->getBgData(mItemID.getIndex() >> 22)[mItemID.getIndex() & 0x003FFFFF];
}

void BgUnitItem::drawSelectionUI()
{
    const CourseDataFile* p_cd_file = CourseView::instance()->getCourseDataFile();
    RIO_ASSERT(p_cd_file != nullptr);

    const BgCourseData& data = p_cd_file->getBgData(mItemID.getIndex() >> 22)[mItemID.getIndex() & 0x003FFFFF];

    ImGui::Text("Object");
    ImGui::Separator();

    const u16 single_step = 1; //Needed for +/- buttons to appear.

    u16 env = mSelectionData.type >> 12;
    u16 idx = mSelectionData.type & 0xFFF;

    bool type_modified  = ImGui::InputScalar("Environment Slot", ImGuiDataType_U16, &env, &single_step);
         type_modified |= ImGui::InputScalar("Object Index", ImGuiDataType_U16, &idx, &single_step);

     if (type_modified)
    {
        const BgUnitFile* file = Bg::instance()->getUnitFile(p_cd_file->getEnvironment(env));
        if (file && idx < file->getObjCount())
            mSelectionData.type = (env << 12) | idx;
    }

    int flag = mSelectionData.flag;

    if (ImGui::InputInt("Override", &flag, 1))
        mSelectionData.flag = std::clamp(flag, 0, 24);

    ImGui::DragScalarN("Size", ImGuiDataType_U16, &mSelectionData.size, 2);

    ImGui::Separator();

    if (ImGui::Button("Apply"))
    {
        const bool anything_modified =
            mSelectionData.type != data.type ||
            mSelectionData.size.x != data.size.x ||
            mSelectionData.size.y != data.size.y ||
            mSelectionData.flag != data.flag;

        if (anything_modified)
        {
            mSelectionData.offset = data.offset; // Copy over stuff not modified by the selection ui.

            ActionItemDataChange::Context context {
                mItemID,
                std::static_pointer_cast<const void>(
                    std::make_shared<const BgCourseData>(data)
                ),
                std::static_pointer_cast<const void>(
                    std::make_shared<const BgCourseData>(mSelectionData)
                )
            };
            ActionMgr::instance()->pushAction<ActionItemDataChange>(&context);

            BgRenderer::instance()->calcSelectionVertexBuffer({ mItemID });
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Discard"))
        mSelectionData = data;
}
