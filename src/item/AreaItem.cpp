#include <CourseView.h>
#include <action/ActionItemDataChange.h>
#include <action/ActionMgr.h>
#include <graphics/QuadRenderer.h>
#include <item/AreaItem.h>

#include <imgui.h>

static const rio::Color4f sColor{
    145 / 255.f,
    200 / 255.f,
    255 / 255.f,
    255 / 255.f,
};

static const rio::Color4f sMaskColor{
      0 / 255.f,
      0 / 255.f,
      0 / 255.f,
     48 / 255.f
};

AreaItem::AreaItem(const AreaData& area_data, u32 index)
    : ItemBase(ITEM_TYPE_AREA, index, area_data.offset.x, area_data.offset.y)
{
}

void AreaItem::move(s16 dx, s16 dy, bool commit)
{
    AreaData& area_data = CourseView::instance()->getCourseDataFile().getAreaData()[mItemID.getIndex()];

    area_data.offset.x = mBasePosition.x + dx;
    area_data.offset.y = mBasePosition.y + dy;
    if (commit)
    {
        mBasePosition.x = area_data.offset.x;
        mBasePosition.y = area_data.offset.y;
    }
}

void AreaItem::drawOpa()
{
    const AreaData& area_data = CourseView::instance()->getCourseDataFile().getAreaData()[mItemID.getIndex()];

    rio::Vector3f offs { f32(area_data.offset.x), -f32(area_data.offset.y + area_data.size.y), getZPos_() + 10 };
    rio::Vector2f size { f32(area_data.size.x), f32(area_data.size.y) };

    QuadRenderer::instance()->drawBox(
        QuadRenderer::Arg(sColor)
            .setItemID(mItemID)
            .setSelection(mIsSelected)
            .setCornerAndSize(offs, size)
    );
}

void AreaItem::drawXlu()
{
    const AreaData& area_data = CourseView::instance()->getCourseDataFile().getAreaData()[mItemID.getIndex()];

    if (!(area_data.mask & 0x20))
        return;

    rio::Vector3f offs { f32(area_data.offset.x), -f32(area_data.offset.y + area_data.size.y), getZPos_() };
    rio::Vector2f size { f32(area_data.size.x), f32(area_data.size.y) };

    QuadRenderer::instance()->drawQuad(
        QuadRenderer::Arg(sMaskColor)
            .setCornerAndSize(offs, size)
    );
}

void AreaItem::onSelectionChange_()
{
    if (mIsSelected)
        mSelectionData = CourseView::instance()->getCourseDataFile().getAreaData()[mItemID.getIndex()];
}

