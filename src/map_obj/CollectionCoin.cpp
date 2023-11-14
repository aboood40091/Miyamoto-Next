#include <course/CoinOrigin.h>
#include <graphics/ModelG3d.h>
#include <graphics/ModelResource.h>
#include <graphics/Renderer.h>
#include <map_obj/CollectionCoin.h>

#include <MainWindow.h>
#include <rio.h>

class CollectionCoinResMgr
{
public:
    static const ModelResource* initialize();
    static void destroy();

private:
    static bool             sIsInitialized;
  //static void*            spArchive;
    static SharcArchiveRes  sArchiveRes;
    static ModelResource    sModelResource;
    static s32              sRefCounter;
};

bool            CollectionCoinResMgr::sIsInitialized = false;
//void*         CollectionCoinResMgr::spArchive = nullptr;
SharcArchiveRes CollectionCoinResMgr::sArchiveRes;
ModelResource   CollectionCoinResMgr::sModelResource;
s32             CollectionCoinResMgr::sRefCounter = 0;

const ModelResource* CollectionCoinResMgr::initialize()
{
    if (!sIsInitialized)
    {
        MainWindow* window = static_cast<MainWindow*>(rio::sRootTask);
        const std::span<u8>& res = window->getCourseData().getRes("star_coin");
        RIO_ASSERT(res.data() && res.size());

        {
            [[maybe_unused]] bool success = sArchiveRes.prepareArchive(res.data());
            RIO_ASSERT(success);
        }

        sModelResource.load(&sArchiveRes, "star_coin");
        sIsInitialized = true;
    }
    sRefCounter++;
    return &sModelResource;
}

void CollectionCoinResMgr::destroy()
{
    if (!sIsInitialized || sRefCounter == 0 || --sRefCounter > 0)
        return;

    sModelResource.destroy();
    sArchiveRes.destroy();

    sIsInitialized = false;
}

CollectionCoin::CollectionCoin(MapActorData& map_actor_data)
    : MapActorItem(map_actor_data)
    , mpModel(nullptr)
{
    const ModelResource* model_res = CollectionCoinResMgr::initialize();
    if (!model_res)
        return;

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
        CollectionCoinResMgr::destroy();
    }
}

void CollectionCoin::drawOpa()
{
    if (mpModel)
        return;

    MapActorItem::drawOpa();
}

void CollectionCoin::drawXlu()
{
    if (mpModel)
        return;

    MapActorItem::drawXlu();
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
