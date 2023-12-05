#pragma once

#include <course/Constants.h>
#include <course/UnitID.h>
#include <item/ItemID.h>

#include <gfx/rio_Camera.h>
#include <gfx/rio_Projection.h>
#include <gpu/rio_Shader.h>
#include <gpu/rio_TextureSampler.h>
#include <gpu/rio_VertexArray.h>

//#include <array>
#include <span>
#include <vector>

class Bg;
class CourseDataFile;

class BgRenderer
{
public:
    static bool createSingleton();
    static void destroySingleton();
    static BgRenderer* instance() { return sInstance; }

private:
    static BgRenderer* sInstance;

    BgRenderer();
    ~BgRenderer();

    BgRenderer(const BgRenderer&);
    BgRenderer& operator=(const BgRenderer&);

public:
    void setCamera(rio::Camera* p_camera)
    {
        RIO_ASSERT(p_camera != nullptr);
        mpCamera = p_camera;
    }

    void setProjection(rio::Projection* p_projection)
    {
        RIO_ASSERT(p_projection != nullptr);
        mpProjection = p_projection;
    }

    void createVertexBuffer(u8 layer);

    void createVertexBuffer()
    {
        createVertexBuffer(LAYER_0);
        createVertexBuffer(LAYER_1);
        createVertexBuffer(LAYER_2);
    }

    void drawUnit(ItemID item_id, const rio::BaseVec3f& tl_pos, UnitID unit, u8 layer);

    void calcSelectionVertexBuffer(const std::vector<ItemID>& selected_items);

    void render(u8 layer, const CourseDataFile& cd_file, bool render_static, bool render_dynamic = true, bool render_normal = false);

private:
    void initialize_();
    void destroy_();

    struct Vertex
    {
        rio::BaseVec3f  pos;
        rio::BaseVec2f  tex;
        ItemID          item_id;
    };

    void setUnitVertexBuffer_(Vertex* vtx_data, const rio::BaseVec3f& tl_pos, u8 unit_idx, ItemID item_id);

    static constexpr s32 cVtxPerBlock = 4;
    static constexpr s32 cIdxPerBlock = 6;

    static constexpr s32 cUnitSize          = 60;
    static constexpr s32 cUnitSizePad       = 64;

    static constexpr s32 cPad               = (cUnitSizePad - cUnitSize) / 2;

    static constexpr s32 cTextureWidth      = 2048;
    static constexpr s32 cTextureHeight     = 512;

    static constexpr s32 cUnitsPerRow       = cTextureWidth  / cUnitSizePad;
    static constexpr s32 cUnitsPerColumn    = cTextureHeight / cUnitSizePad;

    static constexpr f32 cUnitSizePadXNorm  = f32(cUnitSizePad) / cTextureWidth;
    static constexpr f32 cUnitSizePadYNorm  = f32(cUnitSizePad) / cTextureHeight;

    static constexpr f32 cPadXNorm          = f32(cPad) / cTextureWidth;
    static constexpr f32 cPadYNorm          = f32(cPad) / cTextureHeight;

    static constexpr s32 cDynamicMaxNum = 0x800;

private:
    std::span<Vertex>       mVtxData;
    std::span<   s32>       mSelData;
    std::span<   u32>       mIdxData;

    rio::Shader             mShader;
    rio::VertexBuffer       mVertexBuffer;
    rio::VertexBuffer       mSelectionVertexBuffer;
    rio::VertexStream       mPosStream;
    rio::VertexStream       mTexStream;
    rio::VertexStream       mItemIDStream;
    rio::VertexStream       mIsSelectedStream;
    rio::VertexArray        mVertexArray;

    rio::Camera*            mpCamera;
    rio::Projection*        mpProjection;
    u32                     mMVPLocation;

    rio::TextureSampler2D   mTextureSampler;
    u32                     mTexLocation;

    u32                     mDrawNum[CD_FILE_LAYER_MAX_NUM][CD_FILE_ENV_MAX_NUM];
    u32                     mDynamicDrawNum[CD_FILE_LAYER_MAX_NUM][CD_FILE_ENV_MAX_NUM];
};
