#include <CourseView.h>
#include <MainWindow.h>
#include <course/Bg.h>
#include <course/BgRenderer.h>
#include <course/BgUnitFile.h>
#include <item/BgUnitItem.h>
#include <action/ActionMgr.h>
#include <action/ActionBgUnitItemEdit.h>

#include <rio.h>

#include <imgui.h>

BgUnitItem::BgUnitItem(BgCourseData& data, u32 index)
    : ItemBase(ITEM_TYPE_BG_UNIT_OBJ, index, data.offset.x, data.offset.y)
    , mBgCourseData(data)
    , mSelectionData(data)
{
}

void BgUnitItem::move(s16 dx, s16 dy, bool commit)
{
    dx /= 16;
    dy /= 16;

    if (dx == 0 && dy == 0)
    {
        if (mBgCourseData.offset.x == mBasePosition.x && mBgCourseData.offset.y == mBasePosition.y)
            return;

        mBgCourseData.offset.x = mBasePosition.x;
        mBgCourseData.offset.y = mBasePosition.y;
    }
    else
    {
        mBgCourseData.offset.x = mBasePosition.x + dx;
        mBgCourseData.offset.y = mBasePosition.y + dy;
        if (commit)
        {
            mBasePosition.x = mBgCourseData.offset.x;
            mBasePosition.y = mBgCourseData.offset.y;
        }
    }
}

void BgUnitItem::drawSelectionUI()
{
    const CourseDataFile* p_cd_file = static_cast<MainWindow*>(rio::sRootTask)->getCourseView()->getCourseDataFile();
    RIO_ASSERT(p_cd_file != nullptr);

    ImGui::Text("Object");
    ImGui::Separator();

    u16 env = mSelectionData.type >> 12;
    u16 idx = mSelectionData.type & 0xFFF;

    const u16 env_max = CD_FILE_ENV_MAX_NUM - 1;
    const u16 idx_max = 0xFFF;
    const u8 flag_max = 24;

    bool type_modified = ImGui::DragScalar("Environment Slot", ImGuiDataType_U16, &env, 1.0f, nullptr, &env_max, nullptr, ImGuiSliderFlags_AlwaysClamp);
    type_modified     |= ImGui::DragScalar("Object Index", ImGuiDataType_U16, &idx, 1.0f, nullptr, &idx_max, nullptr, ImGuiSliderFlags_AlwaysClamp);
    ImGui::DragScalarN("Size", ImGuiDataType_U16, &mSelectionData.size, 2);
    ImGui::DragScalar("Flag", ImGuiDataType_U8, &mSelectionData.flag, 1.0f, nullptr, &flag_max, nullptr, ImGuiSliderFlags_AlwaysClamp);

    if (type_modified)
    {
        const BgUnitFile* file = Bg::instance()->getUnitFile(p_cd_file->getEnvironment(env));
        if (!file || idx >= file->getObjCount())
            mSelectionData.type = mBgCourseData.type; //Revert type if not a valid object.
        else
            mSelectionData.type = (env << 12) | idx;
    }

    ImGui::Separator();

    if (ImGui::Button("Apply"))
    {
        const bool anything_modified =
            mSelectionData.type != mBgCourseData.type ||
            mSelectionData.size.x != mBgCourseData.size.x ||
            mSelectionData.size.y != mBgCourseData.size.y ||
            mSelectionData.flag != mBgCourseData.flag;

        if (anything_modified)
        {
            mSelectionData.offset = mBgCourseData.offset; //Copy over stuff not modified by the selection ui.

            ActionBgUnitItemEdit::Context context { mItemID, mBgCourseData, mSelectionData };
            ActionMgr::instance()->pushAction<ActionBgUnitItemEdit>(&context);
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Revert"))
        mSelectionData = mBgCourseData;
}
