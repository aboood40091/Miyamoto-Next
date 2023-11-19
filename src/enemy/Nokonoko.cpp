#include <graphics/BasicModel.h>
#include <graphics/ModelResMgr.h>
#include <graphics/Renderer.h>
#include <enemy/Nokonoko.h>
#include <resource/ResMgr.h>

#include <MainWindow.h>

static const std::string cResName[2] = {
    "nokonokoA",
    "nokonokoBig"
};

static const char* cShellModelName[2] = {
    "nokonoko_shell",
    "nokonokoBig_shell"
};

static const char* cShellTexAnimName[2] = {
    "Tnokonoko_shell",
    "nokonokoBig_shell"
};

static inline void SetColor(TexturePatternAnimation* tex_anim, const ModelResource* model_res, const char* name, s32 color)
{
    tex_anim->play(model_res, name);
    tex_anim->getFrameCtrl().setRate(0.0f);
    tex_anim->getFrameCtrl().setFrame(color);
    tex_anim->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
}

Nokonoko::Nokonoko(MapActorData& map_actor_data)
    : MapActorItem(map_actor_data)
    , mIsBig(map_actor_data.id == 476)
    , mpModel(nullptr)
    , mpShellModel(nullptr)
{
    static const std::string cArchivePath[2] = {
        MainWindow::getContentPath() + "/Common/actor/" + cResName[0] + ".szs",
        MainWindow::getContentPath() + "/Common/actor/" + cResName[1] + ".szs"
    };

    const std::string& res_name = cResName[mIsBig];
    const std::string& archive_path = cArchivePath[mIsBig];

    const SharcArchiveRes* archive_res = ResMgr::instance()->loadArchiveRes(res_name, archive_path, true);
    if (archive_res == nullptr)
        return;

    const ModelResource* model_res = ModelResMgr::instance()->loadResFile(res_name, archive_res, res_name.c_str());
    RIO_ASSERT(model_res);

    const char* model_name = res_name.c_str();

    mpModel = BasicModel::create(
        const_cast<ModelResource*>(model_res),
        model_name,
        1, 1, 0, 0, /* mIsBig ? 1 : */ 0,   // Enabling shape animation crashes on Windows atm
        Model::cBoundingMode_Disable
    );

    mpShellModel = BasicModel::create(
        const_cast<ModelResource*>(model_res),
        cShellModelName[mIsBig],
        1, 1, 0, 0, 0,
        Model::cBoundingMode_Disable
    );

    mpModel->getSklAnim(0)->play(model_res, "walkA");
    mpModel->getSklAnim(0)->getFrameCtrl().set(FrameCtrl::cMode_Repeat, 1.0f, 0.0f);

    s32 color = mMapActorData.settings[0] & 1;
    SetColor(mpModel->getTexAnim(0), model_res, model_name, color);
    SetColor(mpShellModel->getTexAnim(0), model_res, cShellTexAnimName[mIsBig], color);

    /*
    if (mIsBig)
    {
        ShapeAnimation* sha_anim = mpModel->getShaAnim(0);
        sha_anim->play(model_res, "nokonokoBig");
        sha_anim->getFrameCtrl().set(FrameCtrl::cMode_Repeat, 1.0f, 0.0f);
    }
    */

    update();
}

Nokonoko::~Nokonoko()
{
    if (mpModel)
    {
        delete mpModel->getModel();
        delete mpModel;

        delete mpShellModel->getModel();
        delete mpShellModel;

        const std::string& res_name = cResName[mIsBig];

        ModelResMgr::instance()->destroyResFile(res_name);
        ResMgr::instance()->destroyArchiveRes(res_name);
    }
}

namespace {

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

static BaseRotMtx sMtx[2] {
    BaseRotMtx(0.0f, rio::Mathf::deg2rad(285), 0.0f),
    BaseRotMtx(0.0f, rio::Mathf::deg2rad(300), 0.0f)
};

static const BaseRotMtx sHeadDeltaRMtx(rio::Mathf::deg2rad(300 - 285), 0.0f, 0.0f);

static const rio::Vector3f cScale2x { 2.0f, 2.0f, 2.0f };

}

void Nokonoko::update()
{
    if (mpModel == nullptr)
        return;

    const rio::Vector3f pos { f32(mMapActorData.offset.x + 8), -f32(mMapActorData.offset.y + 16), getZPos_() };

    rio::Matrix34f& mtx = sMtx[mIsBig].mtx;
    mtx.setTranslationWorld(pos);

    if (mMapActorData.settings[0] >> 4 & 1)
    {
        mpShellModel->getModel()->setMtxRT(mtx);

        if (mIsBig)
            mpShellModel->getModel()->setScale(cScale2x);

        mpShellModel->updateAnimations();
        mpShellModel->updateModel();
    }
    else
    {
        mpModel->getModel()->setMtxRT(mtx);

        if (mIsBig)
            mpModel->getModel()->setScale(cScale2x);

        mpModel->updateAnimations();
        mpModel->getModel()->updateAnimations();

        if (!mIsBig)
        {
            s32 index = mpModel->getModel()->searchBoneIndex("head");

            rio::Matrix34f head_mtx;
            rio::Vector3f head_scale;
            mpModel->getModel()->getBoneLocalMatrix(index, &head_mtx, &head_scale);

            head_mtx.setMul(head_mtx, sHeadDeltaRMtx.mtx);

            mpModel->getModel()->setBoneLocalMatrix(index, head_mtx, head_scale);
        }

        mpModel->getModel()->updateModel();
    }
}

void Nokonoko::scheduleDraw()
{
    if (mpModel == nullptr)
        return;

    if (mMapActorData.settings[0] >> 4 & 1)
        Renderer::instance()->drawModel(*mpShellModel);

    else
        Renderer::instance()->drawModel(*mpModel);
}
