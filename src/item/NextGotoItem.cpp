#include <item/NextGotoItem.h>

#include <gfx/rio_PrimitiveRenderer.h>

static const rio::Color4f sColor{
    190 / 255.f,
      0 / 255.f,
      0 / 255.f,
    120 / 255.f
};

NextGotoItem::NextGotoItem(NextGoto& next_goto)
    : mNextGoto(next_goto)
{
}

void NextGotoItem::draw() const
{
    rio::PrimitiveRenderer::instance()->begin();
    {
        rio::Vector3f offs { f32(mNextGoto.offset.x + 8), -f32(mNextGoto.offset.y + 8), 3000.0f };
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
