#include <CourseView.h>
#include <graphics/QuadRenderer.h>
#include <item/AreaItem.h>

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

AreaItem::AreaItem(u32 index)
    : mIndex(index)
{
}

void AreaItem::drawOpa()
{
    const AreaData& area_data = CourseView::instance()->getCourseDataFile()->getAreaData()[mIndex];

    rio::Vector3f offs { f32(area_data.offset.x), -f32(area_data.offset.y + area_data.size.y), getZPos_() + 10 };
    rio::Vector2f size { f32(area_data.size.x), f32(area_data.size.y) };

    QuadRenderer::instance()->drawBox(
        QuadRenderer::Arg(sColor)
            .setCornerAndSize(offs, size)
    );
}

void AreaItem::drawXlu()
{
    const AreaData& area_data = CourseView::instance()->getCourseDataFile()->getAreaData()[mIndex];

    if (!(area_data.mask & 0x20))
        return;

    rio::Vector3f offs { f32(area_data.offset.x), -f32(area_data.offset.y + area_data.size.y), getZPos_() };
    rio::Vector2f size { f32(area_data.size.x), f32(area_data.size.y) };

    QuadRenderer::instance()->drawQuad(
        QuadRenderer::Arg(sMaskColor)
            .setCornerAndSize(offs, size)
    );
}
