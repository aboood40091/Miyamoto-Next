#include <graphics/QuadRenderer.h>
#include <item/NextGotoItem.h>

static const rio::Color4f sColor{
    190 / 255.f,
      0 / 255.f,
      0 / 255.f,
    120 / 255.f
};

NextGotoItem::NextGotoItem(NextGoto& next_goto, u32 index)
    : ItemBase(ITEM_TYPE_NEXT_GOTO, index)
    , mNextGoto(next_goto)
{
}

void NextGotoItem::drawOpa()
{
    rio::Vector3f offs { f32(mNextGoto.offset.x + 8), -f32(mNextGoto.offset.y + 8), getZPos_() + 10 };
    rio::Vector2f size { 16.0f, 16.0f };

    QuadRenderer::instance()->drawBox(
        QuadRenderer::Arg(rio::Color4f::cBlack)
            .setItemID(mItemID)
            .setSelection(mIsSelected)
            .setCenter(offs)
            .setSize(size)
    );
}

void NextGotoItem::drawXlu()
{
    rio::Vector3f offs { f32(mNextGoto.offset.x + 8), -f32(mNextGoto.offset.y + 8), getZPos_() };
    rio::Vector2f size { 16.0f, 16.0f };

    QuadRenderer::instance()->drawQuad(
        QuadRenderer::Arg(sColor)
            .setItemID(mItemID)
            .setSelection(mIsSelected)
            .setCenter(offs)
            .setSize(size)
    );
}
