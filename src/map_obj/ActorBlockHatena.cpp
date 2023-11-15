#include <course/BgTexMgr.h>
#include <map_obj/ActorBlockHatena.h>

#include <gfx/lyr/rio_Layer.h>
#include <utility/aglDevTools.h>

UnitID ActorBlockHatena::getUnitID_() const
{
    if (mMapActorData.settings[1] >> 28 & 1)
        return cUnitID_QBlockAcorn;

    switch (mMapActorData.settings[1] & 0xF)
    {
    default:
        return cUnitID_QBlock;
    case 2:
    case 3:
        return cUnitID_QBlockFireFlower;
    case 4:
        return cUnitID_QBlockPropeller;
    case 5:
        return cUnitID_QBlockPenguin;
    case 6:
        return cUnitID_QBlockMiniMushroom;
    case 7:
        return cUnitID_QBlockStar;
    case 8:
        return cUnitID_QBlockCoinStar;
    case 9:
        return cUnitID_QBlockYoshiEgg;
    case 12:
        return cUnitID_QBlockVine;
    case 13:
        return cUnitID_QBlockSpring;
    case 15:
        return cUnitID_QBlockIceFlower;
    }
}

void ActorBlockHatena::drawXlu(const rio::lyr::DrawInfo& draw_info)
{
    BgTexMgr::ItemType type;

    switch (mMapActorData.settings[1] & 0xF)
    {
    default:
        return;
    case 10:
        type = BgTexMgr::ITEM_COIN_10;
        break;
    case 11:
        type = BgTexMgr::ITEM_1UP;
        break;
    case 14:
        type = BgTexMgr::ITEM_COIN_MUSHROOM;
        break;
    }

    agl::TextureSampler sampler(BgTexMgr::instance()->getItemsTexture());

    rio::Matrix34f model_mtx;
    model_mtx.makeST(
        { 16.0f, 16.0f, 1.0f },
        { f32(mMapActorData.offset.x + 8), -f32(mMapActorData.offset.y + 8), getZPos_() }
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
        { s32(type) - s32(BgTexMgr::ITEM_MAX) * 0.5f + 0.5f, 0.0f },
        agl::cShaderMode_Invalid
    );
}
