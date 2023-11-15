#include <course/BgTexMgr.h>
#include <map_obj/ActorBlockBigBase.h>

#include <utility/aglDevTools.h>

#include <MainWindow.h>
#include <rio.h>

void ActorBlockBigBase::scheduleDraw()
{
    UnitID unit = getUnitID_();

    static_cast<MainWindow*>(rio::sRootTask)->getBgRenderer().drawUnit(
        { f32(mMapActorData.offset.x), -f32(mMapActorData.offset.y + 16), getZPos_() },
        unit,
        mMapActorData.layer
    );
    static_cast<MainWindow*>(rio::sRootTask)->getBgRenderer().drawUnit(
        { f32(mMapActorData.offset.x + 16), -f32(mMapActorData.offset.y + 16), getZPos_() },
        UnitID(s32(unit) + 1),
        mMapActorData.layer
    );
    static_cast<MainWindow*>(rio::sRootTask)->getBgRenderer().drawUnit(
        { f32(mMapActorData.offset.x), -f32(mMapActorData.offset.y + 32), getZPos_() },
        UnitID(s32(unit) + 16),
        mMapActorData.layer
    );
    static_cast<MainWindow*>(rio::sRootTask)->getBgRenderer().drawUnit(
        { f32(mMapActorData.offset.x + 16), -f32(mMapActorData.offset.y + 32), getZPos_() },
        UnitID(s32(unit) + 16 + 1),
        mMapActorData.layer
    );
}

void ActorBlockBigBase::drawXlu(const rio::lyr::DrawInfo& draw_info)
{
    BgTexMgr::ItemType type;

    if (mMapActorData.settings[1] >> 28 & 1)
        type = BgTexMgr::ITEM_ACORN;

    else
    {
        switch (mMapActorData.settings[1] & 0xF)
        {
        default:
            return;
        case 1:
            if (!setCoin_())
                return;
            type = BgTexMgr::ITEM_COIN;
            break;
        case 2:
        case 3:
            type = BgTexMgr::ITEM_FIRE_FLOWER;
            break;
        case 4:
            type = BgTexMgr::ITEM_PROPELLER;
            break;
        case 5:
            type = BgTexMgr::ITEM_PENGUIN;
            break;
        case 6:
            type = BgTexMgr::ITEM_MINI_MUSHROOM;
            break;
        case 7:
            type = BgTexMgr::ITEM_STAR;
            break;
        case 8:
            type = BgTexMgr::ITEM_COIN_STAR;
            break;
        case 9:
            type = BgTexMgr::ITEM_YOSHI_EGG;
            break;
        case 10:
            type = BgTexMgr::ITEM_COIN_10;
            break;
        case 11:
            type = BgTexMgr::ITEM_1UP;
            break;
        case 12:
            type = BgTexMgr::ITEM_VINE;
            break;
        case 13:
            type = BgTexMgr::ITEM_SPRING;
            break;
        case 14:
            type = BgTexMgr::ITEM_COIN_MUSHROOM;
            break;
        case 15:
            type = BgTexMgr::ITEM_ICE_FLOWER;
            break;
        }
    }

    agl::TextureSampler sampler(BgTexMgr::instance()->getItemsTexture());

    rio::Matrix34f model_mtx;
    model_mtx.makeST(
        { 32.0f, 32.0f, 1.0f },
        { f32(mMapActorData.offset.x + 16), -f32(mMapActorData.offset.y + 32), getZPos_() }
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
