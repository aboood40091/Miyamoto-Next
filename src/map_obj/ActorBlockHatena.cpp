#include <course/BgTexMgr.h>
#include <map_obj/ActorBlockHatena.h>

#include <gfx/lyr/rio_Layer.h>
#include <utility/aglDevTools.h>

void ActorBlockHatena::updateType_()
{
    if (mMapActorData.settings[1] >> 28 & 1)
    {
        mUnitID = cUnitID_QBlockAcorn;
        mItemType = BgTexMgr::ITEM_MAX;
    }
    else
    {
        switch (mMapActorData.settings[1] & 0xF)
        {
        default:
            mUnitID = cUnitID_QBlock;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 2:
        case 3:
            mUnitID = cUnitID_QBlockFireFlower;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 4:
            mUnitID = cUnitID_QBlockPropeller;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 5:
            mUnitID = cUnitID_QBlockPenguin;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 6:
            mUnitID = cUnitID_QBlockMiniMushroom;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 7:
            mUnitID = cUnitID_QBlockStar;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 8:
            mUnitID = cUnitID_QBlockCoinStar;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 9:
            mUnitID = cUnitID_QBlockYoshiEgg;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 10:
            mUnitID = cUnitID_QBlock;
            mItemType = BgTexMgr::ITEM_COIN_10;
            break;
        case 11:
            mUnitID = cUnitID_QBlock;
            mItemType = BgTexMgr::ITEM_1UP;
            break;
        case 12:
            mUnitID = cUnitID_QBlockVine;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 13:
            mUnitID = cUnitID_QBlockSpring;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        case 14:
            mUnitID = cUnitID_QBlock;
            mItemType = BgTexMgr::ITEM_COIN_MUSHROOM;
            break;
        case 15:
            mUnitID = cUnitID_QBlockIceFlower;
            mItemType = BgTexMgr::ITEM_MAX;
            break;
        }
    }
}

void ActorBlockHatena::onDataChange(DataChangeFlag flag)
{
    BlockCoinBase::onDataChange(flag);

    if (flag & DATA_CHANGE_FLAG_SETTINGS_1)
        updateType_();
}

void ActorBlockHatena::drawXlu(const rio::lyr::DrawInfo& draw_info)
{
    if (mItemType == BgTexMgr::ITEM_MAX)
        return;

    agl::TextureSampler sampler(BgTexMgr::instance()->getItemsTexture());

    rio::Matrix34f model_mtx;
    model_mtx.makeST(
        { 16.0f, 16.0f, 1.0f },
        { mPosition.x + 8, mPosition.y - 8, mPosition.z }
    );

    rio::Matrix34f view_mtx;
    draw_info.parent_layer.camera()->getMatrix(&view_mtx);

    rio::Matrix34f mv_mtx;
    mv_mtx.setMul(view_mtx, model_mtx);

    const rio::Matrix44f& proj_mtx = static_cast<const rio::Matrix44f&>(draw_info.parent_layer.projection()->getMatrix());;

    agl::utl::DevTools::drawTextureTexCoord(
        sampler, mv_mtx, proj_mtx,
        { 1.0f / s32(BgTexMgr::ITEM_MAX), 1.0f },
        0.0f,
        { s32(mItemType) - s32(BgTexMgr::ITEM_MAX) * 0.5f + 0.5f, 0.0f },
        agl::cShaderMode_Invalid
    );
}
