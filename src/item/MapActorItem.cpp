#include <CourseView.h>
#include <action/ActionItemDataChange.h>
#include <action/ActionMgr.h>
#include <actor/ActorCreateMgr.h>
#include <graphics/QuadRenderer.h>
#include <item/MapActorItem.h>

#include <imgui.h>

static const rio::Color4f sColor{
      0 / 255.f,
     92 / 255.f,
    196 / 255.f,
    120 / 255.f
};

MapActorItem::MapActorItem(const MapActorData& map_actor_data, u32 index)
    : ItemBase(ITEM_TYPE_MAP_ACTOR, index, map_actor_data.offset.x, map_actor_data.offset.y)
{
}

void MapActorItem::move(s16 dx, s16 dy, bool commit)
{
    MapActorData& map_actor_data = CourseView::instance()->getCourseDataFile()->getMapActorData()[mItemID.getIndex()];

    map_actor_data.offset.x = mBasePosition.x + dx;
    map_actor_data.offset.y = mBasePosition.y + dy;
    if (commit)
    {
        mBasePosition.x = map_actor_data.offset.x;
        mBasePosition.y = map_actor_data.offset.y;
    }
    onDataChange(map_actor_data, DATA_CHANGE_FLAG_OFFSET);
}

bool MapActorItem::drawBox() const
{
    return drawBox_() || !*CourseView::instance()->getActorGraphicsEnable();
}

void MapActorItem::drawOpa(const rio::lyr::DrawInfo& draw_info)
{
    if (!drawBox())
        return;

    const MapActorData& map_actor_data = CourseView::instance()->getCourseDataFile()->getMapActorData()[mItemID.getIndex()];

    rio::Vector3f offs { f32(map_actor_data.offset.x + 8), -f32(map_actor_data.offset.y + 8), getDefaultZPos(map_actor_data.layer) + 10 };
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
    if (!drawBox())
        return;

    const MapActorData& map_actor_data = CourseView::instance()->getCourseDataFile()->getMapActorData()[mItemID.getIndex()];

    rio::Vector3f offs { f32(map_actor_data.offset.x + 8), -f32(map_actor_data.offset.y + 8), getDefaultZPos(map_actor_data.layer) };
    rio::Vector2f size { 16.0f, 16.0f };

    QuadRenderer::instance()->drawQuad(
        QuadRenderer::Arg(sColor)
            .setItemID(mItemID)
            .setSelection(mIsSelected)
            .setCenter(offs)
            .setSize(size)
    );
}

void MapActorItem::onSelectionChange_()
{
    if (mIsSelected)
        mSelectionData = CourseView::instance()->getCourseDataFile()->getMapActorData()[mItemID.getIndex()];
}

void MapActorItem::drawSelectionUI()
{
    const MapActorData& map_actor_data = CourseView::instance()->getCourseDataFile()->getMapActorData()[mItemID.getIndex()];

    const std::u8string& name = ActorCreateMgr::instance()->getName(map_actor_data.id);
    if (name.empty())
        ImGui::Text("Map Actor %d", map_actor_data.id);
    else
        ImGui::Text("Map Actor %d: %s", map_actor_data.id, (char*)(name.c_str()));
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

        if (mSelectionData.event_id != map_actor_data.event_id)
            data_change_flag |= DATA_CHANGE_FLAG_EVENT_ID;

        if (mSelectionData.settings[0] != map_actor_data.settings[0])
            data_change_flag |= DATA_CHANGE_FLAG_SETTINGS_0;

        if (mSelectionData.settings[1] != map_actor_data.settings[1])
            data_change_flag |= DATA_CHANGE_FLAG_SETTINGS_1;

        if (mSelectionData.area != map_actor_data.area)
            data_change_flag |= DATA_CHANGE_FLAG_AREA;

        if (mSelectionData.layer != map_actor_data.layer)
            data_change_flag |= DATA_CHANGE_FLAG_LAYER;

        if (mSelectionData.movement_id != map_actor_data.movement_id)
            data_change_flag |= DATA_CHANGE_FLAG_MOVEMENT_ID;

        if (mSelectionData.link_id != map_actor_data.link_id)
            data_change_flag |= DATA_CHANGE_FLAG_LINK_ID;

        if (mSelectionData.init_state != map_actor_data.init_state)
            data_change_flag |= DATA_CHANGE_FLAG_INIT_STATE;

        if (data_change_flag)
        {
            mSelectionData.id = map_actor_data.id; // Copy over stuff not modified by the selection ui.
            mSelectionData.offset = map_actor_data.offset; // Copy over stuff not modified by the selection ui.

            ActionItemDataChange::Context context {
                mItemID,
                std::static_pointer_cast<const void>(
                    std::make_shared<const MapActorData>(map_actor_data)
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
        mSelectionData = map_actor_data;
}
