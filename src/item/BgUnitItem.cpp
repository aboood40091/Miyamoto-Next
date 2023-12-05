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

    u16 env = (mBgCourseData.type >> 12) & 3;
    u16 idx = mBgCourseData.type & 0xFFF;

    ImGui::Text("Object");
    ImGui::Separator();

    const u16 min_value_u16 = 0, env_max = CD_FILE_ENV_MAX_NUM - 1, index_max = 0xFFF;
    const u8 min_value_u8 = 0, flag_max = 24;

    bool type_modified = ImGui::DragScalar("Environment Slot", ImGuiDataType_U16, &env, 1.0f, &min_value_u16, &env_max, nullptr, ImGuiSliderFlags_AlwaysClamp);
    type_modified     |= ImGui::DragScalar("Object Index", ImGuiDataType_U16, &idx, 1.0f, &min_value_u16, &index_max, nullptr, ImGuiSliderFlags_AlwaysClamp);
    bool size_modified = ImGui::DragScalarN("Size", ImGuiDataType_U16, &mBgCourseData.size, 2);
    bool flag_modified = ImGui::DragScalar("Flag", ImGuiDataType_U8, &mBgCourseData.flag, 1.0f, &min_value_u8, &flag_max, nullptr, ImGuiSliderFlags_AlwaysClamp);

    if (type_modified)
    {
        const BgUnitFile* file = Bg::instance()->getUnitFile(p_cd_file->getEnvironment(env));
        if (file == nullptr || idx >= file->getObjCount())
            type_modified = false;
    }

    if (type_modified)
        mBgCourseData.type = (env << 12) | idx;

    if (type_modified | size_modified | flag_modified)
    {
        Bg::instance()->processBgCourseData(*p_cd_file);
        BgRenderer::instance()->createVertexBuffer(mItemID.getIndex() >> 22);
        BgRenderer::instance()->calcSelectionVertexBuffer({ mItemID });
    }
}
