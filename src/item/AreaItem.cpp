#include <item/AreaItem.h>

#include <gfx/rio_PrimitiveRenderer.h>

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

AreaItem::AreaItem(AreaData& area)
    : mAreaData(area)
{
}

void AreaItem::drawOpa()
{
    rio::PrimitiveRenderer::instance()->begin();
    {
        rio::Vector3f offs { f32(mAreaData.offset.x), -f32(mAreaData.offset.y + mAreaData.size.y), getZPos_() + 10 };
        rio::Vector2f size { f32(mAreaData.size.x), f32(mAreaData.size.y) };

        rio::PrimitiveRenderer::instance()->drawBox(
            rio::PrimitiveRenderer::QuadArg()
                .setColor(sColor, sColor)
                .setCornerAndSize(offs, size)
        );
    }
    rio::PrimitiveRenderer::instance()->end();
}

void AreaItem::drawXlu()
{
    if (!(mAreaData.mask & 0x20))
        return;

    rio::PrimitiveRenderer::instance()->begin();
    {
        rio::Vector3f offs { f32(mAreaData.offset.x), -f32(mAreaData.offset.y + mAreaData.size.y), getZPos_() };
        rio::Vector2f size { f32(mAreaData.size.x), f32(mAreaData.size.y) };

        rio::PrimitiveRenderer::instance()->drawQuad(
            rio::PrimitiveRenderer::QuadArg()
                .setColor(sMaskColor, sMaskColor)
                .setCornerAndSize(offs, size)
        );
    }
    rio::PrimitiveRenderer::instance()->end();
}
