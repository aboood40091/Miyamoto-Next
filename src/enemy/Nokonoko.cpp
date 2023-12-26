#include <CourseView.h>
#include <Globals.h>
#include <graphics/BasicModel.h>
#include <graphics/ModelResMgr.h>
#include <graphics/Renderer.h>
#include <enemy/Nokonoko.h>
#include <system/ResMgr.h>

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

Nokonoko::Nokonoko(const MapActorData& map_actor_data, u32 index)
    : MapActorItem(map_actor_data, index)
    , cIsBig(map_actor_data.type == 476)
    , mpModelResource(nullptr)
    , mpModel(nullptr)
    , mpShellModel(nullptr)
    , mIsAltColor(false)
{
    static const std::string cArchivePath[2] = {
        Globals::sContentPath + "/Common/actor/" + cResName[0] + ".szs",
        Globals::sContentPath + "/Common/actor/" + cResName[1] + ".szs"
    };

    const std::string& res_name = cResName[cIsBig];
    const std::string& archive_path = cArchivePath[cIsBig];

    const SharcArchiveRes* archive_res = ResMgr::instance()->loadArchiveRes(res_name, archive_path, true);
    if (archive_res == nullptr)
        return;

    mpModelResource = ModelResMgr::instance()->loadResFile(res_name, archive_res, res_name.c_str(), Globals::sForceSharcfb);
    RIO_ASSERT(mpModelResource);

    const char* model_name = res_name.c_str();

    mpModel = BasicModel::create(
        const_cast<ModelResource*>(mpModelResource),
        model_name,
        1, 1, 0, 0, /* cIsBig ? 1 : */ 0,   // Enabling shape animation crashes on Windows atm
        Model::cBoundingMode_Disable
    );

    mpShellModel = BasicModel::create(
        const_cast<ModelResource*>(mpModelResource),
        cShellModelName[cIsBig],
        0, 1, 0, 0, 0,
        Model::cBoundingMode_Disable
    );

    if (cIsBig)
    {
        mpShellModel->getModel()->setScale({ 2.0f, 2.0f, 2.0f });
        mpModel->getModel()->setScale({ 2.0f, 2.0f, 2.0f });
    }

    mpModel->getSklAnim(0)->play(mpModelResource, "walkA");
    mpModel->getSklAnim(0)->getFrameCtrl().set(FrameCtrl::cMode_Repeat, 1.0f, 0.0f);

    mIsAltColor = map_actor_data.settings[0] & 1;
    updateColor_();

    /*
    if (cIsBig)
    {
        ShapeAnimation* sha_anim = mpModel->getShaAnim(0);
        sha_anim->play(mpModelResource, "nokonokoBig");
        sha_anim->getFrameCtrl().set(FrameCtrl::cMode_Repeat, 1.0f, 0.0f);
    }
    */

    updatePositionXY_(map_actor_data);
    updatePositionZ_(map_actor_data);

    setModelMtxRT_();

    setModelItemID_();
}

Nokonoko::~Nokonoko()
{
    if (mpModelResource)
    {
        BasicModel::destroy(mpModel);
        BasicModel::destroy(mpShellModel);

        const std::string& res_name = cResName[cIsBig];

        ModelResMgr::instance()->destroyResFile(res_name);
        ResMgr::instance()->destroyArchiveRes(res_name);
    }
}

void Nokonoko::setModelItemID_()
{
    if (mpModelResource)
    {
        mpModel->getModel()->setItemID(mItemID);
        mpShellModel->getModel()->setItemID(mItemID);
    }
}

void Nokonoko::setModelSelection_()
{
    if (mpModelResource)
    {
        mpModel->getModel()->setSelection(mIsSelected);
        mpShellModel->getModel()->setSelection(mIsSelected);
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

static BaseRotMtx sMtx[2] {
    BaseRotMtx(0.0f, rio::Mathf::deg2rad(285), 0.0f),
    BaseRotMtx(0.0f, rio::Mathf::deg2rad(300), 0.0f)
};

static const BaseRotMtx sHeadDeltaRMtx(rio::Mathf::deg2rad(300 - 285), 0.0f, 0.0f);

}

void Nokonoko::setModelMtxRT_()
{
    if (mpModelResource == nullptr)
        return;

    rio::Matrix34f& mtx = sMtx[cIsBig].mtx;
    mtx.setTranslationWorld(static_cast<const rio::Vector3f&>(mPosition));

    mpModel->getModel()->setMtxRT(mtx);

    mpShellModel->getModel()->setMtxRT(mtx);
    mpShellModel->getModel()->updateModel();
}

void Nokonoko::updateColor_()
{
    if (mpModelResource == nullptr)
        return;

    SetColor(mpModel->getTexAnim(0), mpModelResource, cResName[cIsBig].c_str(), mIsAltColor);

    SetColor(mpShellModel->getTexAnim(0), mpModelResource, cShellTexAnimName[cIsBig], mIsAltColor);
    mpShellModel->updateAnimations();
    mpShellModel->updateModel();
}

void Nokonoko::onDataChange(const MapActorData& map_actor_data, DataChangeFlag flag)
{
    bool position_changed = false;

    if (flag & DATA_CHANGE_FLAG_SETTINGS_0)
    {
        bool is_alt_color = map_actor_data.settings[0] & 1;
        if (mIsAltColor != is_alt_color)
        {
            mIsAltColor = is_alt_color;
            updateColor_();
        }
    }

    if (flag & DATA_CHANGE_FLAG_LAYER)
    {
        updatePositionZ_(map_actor_data);
        position_changed = true;
    }

    if (flag & DATA_CHANGE_FLAG_OFFSET && mpModelResource)
    {
        updatePositionXY_(map_actor_data);
        position_changed = true;
    }

    if (position_changed)
        setModelMtxRT_();
}

void Nokonoko::onSceneUpdate()
{
    if (mpModelResource == nullptr)
        return;

    {
        mpModel->updateAnimations();
        mpModel->getModel()->updateAnimations();

        if (!cIsBig)
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
    if (drawBox())
        return;

    const MapActorData& map_actor_data = CourseView::instance()->getCourseDataFile().getMapActorData()[mItemID.getIndex()];

    if (map_actor_data.settings[0] >> 4 & 1)
        Renderer::instance()->drawModel(*mpShellModel);

    else
        Renderer::instance()->drawModel(*mpModel);
}
