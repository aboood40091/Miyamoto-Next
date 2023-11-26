#include <course/BgRenderer.h>
#include <course/BgTexMgr.h>
#include <map_obj/ActorBlockBigBase.h>

#include <utility/aglDevTools.h>

#include <MainWindow.h>

void ActorBlockBigBase::updateItemType_()
{
    mItemType = BgTexMgr::ITEM_MAX;

    if (mMapActorData.settings[1] >> 28 & 1)
        mItemType = BgTexMgr::ITEM_ACORN;

    else
    {
        switch (mMapActorData.settings[1] & 0xF)
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

void ActorBlockBigBase::onDataChange(DataChangeFlag flag)
{
    if (flag & DATA_CHANGE_FLAG_OFFSET)
        updatePositionXY_();

    if (flag & DATA_CHANGE_FLAG_LAYER)
        updatePositionZ_();

    if (flag & DATA_CHANGE_FLAG_SETTINGS_1)
        updateItemType_();
}

void ActorBlockBigBase::scheduleDraw()
{
    BgRenderer::instance()->drawUnit(
        mPosition,
        cUnitID,
        mMapActorData.layer
    );
    BgRenderer::instance()->drawUnit(
        { mPosition.x + 16, mPosition.y, mPosition.z },
        UnitID(s32(cUnitID) + 1),
        mMapActorData.layer
    );
    BgRenderer::instance()->drawUnit(
        { mPosition.x, mPosition.y - 16, mPosition.z },
        UnitID(s32(cUnitID) + 16),
        mMapActorData.layer
    );
    BgRenderer::instance()->drawUnit(
        { mPosition.x + 16, mPosition.y - 16, mPosition.z },
        UnitID(s32(cUnitID) + 16 + 1),
        mMapActorData.layer
    );
}

void ActorBlockBigBase::drawXlu(const rio::lyr::DrawInfo& draw_info)
{
    if (mItemType == BgTexMgr::ITEM_MAX)
        return;

    agl::TextureSampler sampler(BgTexMgr::instance()->getItemsTexture());

    rio::Matrix34f model_mtx;
    model_mtx.makeST(
        { MainWindow::getBigItemScale(), MainWindow::getBigItemScale(), 1.0f },
        { mPosition.x + 16, mPosition.y - 16, mPosition.z }
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
