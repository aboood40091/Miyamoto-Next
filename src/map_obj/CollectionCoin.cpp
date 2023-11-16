#include <course/CoinOrigin.h>
#include <graphics/ModelG3d.h>
#include <graphics/ModelResMgr.h>
#include <graphics/Renderer.h>
#include <map_obj/CollectionCoin.h>

static const std::string cResName = "star_coin";

CollectionCoin::CollectionCoin(MapActorData& map_actor_data)
    : MapActorItem(map_actor_data)
    , mpModel(nullptr)
{
    if (!ModelResMgr::instance()->loadResFile(cResName, cResName))
        return;

    const ModelResource* model_res = ModelResMgr::instance()->getResource(cResName);
    RIO_ASSERT(model_res);

    mpModel = Model::createG3d(
        *model_res,
        "star_coinA",
        1, 0, 0, 0, 0,
        Model::cBoundingMode_Disable
    );
}

CollectionCoin::~CollectionCoin()
{
    if (mpModel)
    {
        delete mpModel;
        ModelResMgr::instance()->destroyResFile(cResName);
    }
}

void CollectionCoin::drawOpa(const rio::lyr::DrawInfo& draw_info)
{
    if (mpModel)
        return;

    MapActorItem::drawOpa(draw_info);
}

void CollectionCoin::drawXlu(const rio::lyr::DrawInfo& draw_info)
{
    if (mpModel)
        return;

    MapActorItem::drawXlu(draw_info);
}

void CollectionCoin::scheduleDraw()
{
    if (mpModel == nullptr)
        return;

    rio::Matrix34f mtx;
    mtx.makeRT(
        { 0.0f, CoinOrigin::instance()->getCoinAngle(), 0.0f },
        { f32(mMapActorData.offset.x + 16), -f32(mMapActorData.offset.y + 16), getZPos_() }
    );

    mpModel->setMtxRT(mtx);
    mpModel->updateModel();

    Renderer::instance()->drawModel(mpModel, true, false);
}
