#include <item/MapActorItem.h>

#include <gfx/rio_PrimitiveRenderer.h>

static const rio::Color4f sColor{
      0 / 255.f,
     92 / 255.f,
    196 / 255.f,
    120 / 255.f
};

MapActorItem::MapActorItem(MapActorData& map_actor_data)
    : mMapActorData(map_actor_data)
{
}

void MapActorItem::drawOpa(const rio::lyr::DrawInfo& draw_info)
{
    if (!drawBox_())
        return;

    rio::PrimitiveRenderer::instance()->begin();
    {
        rio::Vector3f offs { f32(mMapActorData.offset.x + 8), -f32(mMapActorData.offset.y + 8), getDefaultZPos(mMapActorData.layer) + 10 };
        rio::Vector2f size { 16.0f, 16.0f };

        rio::PrimitiveRenderer::instance()->drawBox(
            rio::PrimitiveRenderer::QuadArg()
                .setColor(rio::Color4f::cBlack, rio::Color4f::cBlack)
                .setCenter(offs)
                .setSize(size)
        );
    }
    rio::PrimitiveRenderer::instance()->end();
}

void MapActorItem::drawXlu(const rio::lyr::DrawInfo& draw_info)
{
    if (!drawBox_())
        return;

    rio::PrimitiveRenderer::instance()->begin();
    {
        rio::Vector3f offs { f32(mMapActorData.offset.x + 8), -f32(mMapActorData.offset.y + 8), getDefaultZPos(mMapActorData.layer) };
        rio::Vector2f size { 16.0f, 16.0f };

        rio::PrimitiveRenderer::instance()->drawQuad(
            rio::PrimitiveRenderer::QuadArg()
                .setColor(sColor, sColor)
                .setCenter(offs)
                .setSize(size)
        );
    }
    rio::PrimitiveRenderer::instance()->end();
}
