#pragma once

#include <item/MapActorItem.h>

#include <math/rio_MathTypes.h>

class BasicModel;

class GoalPole : public MapActorItem
{
    MAP_ACTOR_ITEM_CREATE(GoalPole)

public:
    GoalPole(MapActorData& map_actor_data, u32 index);
    virtual ~GoalPole();

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
        mPosition.x =  f32(mMapActorData.offset.x);
        mPosition.y = -f32(mMapActorData.offset.y + 16);
    }

    void setModelMtxRT_();

    void updateFrame_();

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
