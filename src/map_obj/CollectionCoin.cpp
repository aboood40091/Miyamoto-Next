#include <Globals.h>
#include <course/CoinOrigin.h>
#include <graphics/ModelG3d.h>
#include <graphics/ModelResMgr.h>
#include <graphics/Renderer.h>
#include <map_obj/CollectionCoin.h>
#include <resource/ResMgr.h>

static const std::string cResName = "star_coin";

CollectionCoin::CollectionCoin(const MapActorData& map_actor_data, u32 index)
    : MapActorItem(map_actor_data, index)
    , mpModel(nullptr)
{
    static const std::string archive_path = Globals::getContentPath() + "/Common/actor/" + cResName + ".szs";
    const SharcArchiveRes* archive_res = ResMgr::instance()->loadArchiveRes(cResName, archive_path, true);
    if (archive_res == nullptr)
        return;

    const ModelResource* model_res = ModelResMgr::instance()->loadResFile(cResName, archive_res, cResName.c_str());
    RIO_ASSERT(model_res);

    mpModel = Model::createG3d(
        *model_res,
        "star_coinA",
        0, 0, 0, 0, 0,
        Model::cBoundingMode_Disable
    );

    updatePositionXY_(map_actor_data);
    updatePositionZ_(map_actor_data);

    setModelItemID_();
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

void CollectionCoin::setModelItemID_()
{
    if (mpModel)
        mpModel->setItemID(mItemID);
}

void CollectionCoin::setModelSelection_()
{
    if (mpModel)
        mpModel->setSelection(mIsSelected);
}

void CollectionCoin::onDataChange(const MapActorData& map_actor_data, DataChangeFlag flag)
{
    if (flag & DATA_CHANGE_FLAG_OFFSET)
        updatePositionXY_(map_actor_data);

    if ((flag & DATA_CHANGE_FLAG_LAYER) || (flag & DATA_CHANGE_FLAG_SETTINGS_0))
        updatePositionZ_(map_actor_data);
}

void CollectionCoin::onSceneUpdate()
{
    if (mpModel == nullptr)
        return;

    rio::Matrix34f mtx;
    mtx.makeRT(
        { 0.0f, CoinOrigin::instance()->getCoinAngle(), 0.0f },
        static_cast<const rio::Vector3f&>(mPosition)
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
