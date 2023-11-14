#pragma once

#include <graphics/ModelResource.h>
#include <resource/SharcArchiveRes.h>

#include <gfx/rio_Projection.h>
#include <gfx/lyr/rio_Drawable.h>

#include <string>

class ModelG3d;
class RenderObjLayer;

class CoinOrigin : public rio::lyr::IDrawable
{
public:
    static bool createSingleton();
    static void destroySingleton();
    static CoinOrigin* instance() { return sInstance; }

private:
    static CoinOrigin* sInstance;

    CoinOrigin();
    ~CoinOrigin();

    CoinOrigin(const CoinOrigin&);
    CoinOrigin& operator=(const CoinOrigin&);

public:
    bool initialize(const std::string& pack_arc_path);

    void pushBackDrawMethod(RenderObjLayer* p_bg_prepare_layer);

    void update();
    void draw(RenderObjLayer* p_bg_prepare_layer);

    f32 getCoinAngle() const
    {
        return mCoinAngle * rio::Mathf::pi() / 0x80000000;
    }

private:
    void calcMdl_();

    void apply_(const rio::lyr::DrawInfo& draw_info);

private:
    bool                    mIsInitialized;
    void*                   mpArchive;
    SharcArchiveRes         mArchiveRes;
    ModelResource           mModelResource;

    u32                     mCoinAngle;
    ModelG3d*               mpModelCoin;
    ModelG3d*               mpModelBlueCoin;
    rio::OrthoProjection    mProjection;
};
