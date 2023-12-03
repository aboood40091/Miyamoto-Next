#include <graphics/QuadRenderer.h>
#include <item/LocationItem.h>

static const rio::Color4f sColor{
    114 / 255.f,
     42 / 255.f,
    188 / 255.f,
     70 / 255.f
};

LocationItem::LocationItem(Location& location, u32 index)
    : ItemBase(ITEM_TYPE_LOCATION, index)
    , mLocation(location)
{
}

void LocationItem::drawOpa()
{
    rio::Vector3f offs { f32(mLocation.offset.x), -f32(mLocation.offset.y + mLocation.size.y), getZPos_() + 10 };
    rio::Vector2f size { f32(mLocation.size.x), f32(mLocation.size.y) };

    QuadRenderer::instance()->drawBox(
        QuadRenderer::Arg(rio::Color4f::cBlack)
            .setItemID(mItemID)
            .setSelection(mIsSelected)
            .setCornerAndSize(offs, size)
    );
}

void LocationItem::drawXlu()
{
    rio::Vector3f offs { f32(mLocation.offset.x), -f32(mLocation.offset.y + mLocation.size.y), getZPos_() };
    rio::Vector2f size { f32(mLocation.size.x), f32(mLocation.size.y) };

    QuadRenderer::instance()->drawQuad(
        QuadRenderer::Arg(sColor)
            .setItemID(mItemID)
            .setSelection(mIsSelected)
            .setCornerAndSize(offs, size)
    );
}
