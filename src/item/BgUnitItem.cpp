#include <CourseView.h>
#include <MainWindow.h>
#include <course/Bg.h>
#include <course/BgRenderer.h>
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
    u16 env = (mBgCourseData.type >> 12) & 3;
    u16 idx = mBgCourseData.type & 0xFFF;

    ImGui::Text("Object");
    ImGui::Separator();

    const u16 min_value = 0, tileset_max = 3, index_max = 0xFFF;
    ImGui::DragScalar("Tileset", ImGuiDataType_U16, &env, 1.0f, &min_value, &tileset_max, nullptr, ImGuiSliderFlags_AlwaysClamp);
    ImGui::DragScalar("Index", ImGuiDataType_U16, &idx, 1.0f, &min_value, &index_max, nullptr, ImGuiSliderFlags_AlwaysClamp);
    ImGui::DragScalarN("Size", ImGuiDataType_U16, &mBgCourseData.size, 2);
    ImGui::DragScalar("Flag", ImGuiDataType_U8, &mBgCourseData.flag);

    mBgCourseData.type = (env << 12) | idx;
}
