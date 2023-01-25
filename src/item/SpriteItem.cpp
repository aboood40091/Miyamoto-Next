#include <item/SpriteItem.h>

#include <gfx/rio_PrimitiveRenderer.h>

static const rio::Color4f sColor{
      0 / 255.f,
     92 / 255.f,
    196 / 255.f,
    120 / 255.f
};

SpriteItem::SpriteItem(Sprite& sprite)
    : mSprite(sprite)
{
}

void SpriteItem::draw() const
{
    rio::PrimitiveRenderer::instance()->begin();
    {
        f32 z = (mSprite.layer == LAYER_1) ? 2200.0f : -2500.0f; // Only layer 1 and 2

        rio::Vector3f offs { f32(mSprite.offset.x + 8), -f32(mSprite.offset.y + 8), z };
        rio::Vector2f size { 16.0f, 16.0f };

        rio::PrimitiveRenderer::instance()->drawQuad(
            rio::PrimitiveRenderer::QuadArg()
                .setColor(sColor, sColor)
                .setCenter(offs)
                .setSize(size)
        );

        rio::PrimitiveRenderer::instance()->drawBox(
            rio::PrimitiveRenderer::QuadArg()
                .setColor(rio::Color4f::cBlack, rio::Color4f::cBlack)
                .setCenter(offs)
                .setSize(size)
        );
    }
    rio::PrimitiveRenderer::instance()->end();
}
