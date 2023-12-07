#pragma once

#include <course/BgUnitFile.h>
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
    enum OverridesType
    {
        OVERRIDES_NORMAL = 0,
        OVERRIDES_FOREST,
        OVERRIDES_SKY,
        OVERRIDES_UNDERGROUND,
        OVERRIDES_MAX
    };

    enum ItemType
    {
        ITEM_COIN = 0,
        ITEM_FIRE_FLOWER,
        ITEM_PROPELLER,
        ITEM_PENGUIN,
        ITEM_MINI_MUSHROOM,
        ITEM_STAR,
        ITEM_COIN_STAR,
        ITEM_YOSHI_EGG,
        ITEM_COIN_10,
        ITEM_1UP,
        ITEM_VINE,
        ITEM_SPRING,
        ITEM_COIN_MUSHROOM,
        ITEM_ICE_FLOWER,
        ITEM_ACORN,
        ITEM_MAX
    };
    static_assert(ITEM_MAX == 15);

    using UnitObjTex = std::unique_ptr<rio::Texture2D>;
    using UnitObjTexVector = std::vector<UnitObjTex>;
    using UnitObjTexArray = std::array<UnitObjTexVector, CD_FILE_ENV_MAX_NUM>;

public:
    void initialize(const CourseDataFile& cd_file, RenderObjLayer* p_bg_prepare_layer);
    void destroy(RenderObjLayer* p_bg_prepare_layer);

    void update();

    bool isReady() const
    {
        return mBgUnitFile[0] && mBgUnitFile[0]->getTexture();
    }

    const rio::Texture2D& getTexColor() const
    {
        return mTexColor;
    }

    const rio::RenderBuffer& getTexRenderBuffer() const
    {
        return mTexRenderBuffer;
    }

    void setCurrentOverridesType(OverridesType type)
    {
        mOverridesType = type;
        mOverridesDrawn = false;
    }

    const rio::Texture2D& getItemsTexture() const
    {
        return mItemsTexture;
    }

    const UnitObjTexArray& getUnitObjTexArray() const
    {
        return mUnitObjTexArray;
    }

private:
    void bindTexRenderBuffer_() const;
    static void restoreFramebuffer_();

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

    struct ItemOverrideInfo
    {
        AnimeInfoType   anime_info_type;
        UnitID          unit;
        ItemType        item_type;
    };

    static const s32 cItemOverrideNum = 23;
    static const ItemOverrideInfo cItemOverrideInfo[cItemOverrideNum];

private:
    void drawXlu_(const rio::lyr::DrawInfo& draw_info);

    void createUnitDefaultRender_();
    void doUnitDefaultRender_();
    void clearUnitDefaultRender_();

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
    rio::Texture2D          mTexColor;
    rio::RenderTargetDepth  mTexDepthTarget;
    rio::Texture2D          mTexDepth;
    const BgUnitFile*       mBgUnitFile[CD_FILE_ENV_MAX_NUM];
    s32                     mDelayTimer[ANIME_INFO_TYPE_MAX];
    s32                     mFrame[ANIME_INFO_TYPE_MAX];
    rio::Texture2D*         mOverrides[OVERRIDES_MAX];
    OverridesType           mOverridesType;
    bool                    mOverridesDrawn;
    rio::Texture2D          mItemsTexture;
    UnitObjTexArray         mUnitObjTexArray;
};
