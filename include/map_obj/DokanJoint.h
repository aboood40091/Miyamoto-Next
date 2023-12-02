#pragma once

#include <item/MapActorItem.h>

#include <math/rio_MathTypes.h>

class ModelG3d;

class DokanJoint : public MapActorItem
{
    MAP_ACTOR_ITEM_CREATE(DokanJoint)

public:
    DokanJoint(MapActorData& map_actor_data, u32 index);
    virtual ~DokanJoint();

    void onDataChange(DataChangeFlag flag) override;
    void scheduleDraw() override;

private:
    bool drawBox_() const override
    {
        return mpModel == nullptr;
    }

    void updatePositionXY_()
    {
        mPosition.x =  f32(mMapActorData.offset.x + 16);
        mPosition.y = -f32(mMapActorData.offset.y + 16);
    }

    void updatePositionZ_()
    {
        switch (mMapActorData.layer)
        {
        case LAYER_0:
            mPosition.z = 3584.0f;
            break;
        case LAYER_2:
            mPosition.z = -3564.0f;
            break;
        default:
            mPosition.z = -64.0f;
            break;
        }
    }

    void setModelMtxRT_();

    void setModelItemID_();
    void setModelSelection_();

    void onIndexChange_() override { setModelItemID_(); }
    void onSelectionChange_() override { setModelSelection_(); }

private:
    ModelG3d*       mpModel;
    rio::BaseVec3f  mPosition;
};
