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

    if (ImGui::DragScalarN("Events", ImGuiDataType_U8, &mMapActorData.event_id, 2))
        onDataChange(DATA_CHANGE_FLAG_EVENT_ID);
    if (ImGui::DragScalar("Settings 1", ImGuiDataType_U32, &mMapActorData.settings[0], 1.0f, nullptr, nullptr, "%08X"))
        onDataChange(DATA_CHANGE_FLAG_SETTINGS_0);
    if (ImGui::DragScalar("Settings 2", ImGuiDataType_U32, &mMapActorData.settings[1], 1.0f, nullptr, nullptr, "%08X"))
        onDataChange(DATA_CHANGE_FLAG_SETTINGS_1);
    if (ImGui::DragScalar("Area", ImGuiDataType_U8, &mMapActorData.area))
        onDataChange(DATA_CHANGE_FLAG_AREA);
    if (ImGui::DragScalar("Layer", ImGuiDataType_U8, &mMapActorData.layer))
        onDataChange(DATA_CHANGE_FLAG_LAYER);
    if (ImGui::DragScalar("Movement ID", ImGuiDataType_U8, &mMapActorData.movement_id))
        onDataChange(DATA_CHANGE_FLAG_MOVEMENT_ID);
    if (ImGui::DragScalar("Link ID", ImGuiDataType_U8, &mMapActorData.link_id))
        onDataChange(DATA_CHANGE_FLAG_LINK_ID);
    if (ImGui::DragScalar("Init State", ImGuiDataType_U8, &mMapActorData.init_state))
        onDataChange(DATA_CHANGE_FLAG_INIT_STATE);
}
