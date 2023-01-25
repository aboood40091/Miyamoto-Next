#include <item/LocationItem.h>

#include <gfx/rio_PrimitiveRenderer.h>

static const rio::Color4f sColor{
    114 / 255.f,
     42 / 255.f,
    188 / 255.f,
     70 / 255.f
};

LocationItem::LocationItem(Location& location)
    : mLocation(location)
{
}

void LocationItem::draw() const
{
    rio::PrimitiveRenderer::instance()->begin();
    {
        rio::Vector3f offs { f32(mLocation.offset.x), -f32(mLocation.offset.y + mLocation.size.y), 3600.0f };
        rio::Vector2f size { f32(mLocation.size.x), f32(mLocation.size.y) };

        rio::PrimitiveRenderer::instance()->drawQuad(
            rio::PrimitiveRenderer::QuadArg()
                .setColor(sColor, sColor)
                .setCornerAndSize(offs, size)
        );

        rio::PrimitiveRenderer::instance()->drawBox(
            rio::PrimitiveRenderer::QuadArg()
                .setColor(rio::Color4f::cBlack, rio::Color4f::cBlack)
                .setCornerAndSize(offs, size)
        );
    }
    rio::PrimitiveRenderer::instance()->end();
}
