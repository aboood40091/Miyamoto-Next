#include <course/CoinOrigin.h>
#include <graphics/ModelG3d.h>
#include <graphics/ModelResMgr.h>
#include <graphics/Renderer.h>
#include <map_obj/CollectionCoin.h>
#include <resource/ResMgr.h>

#include <MainWindow.h>

static const std::string cResName = "star_coin";

CollectionCoin::CollectionCoin(MapActorData& map_actor_data)
    : MapActorItem(map_actor_data)
    , mpModel(nullptr)
{
    static const std::string archive_path = MainWindow::getContentPath() + "/Common/actor/" + cResName + ".szs";
    const SharcArchiveRes* archive_res = ResMgr::instance()->loadArchiveRes(cResName, archive_path, true);
    if (archive_res == nullptr)
        return;

    const ModelResource* model_res = ModelResMgr::instance()->loadResFile(cResName, archive_res, cResName.c_str());
    RIO_ASSERT(model_res);

    mpModel = Model::createG3d(
        *model_res,
        "star_coinA",
        1, 0, 0, 0, 0,
        Model::cBoundingMode_Disable
    );

    update();
}

CollectionCoin::~CollectionCoin()
{
    if (mpModel)
    {
        delete mpModel;
        ModelResMgr::instance()->destroyResFile(cResName);
        ResMgr::instance()->destroyArchiveRes(cResName);
    }
}

void CollectionCoin::update()
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
}

void CollectionCoin::scheduleDraw()
{
    if (mpModel == nullptr)
        return;

    Renderer::instance()->drawModel(mpModel, true, false);
}
