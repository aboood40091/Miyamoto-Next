#include <Globals.h>
#include <graphics/BasicModel.h>
#include <graphics/ModelResMgr.h>
#include <graphics/Renderer.h>
#include <map_obj/GoalPole.h>
#include <resource/ResMgr.h>

static const std::string cResNameNormal = "goal_set";
static const std::string cResNameKaiga = "goal_set_kaiga";
static const std::string cResNameRDash = "R_goal_set";
static const std::string cResNameKaigaRDash = "R_goal_set_kaiga";

static inline void SetFrame(TexturePatternAnimation* tex_anim, const ModelResource* model_res, const char* name, f32 frame)
{
    tex_anim->play(model_res, name);
    tex_anim->getFrameCtrl().set(FrameCtrl::cMode_NoRepeat, 0.0f, frame);
}

static inline void SetFrame(VisibilityAnimation* vis_anim, const ModelResource* model_res, const char* name, f32 frame)
{
    vis_anim->playBoneVisAnim(model_res, name);
    vis_anim->getFrameCtrl().set(FrameCtrl::cMode_NoRepeat, 0.0f, frame);
}

GoalPole::GoalPole(MapActorData& map_actor_data, u32 index)
    : MapActorItem(map_actor_data, index)
    , mpResName(nullptr)
    , mpModelResource(nullptr)
    , mpBaseModel(nullptr)
    , mpGoalFlagModel(nullptr)
    , mpTorideStdModel(nullptr)
    , cIsKaiga(map_actor_data.id == 503 || map_actor_data.id == 631)
    , mFrame(0)
{
    static const std::string archive_path_normal        = Globals::getContentPath() + "/Common/actor/" + cResNameNormal     + ".szs";
    static const std::string archive_path_kaiga         = Globals::getContentPath() + "/Common/actor/" + cResNameKaiga      + ".szs";
    static const std::string archive_path_rdash         = Globals::getContentPath() + "/Common/actor/" + cResNameRDash      + ".szs";
    static const std::string archive_path_kaiga_rdash   = Globals::getContentPath() + "/Common/actor/" + cResNameKaigaRDash + ".szs";

    bool rdash = map_actor_data.id == 630 || map_actor_data.id == 631;

    const std::string& res_name =
        rdash
            ? (cIsKaiga ? cResNameKaigaRDash : cResNameRDash)
            : (cIsKaiga ? cResNameKaiga : cResNameNormal);

    mpResName = &res_name;

    const std::string& archive_path =
        rdash
            ? (cIsKaiga ? archive_path_kaiga_rdash : archive_path_rdash)
            : (cIsKaiga ? archive_path_kaiga : archive_path_normal);

    const SharcArchiveRes* archive_res = ResMgr::instance()->loadArchiveRes(res_name, archive_path, true);
    if (archive_res == nullptr)
        return;

    mpModelResource = ModelResMgr::instance()->loadResFile(res_name, archive_res, res_name.c_str());
    RIO_ASSERT(mpModelResource);

    mpBaseModel = BasicModel::create(
        const_cast<ModelResource*>(mpModelResource),
        "baseA",
        0, 1, 0, 0, 0,
        Model::cBoundingMode_Disable
    );

    mpGoalFlagModel = BasicModel::create(
        const_cast<ModelResource*>(mpModelResource),
        "goal_flag",
        1, 1, 1, 0, 0,
        Model::cBoundingMode_Disable
    );

    mpGoalFlagModel->getSklAnim(0)->play(mpModelResource, "wait");
    mpGoalFlagModel->getSklAnim(0)->getFrameCtrl().setRate(1.0f);
    mpGoalFlagModel->getSklAnim(0)->getFrameCtrl().setPlayMode(FrameCtrl::cMode_Repeat);
    mpGoalFlagModel->getSklAnim(0)->getFrameCtrl().reset();

    mpGoalFlagModel->getShuAnim(0)->playTexSrtAnim(mpModelResource, "wait");
    mpGoalFlagModel->getShuAnim(0)->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
    mpGoalFlagModel->getShuAnim(0)->getFrameCtrl().setRate(1.0f);

    mpTorideStdModel = BasicModel::create(
        const_cast<ModelResource*>(mpModelResource),
        "toride_std",
        0, 1, 0, cIsKaiga ? 0 : 1, 0,
        Model::cBoundingMode_Disable
    );

    updatePositionXY_();
    setModelMtxRT_();

    mFrame = (mMapActorData.settings[0] >> 28) +
        (cIsKaiga
            ? 0
            : ((mMapActorData.settings[0] & 0xf) * 2));

    updateFrame_();
}

