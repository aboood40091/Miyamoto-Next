#include <CourseView.h>
#include <Globals.h>
#include <course/BgRenderer.h>
#include <course/BgTexMgr.h>
#include <graphics/QuadRenderer.h>
#include <map_obj/ActorBlockBigBase.h>

void ActorBlockBigBase::updateItemType_(const MapActorData& map_actor_data)
{
    mItemType = BgTexMgr::ITEM_MAX;

    if (map_actor_data.settings[1] >> 28 & 1)
        mItemType = BgTexMgr::ITEM_ACORN;

    else
    {
        switch (map_actor_data.settings[1] & 0xF)
        {
        default:
            break;
        case 1:
            if (cSetCoin)
                mItemType = BgTexMgr::ITEM_COIN;
            break;
        case 2:
        case 3:
            mItemType = BgTexMgr::ITEM_FIRE_FLOWER;
            break;
        case 4:
            mItemType = BgTexMgr::ITEM_PROPELLER;
            break;
        case 5:
            mItemType = BgTexMgr::ITEM_PENGUIN;
            break;
        case 6:
            mItemType = BgTexMgr::ITEM_MINI_MUSHROOM;
            break;
        case 7:
            mItemType = BgTexMgr::ITEM_STAR;
            break;
        case 8:
            mItemType = BgTexMgr::ITEM_COIN_STAR;
            break;
        case 9:
            mItemType = BgTexMgr::ITEM_YOSHI_EGG;
            break;
        case 10:
            mItemType = BgTexMgr::ITEM_COIN_10;
            break;
        case 11:
            mItemType = BgTexMgr::ITEM_1UP;
            break;
        case 12:
            mItemType = BgTexMgr::ITEM_VINE;
            break;
        case 13:
            mItemType = BgTexMgr::ITEM_SPRING;
            break;
        case 14:
            mItemType = BgTexMgr::ITEM_COIN_MUSHROOM;
            break;
        case 15:
            mItemType = BgTexMgr::ITEM_ICE_FLOWER;
            break;
        }
    }
}

void ActorBlockBigBase::onDataChange(const MapActorData& map_actor_data, DataChangeFlag flag)
{
    if (flag & DATA_CHANGE_FLAG_OFFSET)
        updatePositionXY_(map_actor_data);

    if (flag & DATA_CHANGE_FLAG_LAYER)
        updatePositionZ_(map_actor_data);

    if (flag & DATA_CHANGE_FLAG_SETTINGS_1)
        updateItemType_(map_actor_data);
}

void ActorBlockBigBase::scheduleDraw()
{
    if (drawBox())
        return;

    const MapActorData& map_actor_data = CourseView::instance()->getCourseDataFile()->getMapActorData()[mItemID.getIndex()];

    BgRenderer::instance()->drawUnit(
        mItemID,
        mPosition,
        cUnitID,
        map_actor_data.layer
    );
    BgRenderer::instance()->drawUnit(
        mItemID,
        { mPosition.x + 16, mPosition.y, mPosition.z },
        UnitID(s32(cUnitID) + 1),
        map_actor_data.layer
    );
    BgRenderer::instance()->drawUnit(
        mItemID,
        { mPosition.x, mPosition.y - 16, mPosition.z },
        UnitID(s32(cUnitID) + 16),
        map_actor_data.layer
    );
    BgRenderer::instance()->drawUnit(
        mItemID,
        { mPosition.x + 16, mPosition.y - 16, mPosition.z },
        UnitID(s32(cUnitID) + 16 + 1),
        map_actor_data.layer
    );
}

void ActorBlockBigBase::drawXlu(const rio::lyr::DrawInfo& draw_info)
{
    if (drawBox())
        return MapActorItem::drawXlu(draw_info);

    if (mItemType == BgTexMgr::ITEM_MAX)
        return;

    const rio::Texture2D& texture = BgTexMgr::instance()->getItemsTexture();

    QuadRenderer::instance()->drawQuad(
        QuadRenderer::TextureArg(&texture)
            .setItemID(mItemID)
            .setSelection(mIsSelected)
            .setCenter({ mPosition.x + 16, mPosition.y - 16, mPosition.z })
            .setSize({ Globals::getBigItemScale(), Globals::getBigItemScale() }),
        { 1.0f / s32(BgTexMgr::ITEM_MAX), 1.0f },
        0.0f,
        { s32(mItemType) - s32(BgTexMgr::ITEM_MAX) * 0.5f + 0.5f, 0.0f }
    );
}
