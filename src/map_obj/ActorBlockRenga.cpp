#include <course/BgTexMgr.h>
#include <graphics/QuadRenderer.h>
#include <map_obj/ActorBlockRenga.h>

void ActorBlockRenga::updateType_(const MapActorData& map_actor_data)
{
    if (map_actor_data.settings[1] >> 28 & 1)
    {
        mUnitID = cUnitID_BrickBlockAcorn;
        mItemType = BgTexMgr::ITEM_MAX;
    }
    else
    {
        switch (map_actor_data.settings[1] & 0xF)
        {
        default:
            mUnitID = cUnitID_BrickBlock;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 1:
            mUnitID = cUnitID_BrickBlockCoin;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 2:
        case 3:
            mUnitID = cUnitID_BrickBlockFireFlower;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 4:
            mUnitID = cUnitID_BrickBlockPropeller;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 5:
            mUnitID = cUnitID_BrickBlockPenguin;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 6:
            mUnitID = cUnitID_BrickBlockMiniMushroom;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 7:
            mUnitID = cUnitID_BrickBlockStar;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 8:
            mUnitID = cUnitID_BrickBlock;
            mItemType = BgTexMgr::ITEM_COIN_STAR;
            break;
        case 9:
            mUnitID = cUnitID_BrickBlockYoshiEgg;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 10:
            mUnitID = cUnitID_BrickBlockCoin10;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 11:
            mUnitID = cUnitID_BrickBlock1UP;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 12:
            mUnitID = cUnitID_BrickBlockVine;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 13:
            mUnitID = cUnitID_BrickBlock;
            mItemType = BgTexMgr::ITEM_SPRING;
            break;
        case 14:
            mUnitID = cUnitID_BrickBlock;
            mItemType = BgTexMgr::ITEM_COIN_MUSHROOM;
            break;
        case 15:
            mUnitID = cUnitID_BrickBlockIceFlower;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        }
    }
}

void ActorBlockRenga::onDataChange(const MapActorData& map_actor_data, DataChangeFlag flag)
{
    BlockCoinBase::onDataChange(map_actor_data, flag);

    if (flag & DATA_CHANGE_FLAG_SETTINGS_1)
        updateType_(map_actor_data);
}

void ActorBlockRenga::drawXlu(const rio::lyr::DrawInfo& draw_info)
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
            .setCenter({ mPosition.x + 8, mPosition.y - 8, mPosition.z })
            .setSize({ 16.0f, 16.0f }),
        { 1.0f / s32(BgTexMgr::ITEM_MAX), 1.0f },
        0.0f,
        { s32(mItemType) - s32(BgTexMgr::ITEM_MAX) * 0.5f + 0.5f, 0.0f }
    );
}
