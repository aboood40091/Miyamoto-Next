#pragma once

#include <course/Constants.h>
#include <course/UnitID.h>
#include <graphics/RenderMgr.h>

#include <gpu/rio_RenderBuffer.h>
#include <gpu/rio_RenderTarget.h>

class Bg;
class CourseDataFile;
class RenderObjLayer;

class BgTexMgr : public rio::lyr::IDrawable
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

    void update();

    const rio::RenderBuffer& getTexRenderBuffer() const
    {
        return mTexRenderBuffer;
    }

private:
    void bindTexRenderBuffer_() const;
    void restoreFramebuffer_() const;

private:
    enum AnimeInfoType
    {
        ANIME_INFO_TYPE_HATENA = 0,
        ANIME_INFO_TYPE_BLOCK,
        ANIME_INFO_TYPE_TUKA_COIN,
        ANIME_INFO_TYPE_BELT_CONVEYOR,
        ANIME_INFO_TYPE_BELT_CONVEYOR_REVERSE,
        ANIME_INFO_TYPE_BELT_CONVEYOR_FAST,
        ANIME_INFO_TYPE_BELT_CONVEYOR_FAST_REVERSE,
        ANIME_INFO_TYPE_HATENA_L,
        ANIME_INFO_TYPE_BLOCK_L,
        ANIME_INFO_TYPE_MAX
    };
    static_assert(ANIME_INFO_TYPE_MAX == 9);

    struct AnimeInfo
    {
        bool        reverse;
        bool        square;
        const s32*  frame_delay;
        s32         frame_num;
        AnimeType   anim_type;
    };

    static const AnimeInfo cAnimeInfo[ANIME_INFO_TYPE_MAX];
    static const UnitID cAnimeInfoUnitID[ANIME_INFO_TYPE_MAX];

private:
    static void drawAnime_(UnitID unit, s32 frame, AnimeType type, bool square, const rio::BaseMtx44f& proj_mtx);
    void drawXlu_(const rio::lyr::DrawInfo& draw_info);

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
    s32                     mDelayTimer[ANIME_INFO_TYPE_MAX];
    s32                     mFrame[ANIME_INFO_TYPE_MAX];
};
