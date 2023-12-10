#pragma once

#include <item/MapActorItem.h>

#include <math/rio_MathTypes.h>

class BasicModel;
class ModelResource;

class Nokonoko : public MapActorItem
{
    MAP_ACTOR_ITEM_CREATE(Nokonoko)

public:
    Nokonoko(MapActorData& map_actor_data, u32 index);
    virtual ~Nokonoko();

    void onDataChange(const MapActorData& map_actor_data, DataChangeFlag flag) override;
    void onSceneUpdate() override;
    void scheduleDraw() override;

private:
    bool drawBox_() const override
    {
        return mpModelResource == nullptr;
    }

    void updatePositionXY_(const MapActorData& map_actor_data)
    {
        mPosition.x =  f32(map_actor_data.offset.x +  8);
        mPosition.y = -f32(map_actor_data.offset.y + 16);
    }

    void updatePositionZ_(const MapActorData& map_actor_data)
    {
        mPosition.z = map_actor_data.layer == LAYER_1 ? 1500.0f : -2500.0f;
    }

    void setModelMtxRT_();

    void updateColor_();

    void setModelItemID_();
    void setModelSelection_();

    void onIndexChange_() override { setModelItemID_(); }
    void onSelectionChange_() override { MapActorItem::onSelectionChange_(); setModelSelection_(); }

private:
    const bool              cIsBig;

    const ModelResource*    mpModelResource;
    BasicModel*             mpModel;
    BasicModel*             mpShellModel;

    bool                    mIsAltColor;
    rio::BaseVec3f          mPosition;
};
