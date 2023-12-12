#include <Globals.h>
#include <graphics/BasicModel.h>
#include <graphics/ModelResMgr.h>
#include <graphics/Renderer.h>
#include <enemy/Kuribo.h>
#include <resource/ResMgr.h>

static const std::string cResName[2] = {
    "kuribo",
    "kakibo"
};

Kuribo::Kuribo(const MapActorData& map_actor_data, u32 index)
    : MapActorItem(map_actor_data, index)
    , cIsKakibo(map_actor_data.id == 595)
    , mpModel(nullptr)
    , mIsLayer2(false)
{
    static const std::string cArchivePath[2] = {
        Globals::getContentPath() + "/Common/actor/" + cResName[0] + ".szs",
        Globals::getContentPath() + "/Common/actor/" + cResName[1] + ".szs"
    };

    const std::string& res_name = cResName[cIsKakibo];
    const std::string& archive_path = cArchivePath[cIsKakibo];

    const SharcArchiveRes* archive_res = ResMgr::instance()->loadArchiveRes(res_name, archive_path, true);
    if (archive_res == nullptr)
        return;

    const ModelResource* model_res = ModelResMgr::instance()->loadResFile(res_name, archive_res, res_name.c_str());
    RIO_ASSERT(model_res);

    const char* model_name = res_name.c_str();

    mpModel = BasicModel::create(
        const_cast<ModelResource*>(model_res),
        model_name,
        1, 1, 0, 0, 0,
        Model::cBoundingMode_Disable
    );

    mpModel->getSklAnim(0)->play(model_res, "walk");
    mpModel->getSklAnim(0)->getFrameCtrl().set(FrameCtrl::cMode_Repeat, 1.0f, 0.0f);

    mpModel->getTexAnim(0)->play(model_res, "walk");

    mIsLayer2 = map_actor_data.settings[0] >> 16 & 1;

    updatePositionXY_(map_actor_data);
    updatePositionZ_();

    setModelMtxRT_();

    setModelItemID_();
}

Kuribo::~Kuribo()
{
    if (mpModel)
    {
        BasicModel::destroy(mpModel);

        const std::string& res_name = cResName[cIsKakibo];

        ModelResMgr::instance()->destroyResFile(res_name);
        ResMgr::instance()->destroyArchiveRes(res_name);
    }
}

void Kuribo::setModelItemID_()
{
    if (mpModel)
        mpModel->getModel()->setItemID(mItemID);
}

void Kuribo::setModelSelection_()
{
    if (mpModel)
        mpModel->getModel()->setSelection(mIsSelected);
}

namespace {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winline"

struct BaseRotMtx
{
    BaseRotMtx(f32 x, f32 y, f32 z)
    {
        mtx.makeR({ x, y, z });
    }

    BaseRotMtx(const rio::Vector3f& rot)
    {
        mtx.makeR(rot);
    }

    rio::Matrix34f mtx;
};

#pragma GCC diagnostic pop

static BaseRotMtx sMtx(0.0f, rio::Mathf::deg2rad(315), 0.0f);

}

void Kuribo::setModelMtxRT_()
{
    if (mpModel == nullptr)
        return;

    rio::Matrix34f& mtx = sMtx.mtx;
    mtx.setTranslationWorld(static_cast<const rio::Vector3f&>(mPosition));

    mpModel->getModel()->setMtxRT(mtx);
}

void Kuribo::onDataChange(const MapActorData& map_actor_data, DataChangeFlag flag)
{
    bool position_changed = false;

    if (flag & DATA_CHANGE_FLAG_SETTINGS_0)
    {
        bool is_layer2 = map_actor_data.settings[0] >> 16 & 1;
        if (mIsLayer2 != is_layer2)
        {
            mIsLayer2 = is_layer2;
            updatePositionZ_();
            position_changed = true;
        }
    }

    if (flag & DATA_CHANGE_FLAG_OFFSET)
    {
        updatePositionXY_(map_actor_data);
        position_changed = true;
    }

    if (position_changed)
        setModelMtxRT_();
}

void Kuribo::onSceneUpdate()
{
    if (mpModel == nullptr)
        return;

    mpModel->updateAnimations();
    mpModel->updateModel();
}

void Kuribo::scheduleDraw()
{
    if (drawBox())
        return;

    Renderer::instance()->drawModel(*mpModel);
}
