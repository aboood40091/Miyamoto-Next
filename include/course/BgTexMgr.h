#pragma once

#include <graphics/RenderMgr.h>

#include <gpu/rio_RenderBuffer.h>
#include <gpu/rio_RenderTarget.h>

class Bg;
class CourseDataFile;
class RenderObjLayer;

class BgTexMgr
{
public:
    static bool createSingleton();
    static void destroySingleton();
    static BgTexMgr* instance() { return sInstance; }

private:
    static BgTexMgr* sInstance;

    BgTexMgr();
    ~BgTexMgr();

    BgTexMgr(const BgTexMgr&);
    BgTexMgr& operator=(const BgTexMgr&);

public:
    void initialize(const Bg& bg, const CourseDataFile& cd_file, RenderObjLayer* p_bg_prepare_layer);
    void destroy(RenderObjLayer* p_bg_prepare_layer);

    const rio::RenderBuffer& getTexRenderBuffer() const
    {
        return mTexRenderBuffer;
    }

private:
    class DrawCallback : public RenderMgr::CallbackBase
    {
    public:
        DrawCallback(BgTexMgr& bg_tex_mgr)
            : mBgTexMgr(bg_tex_mgr)
        {
        }

        void preDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info) override;
        void preDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info) override;
        void postDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info) override;
        void postDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info) override;

    private:
        BgTexMgr&   mBgTexMgr;
    };

    DrawCallback            mDrawCallback;
    rio::RenderBuffer       mTexRenderBuffer;
    rio::RenderTargetColor  mTexColorTarget;
    rio::RenderTargetDepth  mTexDepthTarget;
    rio::Texture2D          mTexDepth;
};
