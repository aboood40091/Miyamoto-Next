#pragma once

#include <graphics/GridType.h>

#include <gfx/rio_Color.h>
#include <gpu/rio_Shader.h>
#include <gpu/rio_VertexArray.h>
#include <gpu/rio_VertexBuffer.h>
#include <math/rio_Matrix.h>
#include <math/rio_Vector.h>

class GridRenderer
{
public:
    static bool createSingleton();
    static void destroySingleton();
    static GridRenderer* instance() { return sInstance; }

private:
    static GridRenderer* sInstance;

    GridRenderer();
    ~GridRenderer();

    GridRenderer(const GridRenderer&);
    GridRenderer& operator=(const GridRenderer&);

public:
    void draw(
        const rio::BaseMtx44f&  view_proj_mtx,
        const rio::BaseVec2f&   world_min,
        const rio::BaseVec2f&   world_max,
        f32                     pixels_per_unit,
        GridType                type
    );

private:
    void initialize_();

    struct Vertex
    {
        rio::BaseVec3f pos;
    };

    rio::Shader         mShader;
    rio::VertexBuffer   mVertexBuffer;
    rio::VertexStream   mPosStream;
    rio::VertexArray    mVertexArray;

    Vertex*             mVertexBuf;
    u16*                mIndexBuf;

    u32                 mMVPUniformLoc;
    u32                 mColorUniformLoc;
    u32                 mPixelsPerUnitUniformLoc;
    u32                 mModeUniformLoc;
};
