#pragma once

#include <item/MapActorItem.h>

#include <math/rio_MathTypes.h>

class BasicModel;

class Kuribo : public MapActorItem
{
    MAP_ACTOR_ITEM_CREATE(Kuribo)

public:
    Kuribo(MapActorData& map_actor_data, u32 index);
    virtual ~Kuribo();

    void onDataChange(DataChangeFlag flag) override;
    void onSceneUpdate() override;
    void scheduleDraw() override;

private:
    bool drawBox_() const override
    {
        return mpModel == nullptr;
    }

    void updatePositionXY_()
    {
        mPosition.x =  f32(mMapActorData.offset.x +  8);
        mPosition.y = -f32(mMapActorData.offset.y + 16);
    }

    void updatePositionZ_()
    {
        mPosition.z = mIsLayer2 ? -2500.0f : 1500.0f;
    }

    void setModelMtxRT_();

    void setModelItemID_();
    void setModelSelection_();

    void onIndexChange_() override { setModelItemID_(); }
    void onSelectionChange_() override { setModelSelection_(); }

private:
    const bool      cIsKakibo;

    BasicModel*     mpModel;

    bool            mIsLayer2;
    rio::BaseVec3f  mPosition;
};
