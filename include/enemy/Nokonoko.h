#pragma once

#include <item/MapActorItem.h>

#include <math/rio_MathTypes.h>

class BasicModel;
class ModelResource;

class Nokonoko : public MapActorItem
{
    MAP_ACTOR_ITEM_CREATE(Nokonoko)

public:
    Nokonoko(MapActorData& map_actor_data);
    virtual ~Nokonoko();

    void onDataChange(DataChangeFlag flag) override;
    void onSceneUpdate() override;
    void scheduleDraw() override;

private:
    bool drawBox_() const override
    {
        return mpModelResource == nullptr;
    }

    void updatePositionXY_()
    {
        mPosition.x =  f32(mMapActorData.offset.x +  8);
        mPosition.y = -f32(mMapActorData.offset.y + 16);
    }

    void updatePositionZ_()
    {
        mPosition.z = mMapActorData.layer == LAYER_1 ? 1500.0f : -2500.0f;
    }

    void setModelMtxRT_();

    void updateColor_();

private:
    const bool              cIsBig;

    const ModelResource*    mpModelResource;
    BasicModel*             mpModel;
    BasicModel*             mpShellModel;

    bool                    mIsAltColor;
    rio::BaseVec3f          mPosition;
};
