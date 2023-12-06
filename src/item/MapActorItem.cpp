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

    ImGui::DragScalarN("Events", ImGuiDataType_U8, &mSelectionData.event_id, 2);
    ImGui::DragScalarN("Settings", ImGuiDataType_U32, &mSelectionData.settings, 2, 1.0f, nullptr, nullptr, "%08X");
    ImGui::DragScalar("Area", ImGuiDataType_U8, &mSelectionData.area);
    ImGui::DragScalar("Layer", ImGuiDataType_U8, &mSelectionData.layer);
    ImGui::DragScalar("Movement ID", ImGuiDataType_U8, &mSelectionData.movement_id);
    ImGui::DragScalar("Link ID", ImGuiDataType_U8, &mSelectionData.link_id);
    ImGui::DragScalar("Init State", ImGuiDataType_U8, &mSelectionData.init_state);

    ImGui::Separator();

    if (ImGui::Button("Apply"))
    {
        const bool anything_modified =
            mSelectionData.event_id     != mMapActorData.event_id ||
            mSelectionData.settings[0]  != mMapActorData.settings[0] ||
            mSelectionData.settings[1]  != mMapActorData.settings[1] ||
            mSelectionData.area         != mMapActorData.area ||
            mSelectionData.layer        != mMapActorData.layer ||
            mSelectionData.movement_id  != mMapActorData.movement_id ||
            mSelectionData.link_id      != mMapActorData.link_id ||
            mSelectionData.init_state   != mMapActorData.init_state;

        if (anything_modified)
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
                )
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
