#pragma once

#include <item/MapActorItem.h>

class BasicModel;
class TexturePatternAnimation;

class Kuribo : public MapActorItem
{
    MAP_ACTOR_ITEM_CREATE(Kuribo)

public:
    Kuribo(MapActorData& map_actor_data);
    virtual ~Kuribo();

    void update() override;
    void scheduleDraw() override;

private:
    bool drawBox_() const override
    {
        return mpModel == nullptr;
    }

    f32 getZPos_() const
    {
        return (mMapActorData.settings[0] >> 16 & 1) ? -2500.0f : 1500.0f;
    }

private:
    bool                        mIsKakibo;
    BasicModel*                 mpModel;
    TexturePatternAnimation*    mpTexAnim;
};
