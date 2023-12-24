#include <Globals.h>
#include <graphics/BasicModel.h>
#include <graphics/ModelResMgr.h>
#include <graphics/Renderer.h>
#include <map_obj/ObjDokan.h>
#include <system/ResMgr.h>

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

static const f32 cBaseFrame[ObjDokan::DIRECTION_MAX] = {
    0.0f,
    8.0f,
    0.0f,
    4.0f
};

ObjDokan::ObjDokan(Direction dir)
    : mpModelResource(nullptr)
    , mpModelA(nullptr)
    , mpModelB(nullptr)
    , mBaseFrame(0.0f)
    , mType(TYPE_MAX)
    , mLength(0.0f)
    , mIsEnableDrawA(false)
    , mColor(COLOR_INVALID)
{
    mScale.x = 1.0f;
    mScale.z = 1.0f;

    RIO_ASSERT(dir < DIRECTION_MAX);
    static_cast<rio::Matrix34f&>(mMtxRT).makeR({ 0.0f, 0.0f, cAngle[dir] });
    mBaseFrame = cBaseFrame[dir];
}

ObjDokan::~ObjDokan()
{
    destroy();
}

bool ObjDokan::update(f32 length, bool draw_a, Color color)
{
    if (!isCreated() || (mType != TYPE_KAIGA && mColor == COLOR_INVALID && color != COLOR_INVALID))
        return false;

    bool need_mtx_update =  false;

    if (mLength != length)
    {
        setLength_(length);
        need_mtx_update = true;
    }

    mIsEnableDrawA = draw_a;

    if (mType != TYPE_CB && mColor != color)
    {
        mColor = color;

        const char* const model_name_a = cModelNameA[mType];
        const char* const model_name_b = cModelNameB[mType];

        f32 frame =
            (mColor != COLOR_INVALID)
                ? mBaseFrame + s32(mColor)
                : -1.0f;

        if (frame != -1.0f)
        {
            mpModelA->getTexAnim(0)->play(mpModelResource, model_name_a);
            mpModelA->getTexAnim(0)->getFrameCtrl().set(FrameCtrl::cMode_NoRepeat, 0.0f, frame);

            mpModelB->getTexAnim(0)->play(mpModelResource, model_name_b);
            mpModelB->getTexAnim(0)->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
            mpModelB->getTexAnim(0)->getFrameCtrl().setFrame(frame);
        }

        if (mType == TYPE_KAIGA)
        {
            mpModelA->getShuAnim(0)->playTexSrtAnim(mpModelResource, model_name_a);
            mpModelA->getShuAnim(0)->getFrameCtrl().set(FrameCtrl::cMode_NoRepeat, 0.0f, frame);

            mpModelB->getShuAnim(0)->playTexSrtAnim(mpModelResource, model_name_b);
            mpModelB->getShuAnim(0)->getFrameCtrl().set(FrameCtrl::cMode_NoRepeat, 0.0f, frame);
        }

        need_mtx_update = true;
    }

    if (need_mtx_update)
        setModelMtxSRT_();

    return true;
}

bool ObjDokan::initialize(Type type, f32 length, bool draw_a, Color color)
{
    if (isCreated() && mType == type && update(length, draw_a, color))
        return false;

    destroy();

    mIsEnableDrawA = draw_a;
    mColor = color;

    setLength_(length);

    RIO_ASSERT(type < TYPE_MAX);
    mType = type;

    static const std::string cArchivePath[TYPE_MAX] = {
        Globals::getContentPath() + "/Common/actor/" + cResName[TYPE_NORMAL] + ".szs",
        Globals::getContentPath() + "/Common/actor/" + cResName[TYPE_KAIGA]  + ".szs",
        Globals::getContentPath() + "/Common/actor/" + cResName[TYPE_MAME]   + ".szs",
        Globals::getContentPath() + "/Common/actor/" + cResName[TYPE_BIG]    + ".szs",
        Globals::getContentPath() + "/Common/actor/" + cResName[TYPE_CB]     + ".szs"
    };

    const std::string& res_name = cResName[mType];
    const std::string& archive_path = cArchivePath[mType];

    const SharcArchiveRes* archive_res = ResMgr::instance()->loadArchiveRes(res_name, archive_path, true);
    if (archive_res == nullptr)
        return false;

    mpModelResource = ModelResMgr::instance()->loadResFile(res_name, archive_res, res_name.c_str(), Globals::forceSharcfb());
    RIO_ASSERT(mpModelResource);

    const char* const model_name_a = cModelNameA[mType];
    const char* const model_name_b = cModelNameB[mType];

    mpModelA = BasicModel::create(
        const_cast<ModelResource*>(mpModelResource),
        model_name_a,
        0, 1, 2, 0, 0,
        Model::cBoundingMode_Disable
    );

    mpModelB = BasicModel::create(
        const_cast<ModelResource*>(mpModelResource),
        model_name_b,
        0, 1, 2, 0, 0,
        Model::cBoundingMode_Disable
    );

    if (mType != TYPE_CB)
    {
        f32 frame =
            (mColor != COLOR_INVALID)
                ? mBaseFrame + s32(mColor)
                : -1.0f;

        if (frame != -1.0f)
        {
            mpModelA->getTexAnim(0)->play(mpModelResource, model_name_a);
            mpModelA->getTexAnim(0)->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
            mpModelA->getTexAnim(0)->getFrameCtrl().setFrame(frame);

            mpModelB->getTexAnim(0)->play(mpModelResource, model_name_b);
            mpModelB->getTexAnim(0)->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
            mpModelB->getTexAnim(0)->getFrameCtrl().setFrame(frame);
        }

        if (mType == TYPE_KAIGA)
        {
            mpModelA->getShuAnim(0)->playTexSrtAnim(mpModelResource, model_name_a);
            mpModelA->getShuAnim(0)->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
            mpModelA->getShuAnim(0)->getFrameCtrl().setFrame(frame);

            mpModelB->getShuAnim(0)->playTexSrtAnim(mpModelResource, model_name_b);
            mpModelB->getShuAnim(0)->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
            mpModelB->getShuAnim(0)->getFrameCtrl().setFrame(frame);
        }
    }
    else
    {
        mpModelA->getShuAnim(0)->playTexSrtAnim(mpModelResource, "obj_dokan_CB_wait");
        mpModelA->getShuAnim(0)->getFrameCtrl().setPlayMode(FrameCtrl::cMode_Repeat);
        mpModelA->getShuAnim(0)->getFrameCtrl().setFrame(0.0f);
        mpModelA->getShuAnim(0)->getFrameCtrl().setRate(1.0f);

        mpModelB->getShuAnim(0)->playTexSrtAnim(mpModelResource, "obj_dokan_CB_wait");
        mpModelB->getShuAnim(0)->getFrameCtrl().setPlayMode(FrameCtrl::cMode_Repeat);
        mpModelB->getShuAnim(0)->getFrameCtrl().setFrame(0.0f);
        mpModelB->getShuAnim(0)->getFrameCtrl().setRate(1.0f);

        mpModelA->getShuAnim(1)->playColorAnim(mpModelResource, "obj_dokan_CB_wait");
        mpModelA->getShuAnim(1)->getFrameCtrl().setPlayMode(FrameCtrl::cMode_Repeat);
        mpModelA->getShuAnim(1)->getFrameCtrl().setFrame(0.0f);
        mpModelA->getShuAnim(1)->getFrameCtrl().setRate(1.0f);

        mpModelB->getShuAnim(1)->playColorAnim(mpModelResource, "obj_dokan_CB_wait");
        mpModelB->getShuAnim(1)->getFrameCtrl().setPlayMode(FrameCtrl::cMode_Repeat);
        mpModelB->getShuAnim(1)->getFrameCtrl().setFrame(0.0f);
        mpModelB->getShuAnim(1)->getFrameCtrl().setRate(1.0f);
    }

    return true;
}

