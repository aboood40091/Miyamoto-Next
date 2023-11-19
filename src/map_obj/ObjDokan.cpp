#include <graphics/BasicModel.h>
#include <graphics/ModelResMgr.h>
#include <graphics/Renderer.h>
#include <map_obj/ObjDokan.h>
#include <resource/ResMgr.h>

#include <MainWindow.h>

static const std::string cResName[ObjDokan::TYPE_MAX] = {
    "obj_dokan",
    "obj_dokan_kaiga",
    "obj_dokan",
    "obj_dokan",
    "obj_dokan_CB"
};

static const char* const cModelNameA[ObjDokan::TYPE_MAX] = {
    "obj_dokan_A",
    "obj_dokan_kaiga_A",
    "obj_dokan_mame_A",
    "obj_dokan_big_A",
    "obj_dokan_CB_A"
};

static const char* const cModelNameB[ObjDokan::TYPE_MAX] = {
    "obj_dokan_B",
    "obj_dokan_kaiga_B",
    "obj_dokan_mame_B",
    "obj_dokan_big_B",
    "obj_dokan_CB_B"
};

static const f32 cAngle[ObjDokan::DIRECTION_MAX] = {
    rio::Mathf::pi() + rio::Mathf::piHalf(),
    rio::Mathf::piHalf(),
    0,
    rio::Mathf::pi()
};

ObjDokan::ObjDokan(Direction dir, Type type, f32 length, bool a_visible, Color color)
    : mIsAVisible(a_visible)
{
    rio::MemUtil::set(&mA, 0, sizeof(mA));
    rio::MemUtil::set(&mB, 0, sizeof(mB));

    RIO_ASSERT(length > 0);
    mLength = length;
    mScale.x = 1.0f;
    mScale.y = mLength / 16;
    mScale.z = 1.0f;

    RIO_ASSERT(dir < DIRECTION_MAX);
    static_cast<rio::Matrix34f&>(mMtxRT).makeR({ 0.0f, 0.0f, cAngle[dir] });

    RIO_ASSERT(type < TYPE_MAX);
    mType = type;

    static const std::string cArchivePath[TYPE_MAX] = {
        MainWindow::getContentPath() + "/Common/actor/" + cResName[TYPE_NORMAL] + ".szs",
        MainWindow::getContentPath() + "/Common/actor/" + cResName[TYPE_KAIGA]  + ".szs",
        MainWindow::getContentPath() + "/Common/actor/" + cResName[TYPE_MAME]   + ".szs",
        MainWindow::getContentPath() + "/Common/actor/" + cResName[TYPE_BIG]    + ".szs",
        MainWindow::getContentPath() + "/Common/actor/" + cResName[TYPE_CB]     + ".szs"
    };

    const std::string& res_name = cResName[mType];
    const std::string& archive_path = cArchivePath[mType];

    const SharcArchiveRes* archive_res = ResMgr::instance()->loadArchiveRes(res_name, archive_path, true);
    if (archive_res == nullptr)
        return;

    const ModelResource* model_res = ModelResMgr::instance()->loadResFile(res_name, archive_res, res_name.c_str());
    RIO_ASSERT(model_res);

    const char* const model_name_a = cModelNameA[mType];
    const char* const model_name_b = cModelNameB[mType];

    mA.p_model = BasicModel::create(
        const_cast<ModelResource*>(model_res),
        model_name_a,
        0, 1, 2, 0, 0,
        Model::cBoundingMode_Disable
    );

    mB.p_model = BasicModel::create(
        const_cast<ModelResource*>(model_res),
        model_name_b,
        0, 1, 2, 0, 0,
        Model::cBoundingMode_Disable
    );

    static const f32 cBaseFrame[DIRECTION_MAX] = {
        0.0f,
        8.0f,
        0.0f,
        4.0f
    };
    f32 frame =
        (mType != TYPE_CB && color != COLOR_INVALID)
            ? cBaseFrame[dir] + s32(color)
            : -1.0f;

    if (frame != -1.0f)
    {
        mA.p_tex_pat_anim = mA.p_model->getTexAnim(0);
        mA.p_tex_pat_anim->play(model_res, model_name_a);
        mA.p_tex_pat_anim->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
        mA.p_tex_pat_anim->getFrameCtrl().setFrame(frame);

        mB.p_tex_pat_anim = mB.p_model->getTexAnim(0);
        mB.p_tex_pat_anim->play(model_res, model_name_b);
        mB.p_tex_pat_anim->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
        mB.p_tex_pat_anim->getFrameCtrl().setFrame(frame);
    }

    if (mType == TYPE_KAIGA)
    {
        mA.p_tex_srt_anim = mA.p_model->getShuAnim(0);
        mA.p_tex_srt_anim->playTexSrtAnim(model_res, model_name_a);
        mA.p_tex_srt_anim->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
        mA.p_tex_srt_anim->getFrameCtrl().setFrame(frame);

        mB.p_tex_srt_anim = mB.p_model->getShuAnim(0);
        mB.p_tex_srt_anim->playTexSrtAnim(model_res, model_name_b);
        mB.p_tex_srt_anim->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
        mB.p_tex_srt_anim->getFrameCtrl().setFrame(frame);
    }
    else if (mType == TYPE_CB)
    {
        mA.p_tex_srt_anim = mA.p_model->getShuAnim(0);
        mA.p_tex_srt_anim->playTexSrtAnim(model_res, "obj_dokan_CB_wait");
        mA.p_tex_srt_anim->getFrameCtrl().setPlayMode(FrameCtrl::cMode_Repeat);
        mA.p_tex_srt_anim->getFrameCtrl().setFrame(0.0f);
        mA.p_tex_srt_anim->getFrameCtrl().setRate(1.0f);

        mB.p_tex_srt_anim = mB.p_model->getShuAnim(0);
        mB.p_tex_srt_anim->playTexSrtAnim(model_res, "obj_dokan_CB_wait");
        mB.p_tex_srt_anim->getFrameCtrl().setPlayMode(FrameCtrl::cMode_Repeat);
        mB.p_tex_srt_anim->getFrameCtrl().setFrame(0.0f);
        mB.p_tex_srt_anim->getFrameCtrl().setRate(1.0f);

        mA.p_color_anim = mA.p_model->getShuAnim(1);
        mA.p_color_anim->playColorAnim(model_res, "obj_dokan_CB_wait");
        mA.p_color_anim->getFrameCtrl().setPlayMode(FrameCtrl::cMode_Repeat);
        mA.p_color_anim->getFrameCtrl().setFrame(0.0f);
        mA.p_color_anim->getFrameCtrl().setRate(1.0f);

        mB.p_color_anim = mB.p_model->getShuAnim(1);
        mB.p_color_anim->playColorAnim(model_res, "obj_dokan_CB_wait");
        mB.p_color_anim->getFrameCtrl().setPlayMode(FrameCtrl::cMode_Repeat);
        mB.p_color_anim->getFrameCtrl().setFrame(0.0f);
        mB.p_color_anim->getFrameCtrl().setRate(1.0f);
    }
}