GoalPole::~GoalPole()
{
    if (mpModelResource)
    {
        BasicModel::destroy(mpBaseModel);
        BasicModel::destroy(mpGoalFlagModel);
        BasicModel::destroy(mpTorideStdModel);

        ModelResMgr::instance()->destroyResFile(*mpResName);
        ResMgr::instance()->destroyArchiveRes(*mpResName);
    }
}

void GoalPole::setModelItemID_()
{
    if (mpModelResource)
    {
        mpBaseModel->getModel()->setItemID(mItemID);
        mpGoalFlagModel->getModel()->setItemID(mItemID);
        mpTorideStdModel->getModel()->setItemID(mItemID);
    }
}

void GoalPole::setModelSelection_()
{
    if (mpModelResource)
    {
        mpBaseModel->getModel()->setSelection(mIsSelected);
        mpGoalFlagModel->getModel()->setSelection(mIsSelected);
        mpTorideStdModel->getModel()->setSelection(mIsSelected);
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

void GoalPole::setModelMtxRT_()
{
    if (mpModelResource == nullptr)
        return;

    {
        rio::Matrix34f mtx;
        mtx.makeT({ mPosition.x, mPosition.y, 2900.0f });
        mpBaseModel->getModel()->setMtxRT(mtx);
        mpBaseModel->getModel()->updateModel();
    }
    {
        rio::Matrix34f mtx;
        mtx.makeT({ mPosition.x + 256, mPosition.y, -1800.0f });
        mpTorideStdModel->getModel()->setMtxRT(mtx);
        mpTorideStdModel->getModel()->updateModel();
    }
    {
        rio::Matrix34f& mtx = sMtx.mtx;
        mtx.setTranslationWorld({ mPosition.x, mPosition.y + 86, 2900.0f });
        mpGoalFlagModel->getModel()->setMtxRT(mtx);
    }
}

void GoalPole::updateFrame_()
{
    if (mpModelResource == nullptr)
        return;

    f32 frame = mFrame;

    SetFrame(mpBaseModel->getTexAnim(0), mpModelResource, "baseA", frame);
    mpBaseModel->updateAnimations();
    mpBaseModel->updateModel();

    SetFrame(mpGoalFlagModel->getTexAnim(0), mpModelResource, "goal_flag", frame);

    SetFrame(mpTorideStdModel->getTexAnim(0), mpModelResource, "toride_std", frame);
    if (!cIsKaiga)
        SetFrame(mpTorideStdModel->getVisAnim(0), mpModelResource, "toride_std", frame);
    mpBaseModel->updateAnimations();
    mpBaseModel->updateModel();
}

void GoalPole::onDataChange(DataChangeFlag flag)
{
    if (flag & DATA_CHANGE_FLAG_OFFSET)
    {
        updatePositionXY_();
        setModelMtxRT_();
    }

    if (flag & DATA_CHANGE_FLAG_SETTINGS_0)
    {
        s32 frame = (mMapActorData.settings[0] >> 28) +
            (cIsKaiga
                ? 0
                : ((mMapActorData.settings[0] & 0xf) * 2));
        if (mFrame != frame)
        {
            mFrame = frame;
            updateFrame_();
        }
    }
}

void GoalPole::onSceneUpdate()
{
    if (mpModelResource == nullptr)
        return;

    mpGoalFlagModel->updateAnimations();
    mpGoalFlagModel->updateModel();
}

void GoalPole::scheduleDraw()
{
    if (mpModelResource == nullptr)
        return;

    Renderer::instance()->drawModel(*mpBaseModel);
    Renderer::instance()->drawModel(*mpGoalFlagModel);

    if (!(mMapActorData.settings[0] >> 4 & 1))
        Renderer::instance()->drawModel(*mpTorideStdModel);
}
