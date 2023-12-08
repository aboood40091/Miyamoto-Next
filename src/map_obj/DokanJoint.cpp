#include <MainWindow.h>
#include <graphics/ModelG3d.h>
#include <graphics/ModelResMgr.h>
#include <graphics/Renderer.h>
#include <map_obj/DokanJoint.h>
#include <resource/ResMgr.h>

static const std::string cResName = "obj_dokan_joint";

DokanJoint::DokanJoint(MapActorData& map_actor_data, u32 index)
    : MapActorItem(map_actor_data, index)
    , mpModel(nullptr)
{
    static const std::string archive_path = MainWindow::getContentPath() + "/Common/actor/" + cResName + ".szs";

    const SharcArchiveRes* archive_res = ResMgr::instance()->loadArchiveRes(cResName, archive_path, true);
    if (archive_res == nullptr)
        return;

    const ModelResource* model_res = ModelResMgr::instance()->loadResFile(cResName, archive_res, cResName.c_str());
    RIO_ASSERT(model_res);

    mpModel = ModelG3d::createG3d(
        *model_res,
        "obj_dokan_joint",
        0, 0, 0, 0, 0,
        Model::cBoundingMode_Disable
    );

    updatePositionXY_();
    updatePositionZ_();
    setModelMtxRT_();

    setModelItemID_();
}

DokanJoint::~DokanJoint()
{
    if (mpModel)
    {
        delete mpModel;

        ModelResMgr::instance()->destroyResFile(cResName);
        ResMgr::instance()->destroyArchiveRes(cResName);
    }
}

void DokanJoint::setModelItemID_()
{
    if (mpModel)
        mpModel->setItemID(mItemID);
}

void DokanJoint::setModelSelection_()
{
    if (mpModel)
        mpModel->setSelection(mIsSelected);
}

void DokanJoint::setModelMtxRT_()
{
    rio::Matrix34f mtx;
    mtx.makeT(static_cast<const rio::Vector3f&>(mPosition));

    mpModel->setMtxRT(mtx);
    mpModel->updateModel();
}

void DokanJoint::onDataChange(DataChangeFlag flag)
{
    bool position_changed = false;

    if (flag & DATA_CHANGE_FLAG_LAYER)
    {
        updatePositionZ_();
        position_changed = true;
    }

    if (flag & DATA_CHANGE_FLAG_OFFSET)
    {
        updatePositionXY_();
        position_changed = true;
    }

    if (position_changed)
        setModelMtxRT_();
}

void DokanJoint::scheduleDraw()
{
    if (mpModel == nullptr)
        return;

    Renderer::instance()->drawModel(mpModel);
}
