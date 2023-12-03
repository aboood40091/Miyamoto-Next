#include <graphics/QuadRenderer.h>
#include <item/MapActorItem.h>

static const rio::Color4f sColor{
      0 / 255.f,
     92 / 255.f,
    196 / 255.f,
    120 / 255.f
};

MapActorItem::MapActorItem(MapActorData& map_actor_data, u32 index)
    : ItemBase(ITEM_TYPE_MAP_ACTOR, index)
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
