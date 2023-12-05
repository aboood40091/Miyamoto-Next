#include <CourseView.h>
#include <MainWindow.h>
#include <course/Bg.h>
#include <course/BgRenderer.h>
#include <course/BgUnitFile.h>
#include <item/BgUnitItem.h>

#include <rio.h>

#include <imgui.h>

BgUnitItem::BgUnitItem(BgCourseData& data, u32 index)
    : ItemBase(ITEM_TYPE_BG_UNIT_OBJ, index, data.offset.x, data.offset.y)
    , mBgCourseData(data)
{
    mSelectionData.env = mBgCourseData.type >> 12;
    mSelectionData.idx = mBgCourseData.type & 0xFFF;
    mSelectionData.width = mBgCourseData.size.x;
    mSelectionData.height = mBgCourseData.size.y;
    mSelectionData.flag = mBgCourseData.flag;
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
    ImGui::Text("Object");
    ImGui::Separator();

    const u16 env_max = CD_FILE_ENV_MAX_NUM - 1;
    const u16 idx_max = 0xFFF;
    const u8 flag_max = 24;

    ImGui::DragScalar("Environment Slot", ImGuiDataType_U16, &mSelectionData.env, 1.0f, nullptr, &env_max, nullptr, ImGuiSliderFlags_AlwaysClamp);
    ImGui::DragScalar("Object Index", ImGuiDataType_U16, &mSelectionData.idx, 1.0f, nullptr, &idx_max, nullptr, ImGuiSliderFlags_AlwaysClamp);
    ImGui::DragScalar("Width", ImGuiDataType_U16, &mSelectionData.width);
    ImGui::DragScalar("Height", ImGuiDataType_U16, &mSelectionData.height);
    ImGui::DragScalar("Flag", ImGuiDataType_U8, &mSelectionData.flag, 1.0f, nullptr, &flag_max, nullptr, ImGuiSliderFlags_AlwaysClamp);

    ImGui::Separator();

    if (ImGui::Button("Apply"))
    {
        u16 type = (mSelectionData.env << 12) | mSelectionData.idx;

        const CourseDataFile* p_cd_file = static_cast<MainWindow*>(rio::sRootTask)->getCourseView()->getCourseDataFile();
        RIO_ASSERT(p_cd_file != nullptr);

        const BgUnitFile* file = Bg::instance()->getUnitFile(p_cd_file->getEnvironment(mSelectionData.env));
        if (!file || mSelectionData.idx >= file->getObjCount())
            type = mBgCourseData.type;

        const bool modified = type != mBgCourseData.type ||
            mSelectionData.width != mBgCourseData.size.x ||
            mSelectionData.height != mBgCourseData.size.y ||
            mSelectionData.flag != mBgCourseData.flag;

        if (modified)
        {
            mBgCourseData.type = type;
            mBgCourseData.size.x = mSelectionData.width;
            mBgCourseData.size.y = mSelectionData.height;
            mBgCourseData.flag = mSelectionData.flag;

            Bg::instance()->processBgCourseData(*p_cd_file);
            BgRenderer::instance()->createVertexBuffer(mItemID.getIndex() >> 22);
            BgRenderer::instance()->calcSelectionVertexBuffer({ mItemID });
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Discard"))
    {
        mSelectionData.env = mBgCourseData.type >> 12;
        mSelectionData.idx = mBgCourseData.type & 0xFFF;
        mSelectionData.width = mBgCourseData.size.x;
        mSelectionData.height = mBgCourseData.size.y;
        mSelectionData.flag = mBgCourseData.flag;
    }
}
