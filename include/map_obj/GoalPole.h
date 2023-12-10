#pragma once

#include <item/MapActorItem.h>

#include <math/rio_MathTypes.h>

class BasicModel;

class GoalPole : public MapActorItem
{
    MAP_ACTOR_ITEM_CREATE_DEFAULT(GoalPole)

public:
    GoalPole(const MapActorData& map_actor_data, u32 index);
    virtual ~GoalPole();

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
        mPosition.x =  f32(map_actor_data.offset.x);
        mPosition.y = -f32(map_actor_data.offset.y + 16);
    }

    void setModelMtxRT_();

    void updateFrame_();

    void setModelItemID_();
    void setModelSelection_();

    void onIndexChange_() override { setModelItemID_(); }
    void onSelectionChange_() override { MapActorItem::onSelectionChange_(); setModelSelection_(); }

private:
    const std::string*      mpResName;

    const ModelResource*    mpModelResource;
    BasicModel*             mpBaseModel;
    BasicModel*             mpGoalFlagModel;
    BasicModel*             mpTorideStdModel;

    const bool              cIsKaiga;
    s32                     mFrame;
    rio::BaseVec2f          mPosition;
};
