#pragma once

#include <course/Constants.h>

#include <gfx/rio_Camera.h>
#include <gfx/rio_Projection.h>
#include <gpu/rio_Shader.h>
#include <gpu/rio_TextureSampler.h>
#include <gpu/rio_VertexArray.h>

#include <gsl/span>
//#include <array>

class Bg;
class CourseDataFile;

class BgRenderer
{
public:
    BgRenderer();
    ~BgRenderer();

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

    void createVertexBuffer(u8 layer, const Bg& bg);

    void createVertexBuffer(const Bg& bg)
    {
        createVertexBuffer(LAYER_0, bg);
        createVertexBuffer(LAYER_1, bg);
        createVertexBuffer(LAYER_2, bg);
    }

    void render(u8 layer, const Bg& bg, const CourseDataFile& cd_file);

private:
    void initialize_();
    void destroy_();

    struct Vertex
    {
        rio::BaseVec3f  pos;
        rio::BaseVec2f  tex;
    };

    static constexpr s32 cVtxPerBlock = 4;
    static constexpr s32 cIdxPerBlock = 6;

    static constexpr s32 cTileSize          = 60;
    static constexpr s32 cTileSizePad       = 64;

    static constexpr s32 cPad               = (cTileSizePad - cTileSize) / 2;

    static constexpr s32 cTilesetWidth      = 2048;
    static constexpr s32 cTilesetHeight     = 512;

    static constexpr s32 cTilesPerRow       = cTilesetWidth  / cTileSizePad;
    static constexpr s32 cTilesPerColumn    = cTilesetHeight / cTileSizePad;

    static constexpr f32 cTileSizePadXNorm  = f32(cTileSizePad) / cTilesetWidth;
    static constexpr f32 cTileSizePadYNorm  = f32(cTileSizePad) / cTilesetHeight;

    static constexpr f32 cPadXNorm          = f32(cPad) / cTilesetWidth;
    static constexpr f32 cPadYNorm          = f32(cPad) / cTilesetHeight;

private:
    gsl::span<Vertex>       mVtxData;
    gsl::span<   u32>       mIdxData;

    rio::Shader             mShader;
    rio::VertexBuffer       mVertexBuffer;
    rio::VertexStream       mPosStream;
    rio::VertexStream       mTexStream;
    rio::VertexArray        mVertexArray;

    rio::Camera*            mpCamera;
    rio::Projection*        mpProjection;
    u32                     mMVPLocation;

    rio::TextureSampler2D   mTextureSampler;
    u32                     mTexLocation;

    u32                     mDrawNum[CD_FILE_LAYER_MAX_NUM][CD_FILE_ENV_MAX_NUM];
};
