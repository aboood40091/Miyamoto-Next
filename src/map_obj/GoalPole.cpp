#include <graphics/BasicModel.h>
#include <graphics/ModelResMgr.h>
#include <graphics/Renderer.h>
#include <map_obj/GoalPole.h>
#include <resource/ResMgr.h>

#include <MainWindow.h>

static const std::string cResNameNormal = "goal_set";
static const std::string cResNameKaiga = "goal_set_kaiga";
static const std::string cResNameRDash = "R_goal_set";
static const std::string cResNameKaigaRDash = "R_goal_set_kaiga";

GoalPole::GoalPole(MapActorData& map_actor_data)
    : MapActorItem(map_actor_data)
    , mpResName(nullptr)
{
    rio::MemUtil::set(&mBase, 0, sizeof(mBase));
    rio::MemUtil::set(&mGoalFlag, 0, sizeof(mGoalFlag));
    rio::MemUtil::set(&mTorideStd, 0, sizeof(mTorideStd));

    static const std::string archive_path_normal        = MainWindow::getContentPath() + "/Common/actor/" + cResNameNormal      + ".szs";
    static const std::string archive_path_kaiga         = MainWindow::getContentPath() + "/Common/actor/" + cResNameKaiga       + ".szs";
    static const std::string archive_path_rdash         = MainWindow::getContentPath() + "/Common/actor/" + cResNameRDash       + ".szs";
    static const std::string archive_path_kaiga_rdash   = MainWindow::getContentPath() + "/Common/actor/" + cResNameKaigaRDash  + ".szs";

    bool rdash = map_actor_data.id == 630 || map_actor_data.id == 631;
    bool kaiga = map_actor_data.id == 503 || map_actor_data.id == 631;

    const std::string& res_name =
        rdash
            ? (kaiga ? cResNameKaigaRDash : cResNameRDash)
            : (kaiga ? cResNameKaiga : cResNameNormal);

    mpResName = &res_name;

    const std::string& archive_path =
        rdash
            ? (kaiga ? archive_path_kaiga_rdash : archive_path_rdash)
            : (kaiga ? archive_path_kaiga : archive_path_normal);

    const SharcArchiveRes* archive_res = ResMgr::instance()->loadArchiveRes(res_name, archive_path, true);
    if (archive_res == nullptr)
        return;

    f32 frame = (mMapActorData.settings[0] >> 28) +
        (kaiga
            ? 0
            : ((mMapActorData.settings[0] & 0xf) * 2));

    const ModelResource* model_res = ModelResMgr::instance()->loadResFile(res_name, archive_res, res_name.c_str());
    RIO_ASSERT(model_res);

    mBase.p_model = BasicModel::create(
        const_cast<ModelResource*>(model_res),
        "baseA",
        1, 1, 0, 0, 0,
        Model::cBoundingMode_Disable
    );

    mBase.p_tex_anim = mBase.p_model->getTexAnim(0);
    mBase.p_tex_anim->play(model_res, "baseA");
    mBase.p_tex_anim->getFrameCtrl().set(FrameCtrl::cMode_NoRepeat, 0.0f, frame);

    mGoalFlag.p_model = BasicModel::create(
        const_cast<ModelResource*>(model_res),
        "goal_flag",
        1, 1, 1, 0, 0,
        Model::cBoundingMode_Disable
    );

    mGoalFlag.p_model->getSklAnim(0)->play(model_res, "wait");
    mGoalFlag.p_model->getSklAnim(0)->getFrameCtrl().setRate(1.0f);
    mGoalFlag.p_model->getSklAnim(0)->getFrameCtrl().setPlayMode(FrameCtrl::cMode_Repeat);
    mGoalFlag.p_model->getSklAnim(0)->getFrameCtrl().reset();

    mGoalFlag.p_tex_anim = mGoalFlag.p_model->getTexAnim(0);
    mGoalFlag.p_tex_anim->play(model_res, "goal_flag");
    mGoalFlag.p_tex_anim->getFrameCtrl().set(FrameCtrl::cMode_NoRepeat, 0.0f, frame);

    mGoalFlag.p_shu_anim = mGoalFlag.p_model->getShuAnim(0);
    mGoalFlag.p_shu_anim->playTexSrtAnim(model_res, "wait");
    mGoalFlag.p_shu_anim->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
    mGoalFlag.p_shu_anim->getFrameCtrl().setRate(1.0f);

    mTorideStd.p_model = BasicModel::create(
        const_cast<ModelResource*>(model_res),
        "toride_std",
        1, 1, 0, 1, 0,
        Model::cBoundingMode_Disable
    );

    mTorideStd.p_tex_anim = mTorideStd.p_model->getTexAnim(0);
    mTorideStd.p_tex_anim->play(model_res, "toride_std");
    mTorideStd.p_tex_anim->getFrameCtrl().set(FrameCtrl::cMode_NoRepeat, 0.0f, frame);

    if (!kaiga)
    {
        mTorideStd.p_vis_anim = mTorideStd.p_model->getVisAnim(0);
        mTorideStd.p_vis_anim->playBoneVisAnim(model_res, "toride_std");
        mTorideStd.p_vis_anim->getFrameCtrl().set(FrameCtrl::cMode_NoRepeat, 0.0f, frame);
    }

    update();
}

GoalPole::~GoalPole()
{
    if (mBase.p_model)
    {
        delete mBase.p_model->getModel();
        delete mBase.p_model;

        delete mGoalFlag.p_model->getModel();
        delete mGoalFlag.p_model;

        delete mTorideStd.p_model->getModel();
        delete mTorideStd.p_model;

        ModelResMgr::instance()->destroyResFile(*mpResName);
        ResMgr::instance()->destroyArchiveRes(*mpResName);
    }
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

static BaseRotMtx sMtx(0.0f, rio::Mathf::deg2rad(270), 0.0f);

}

void GoalPole::update()
{
    if (mBase.p_model == nullptr)
        return;

    {
        rio::Matrix34f mtx;
        mtx.makeT({ f32(mMapActorData.offset.x), -f32(mMapActorData.offset.y + 16), 2900.0f });
        mBase.p_model->getModel()->setMtxRT(mtx);
        mBase.p_model->updateModel();
    }
    {
        rio::Matrix34f mtx;
        mtx.makeT({ f32(mMapActorData.offset.x + 256), -f32(mMapActorData.offset.y + 16), -1800.0f });
        mTorideStd.p_model->getModel()->setMtxRT(mtx);
        mTorideStd.p_model->updateModel();
    }
    {
        rio::Matrix34f& mtx = sMtx.mtx;
        mtx.setTranslationWorld({ f32(mMapActorData.offset.x), -f32(mMapActorData.offset.y) + 70, 2900.0f });
        mGoalFlag.p_model->getModel()->setMtxRT(mtx);
        mGoalFlag.p_model->updateAnimations();
        mGoalFlag.p_model->getModel()->updateAnimations();
        mGoalFlag.p_model->getModel()->updateModel();
    }
}

void GoalPole::scheduleDraw()
{
    if (mBase.p_model == nullptr)
        return;

    Renderer::instance()->drawModel(*mBase.p_model);
    Renderer::instance()->drawModel(*mGoalFlag.p_model);

    if (!(mMapActorData.settings[0] >> 4 & 1))
        Renderer::instance()->drawModel(*mTorideStd.p_model);
}
