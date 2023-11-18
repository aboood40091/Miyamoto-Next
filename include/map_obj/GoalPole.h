#pragma once

#include <item/MapActorItem.h>

class BasicModel;
class ShaderParamAnimation;
class TexturePatternAnimation;
class VisibilityAnimation;

class GoalPole : public MapActorItem
{
    MAP_ACTOR_ITEM_CREATE(GoalPole)

public:
    GoalPole(MapActorData& map_actor_data);
    virtual ~GoalPole();

    void update() override;
    void scheduleDraw() override;

private:
    bool drawBox_() const override
    {
        return mBase.p_model == nullptr;
    }

private:
    const std::string* mpResName;
    struct
    {
        BasicModel*                 p_model;
        TexturePatternAnimation*    p_tex_anim;
    } mBase;
    struct
    {
        BasicModel*                 p_model;
        TexturePatternAnimation*    p_tex_anim;
        ShaderParamAnimation*       p_shu_anim;
    } mGoalFlag;
    struct
    {
        BasicModel*                 p_model;
        TexturePatternAnimation*    p_tex_anim;
        VisibilityAnimation*       p_vis_anim;
    } mTorideStd;
};
