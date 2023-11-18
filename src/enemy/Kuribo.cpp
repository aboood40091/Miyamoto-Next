#include <graphics/BasicModel.h>
#include <graphics/ModelResMgr.h>
#include <graphics/Renderer.h>
#include <enemy/Kuribo.h>
#include <resource/ResMgr.h>

#include <MainWindow.h>

static const std::string cResName[2] = {
    "kuribo",
    "kakibo"
};

Kuribo::Kuribo(MapActorData& map_actor_data)
    : MapActorItem(map_actor_data)
    , mIsKakibo(map_actor_data.id == 595)
    , mpModel(nullptr)
    , mpTexAnim(nullptr)
{
    static const std::string cArchivePath[2] = {
        MainWindow::getContentPath() + "/Common/actor/" + cResName[0] + ".szs",
        MainWindow::getContentPath() + "/Common/actor/" + cResName[1] + ".szs"
    };

    const std::string& res_name = cResName[mIsKakibo];
    const std::string& archive_path = cArchivePath[mIsKakibo];

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

    mpTexAnim = mpModel->getTexAnim(0);
    mpTexAnim->play(model_res, "walk");

    update();
}

Kuribo::~Kuribo()
{
    if (mpModel)
    {
        delete mpModel->getModel();
        delete mpModel;

        const std::string& res_name = cResName[mIsKakibo];

        ModelResMgr::instance()->destroyResFile(res_name);
        ResMgr::instance()->destroyArchiveRes(res_name);
    }
}

void Kuribo::update()
{
    if (mpModel == nullptr)
        return;

    const rio::Vector3f pos { f32(mMapActorData.offset.x + 8), -f32(mMapActorData.offset.y + 16), getZPos_() };
    static const rio::Vector3f rot { 0.0f, rio::Mathf::deg2rad(315), 0.0f };

    rio::Matrix34f mtx;
    mtx.makeRT(rot, pos);

    mpModel->getModel()->setMtxRT(mtx);
  //mpModel->getModel()->setScale({ 1.0f, 1.0f, 1.0f });

    mpModel->updateAnimations();
    mpModel->updateModel();
}

void Kuribo::scheduleDraw()
{
    if (mpModel == nullptr)
        return;

    Renderer::instance()->drawModel(*mpModel);
}