void AreaItem::drawSelectionUI()
{
    const AreaData& area_data = CourseView::instance()->getCourseDataFile().getAreaData()[mItemID.getIndex()];

    ImGui::Text("Area");
    ImGui::Separator();

    const u8 single_step = 1; //Needed for +/- buttons to appear.

    ImGui::InputScalar("ID", ImGuiDataType_U8, &mSelectionData.id, &single_step);

    ImGui::Separator();
    ImGui::DragScalarN("Offset", ImGuiDataType_U16, &mSelectionData.offset, 2);
    ImGui::DragScalarN("Size", ImGuiDataType_U16, &mSelectionData.size, 2);

    ImGui::Separator();

    ImGui::InputScalar("Color OBJ (Unused)", ImGuiDataType_U16, &mSelectionData.color_obj);
    ImGui::InputScalar("Color BG (Unused)", ImGuiDataType_U16, &mSelectionData.color_bg);

    ImGui::Separator();

    ImGui::InputScalar("Scroll ID", ImGuiDataType_U8, &mSelectionData.scroll, &single_step);
    if (ImGui::BeginChild("Scroll Preview", ImVec2(0, 0), ImGuiChildFlags_FrameStyle | ImGuiChildFlags_AutoResizeY))
    {
        if (ImGui::CollapsingHeader("Scroll Data (Preview)"))
        {
            const ScrollData* p_scroll_data = nullptr;
            for (const ScrollData& scroll_data : CourseView::instance()->getCourseDataFile().getScrollData())
            {
                if (scroll_data.id == mSelectionData.scroll)
                {
                    p_scroll_data = &scroll_data;
                    break;
                }
            }

            if (p_scroll_data == nullptr)
                ImGui::TextDisabled("Invalid");

            else
            {
                ScrollData& scroll_data = *const_cast<ScrollData*>(p_scroll_data);
                ImGui::BeginDisabled();
                {
                  //ImGui::InputScalar("ID", ImGuiDataType_U16, &scroll_data.id);
                    ImGui::DragScalarN("Bound", ImGuiDataType_S32, &(scroll_data.bound[0]), 2);
                    ImGui::DragScalarN("Bound (Lakitu)", ImGuiDataType_S32, &(scroll_data.bound[1]), 2);
                    ImGui::InputScalar("Flags", ImGuiDataType_U16, &scroll_data.flag, nullptr, nullptr, "%04X");
                    ImGui::DragScalarN("Multiplayer Bound Adjust", ImGuiDataType_S16, &scroll_data.mp_bound_adjust, 2);
                }
                ImGui::EndDisabled();
            }
        }
    }
    ImGui::EndChild();

    ImGui::Separator();

    ImGui::InputScalar("Zoom Type", ImGuiDataType_U8, &mSelectionData.zoom_type);
    ImGui::InputScalar("Zoom ID", ImGuiDataType_U8, &mSelectionData.zoom_id);
    ImGui::InputScalar("Zoom Change", ImGuiDataType_U8, &mSelectionData.zoom_change);

    ImGui::Separator();

    ImGui::InputScalar("Mask No", ImGuiDataType_U8, &mSelectionData.mask);

    ImGui::Separator();

    ImGui::InputScalar("Distant View ID", ImGuiDataType_U8, &mSelectionData.bg2, &single_step);
    if (ImGui::BeginChild("DV Preview", ImVec2(0, 0), ImGuiChildFlags_FrameStyle | ImGuiChildFlags_AutoResizeY))
    {
        if (ImGui::CollapsingHeader("Distant View Data (Preview)"))
        {
            const DistantViewData* p_dv_data = nullptr;
            for (const DistantViewData& dv_data : CourseView::instance()->getCourseDataFile().getDistantViewData())
            {
                if (dv_data.id == mSelectionData.bg2)
                {
                    p_dv_data = &dv_data;
                    break;
                }
            }

            if (p_dv_data == nullptr)
                ImGui::TextDisabled("Invalid");

            else
            {
                DistantViewData& dv_data = *const_cast<DistantViewData*>(p_dv_data);
                ImGui::BeginDisabled();
                {
                  //ImGui::InputScalar("ID", ImGuiDataType_U16, &dv_data.id);
                    ImGui::DragScalarN("Offset (Unused)", ImGuiDataType_S16, &dv_data.offset, 3);
                    ImGui::InputText("Name", dv_data.name, CD_FILE_DV_NAME_MAX_LEN + 1);
                    ImGui::InputScalar("Parallax Mode (Unused)", ImGuiDataType_U8, &dv_data.parallax_mode);
                }
                ImGui::EndDisabled();
            }
        }
    }
    ImGui::EndChild();
    ImGui::InputScalar("Unused 0x13", ImGuiDataType_U8, &mSelectionData.bg3);

    ImGui::Separator();

    ImGui::InputScalar("Direction", ImGuiDataType_U8, &mSelectionData.direction);

    ImGui::Separator();

    ImGui::InputScalar("Unknown 0x15", ImGuiDataType_U8, &mSelectionData._15);

    ImGui::Separator();

    ImGui::InputScalar("Bgm", ImGuiDataType_U8, &mSelectionData.bgm);
    ImGui::InputScalar("Bgm Mode", ImGuiDataType_U8, &mSelectionData.bgm_mode);

    ImGui::Separator();

    ImGui::InputScalar("Unused 0x18", ImGuiDataType_U8, &mSelectionData.dv);

    ImGui::Separator();

    ImGui::InputScalar("Flags", ImGuiDataType_U8, &mSelectionData.flag, nullptr, nullptr, "%02X");

    ImGui::Separator();

    if (ImGui::Button("Apply"))
    {
        const bool anything_modified = memcmp(&mSelectionData, &area_data, sizeof(AreaData)) != 0;

        if (anything_modified)
        {
            ActionItemDataChange::Context context {
                mItemID,
                std::static_pointer_cast<const void>(
                    std::make_shared<const AreaData>(area_data)
                ),
                std::static_pointer_cast<const void>(
                    std::make_shared<const AreaData>(mSelectionData)
                )
            };
            ActionMgr::instance()->pushAction<ActionItemDataChange>(&context);
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Discard"))
        mSelectionData = area_data;
}