ObjDokan::~ObjDokan()
{
    if (isCreated())
    {
        delete mA.p_model->getModel();
        delete mA.p_model;

        delete mB.p_model->getModel();
        delete mB.p_model;

        const std::string& res_name = cResName[mType];

        ModelResMgr::instance()->destroyResFile(res_name);
        ResMgr::instance()->destroyArchiveRes(res_name);
    }
}

void ObjDokan::update(const rio::BaseVec3f& position)
{
    rio::Matrix34f& mtxRT = static_cast<rio::Matrix34f&>(mMtxRT);
    mtxRT.setTranslationWorld(static_cast<const rio::Vector3f&>(position));

    rio::Matrix34f mtx = mtxRT;
    mtx.applyTranslationLocal({ 0.0f, mLength * 0.5f, 0.0f });

    mB.p_model->getModel()->setMtxRT(mtx);
    mB.p_model->getModel()->setScale(static_cast<const rio::Vector3f&>(mScale));

    if (mType == TYPE_CB)
        mB.p_model->updateAnimations();

    mB.p_model->updateModel();

    if (mType == TYPE_KAIGA)
    {
        MaterialG3d* material = static_cast<MaterialG3d*>(mB.p_model->getModel()->getMaterial(0));
        RIO_ASSERT(material);
        material->setTexSrtMtx(0, reinterpret_cast<const rio::Vector2f&>(mScale.x), 0, { 0.0f, (1 - mScale.y) * 0.5f });
    }

    if (mIsAVisible)
    {
        rio::Matrix34f mtx = mtxRT;
        mtx.applyTranslationLocal({ 0.0f, mLength, 0.0f });

        mA.p_model->getModel()->setMtxRT(mtx);
      //mA.p_model->getModel()->setScale({ 1.0f, 1.0f, 1.0f });

        if (mType == TYPE_CB)
            mA.p_model->updateAnimations();

        mA.p_model->updateModel();
    }
}

void ObjDokan::scheduleDraw() const
{
    Renderer::instance()->drawModel(*mB.p_model);
    if (mIsAVisible)
        Renderer::instance()->drawModel(*mA.p_model);
}