void ObjDokan::setModelItemID(ItemID item_id)
{
    if (!isCreated())
        return;

    mpModelA->getModel()->setItemID(item_id);
    mpModelB->getModel()->setItemID(item_id);
}

void ObjDokan::setModelSelection(bool is_selected)
{
    if (!isCreated())
        return;

    mpModelA->getModel()->setSelection(is_selected);
    mpModelB->getModel()->setSelection(is_selected);
}

void ObjDokan::destroy()
{
    if (!isCreated())
        return;

    BasicModel::destroy(mpModelA);
    mpModelA = nullptr;

    BasicModel::destroy(mpModelB);
    mpModelB = nullptr;

    const std::string& res_name = cResName[mType];

    ModelResMgr::instance()->destroyResFile(res_name);
    ResMgr::instance()->destroyArchiveRes(res_name);

    mpModelResource = nullptr;

    mType = TYPE_MAX;
    mLength = 0.0f;
    mIsEnableDrawA = false;
    mColor = COLOR_INVALID;
}

void ObjDokan::move(const rio::BaseVec3f& position)
{
    rio::Matrix34f& mtxRT = static_cast<rio::Matrix34f&>(mMtxRT);
    mtxRT.setTranslationWorld(static_cast<const rio::Vector3f&>(position));

    setModelMtxSRT_();
}

void ObjDokan::setModelMtxSRT_()
{
    rio::Matrix34f mtx = static_cast<const rio::Matrix34f&>(mMtxRT);
    mtx.applyTranslationLocal({ 0.0f, mLength * 0.5f, 0.0f });

    mpModelB->getModel()->setMtxRT(mtx);
    mpModelB->getModel()->setScale(static_cast<const rio::Vector3f&>(mScale));

    if (mType == TYPE_CB)
        mpModelB->updateAnimations();

    mpModelB->updateModel();

    if (mType == TYPE_KAIGA)
    {
        MaterialG3d* material = static_cast<MaterialG3d*>(mpModelB->getModel()->getMaterial(0));
        RIO_ASSERT(material);
        material->setTexSrtMtx(0, reinterpret_cast<const rio::Vector2f&>(mScale.x), 0, { 0.0f, (1 - mScale.y) * 0.5f });
    }

    if (mIsEnableDrawA)
    {
        mtx.applyTranslationLocal({ 0.0f, mLength * 0.5f, 0.0f });

        mpModelA->getModel()->setMtxRT(mtx);

        if (mType == TYPE_CB)
            mpModelA->updateAnimations();

        mpModelA->updateModel();
    }
}

void ObjDokan::onSceneUpdate() const
{
    if (mType == TYPE_CB)
    {
        mpModelB->updateAnimations();
        mpModelB->updateModel();

        if (mIsEnableDrawA)
        {
            mpModelA->updateAnimations();
            mpModelA->updateModel();
        }
    }
}

void ObjDokan::scheduleDraw() const
{
    Renderer::instance()->drawModel(*mpModelB);
    if (mIsEnableDrawA)
        Renderer::instance()->drawModel(*mpModelA);
}
