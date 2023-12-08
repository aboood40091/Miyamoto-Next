#include <action/ActionItemDataChange.h>
#include <action/ActionMgr.h>
#include <graphics/QuadRenderer.h>
#include <item/MapActorItem.h>

#include <imgui.h>

static const rio::Color4f sColor{
      0 / 255.f,
     92 / 255.f,
    196 / 255.f,
    120 / 255.f
};

MapActorItem::MapActorItem(MapActorData& map_actor_data, u32 index)
    : ItemBase(ITEM_TYPE_MAP_ACTOR, index, map_actor_data.offset.x, map_actor_data.offset.y)
    , mMapActorData(map_actor_data)
{
}

void MapActorItem::drawOpa(const rio::lyr::DrawInfo& draw_info)
{
    if (!drawBox_())
        return;

    rio::Vector3f offs { f32(mMapActorData.offset.x + 8), -f32(mMapActorData.offset.y + 8), getDefaultZPos(mMapActorData.layer) + 10 };
    rio::Vector2f size { 16.0f, 16.0f };

    QuadRenderer::instance()->drawBox(
        QuadRenderer::Arg(rio::Color4f::cBlack)
            .setItemID(mItemID)
            .setSelection(mIsSelected)
            .setCenter(offs)
            .setSize(size)
    );
}

void MapActorItem::drawXlu(const rio::lyr::DrawInfo& draw_info)
{
    if (!drawBox_())
        return;

    rio::Vector3f offs { f32(mMapActorData.offset.x + 8), -f32(mMapActorData.offset.y + 8), getDefaultZPos(mMapActorData.layer) };
    rio::Vector2f size { 16.0f, 16.0f };

    QuadRenderer::instance()->drawQuad(
        QuadRenderer::Arg(sColor)
            .setItemID(mItemID)
            .setSelection(mIsSelected)
            .setCenter(offs)
            .setSize(size)
    );
}

void MapActorItem::drawSelectionUI()
{
    ImGui::Text("Actor (Id %d)", mMapActorData.id);
    ImGui::Separator();

    const u8 single_step = 1; //Needed for +/- buttons to appear.

    ImGui::InputScalarN("Events", ImGuiDataType_U8, &mSelectionData.event_id, 2, &single_step);
    ImGui::InputScalarN("Settings", ImGuiDataType_U32, &mSelectionData.settings, 2, nullptr, nullptr, "%08X");
    ImGui::InputScalar("Area", ImGuiDataType_U8, &mSelectionData.area);
    ImGui::InputScalar("Layer", ImGuiDataType_U8, &mSelectionData.layer);
    ImGui::InputScalar("Movement ID", ImGuiDataType_U8, &mSelectionData.movement_id, &single_step);
    ImGui::InputScalar("Link ID", ImGuiDataType_U8, &mSelectionData.link_id, &single_step);
    ImGui::InputScalar("Init State", ImGuiDataType_U8, &mSelectionData.init_state);

    ImGui::Separator();

    if (ImGui::Button("Apply"))
    {
        DataChangeFlag data_change_flag = DATA_CHANGE_FLAG_NONE;

        if (mSelectionData.event_id != mMapActorData.event_id)
            data_change_flag |= DATA_CHANGE_FLAG_EVENT_ID;

        if (mSelectionData.settings[0] != mMapActorData.settings[0])
            data_change_flag |= DATA_CHANGE_FLAG_SETTINGS_0;

        if (mSelectionData.settings[1] != mMapActorData.settings[1])
            data_change_flag |= DATA_CHANGE_FLAG_SETTINGS_1;

        if (mSelectionData.area != mMapActorData.area)
            data_change_flag |= DATA_CHANGE_FLAG_AREA;

        if (mSelectionData.layer != mMapActorData.layer)
            data_change_flag |= DATA_CHANGE_FLAG_LAYER;

        if (mSelectionData.movement_id != mMapActorData.movement_id)
            data_change_flag |= DATA_CHANGE_FLAG_MOVEMENT_ID;

        if (mSelectionData.link_id != mMapActorData.link_id)
            data_change_flag |= DATA_CHANGE_FLAG_LINK_ID;

        if (mSelectionData.init_state != mMapActorData.init_state)
            data_change_flag |= DATA_CHANGE_FLAG_INIT_STATE;

        if (data_change_flag)
        {
            mSelectionData.id = mMapActorData.id; // Copy over stuff not modified by the selection ui.
            mSelectionData.offset = mMapActorData.offset; // Copy over stuff not modified by the selection ui.

            ActionItemDataChange::Context context {
                mItemID,
                std::static_pointer_cast<const void>(
                    std::make_shared<const MapActorData>(mMapActorData)
                ),
                std::static_pointer_cast<const void>(
                    std::make_shared<const MapActorData>(mSelectionData)
                ),
                data_change_flag
            };
            ActionMgr::instance()->pushAction<ActionItemDataChange>(&context);
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Discard"))
        mSelectionData = mMapActorData;
}

void MapActorItem::onSelectionChange_()
{
    if (mIsSelected)
        mSelectionData = mMapActorData;
}
