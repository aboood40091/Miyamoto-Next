#pragma once

#include <item/ItemID.h>

#include <gfx/rio_Camera.h>
#include <gfx/rio_Color.h>
#include <gfx/rio_Projection.h>
#include <gpu/rio_Shader.h>
#include <gpu/rio_TextureSampler.h>
#include <gpu/rio_VertexArray.h>
#include <math/rio_Matrix.h>

class QuadRenderer
{
    template <typename T>
    class ArgBase
    {
    public:
        ArgBase()
            : mCenter{ 0.0f, 0.0f, 0.0f }
            , mSize{ 1.0f, 1.0f }

            , mItemID(ItemID::cInvalidItemID)
            , mIsSelected(false)
        {
        }

        T& setCenter(const rio::BaseVec3f& p) { mCenter = p; return static_cast<T&>(*this); }
        T& setSize(const rio::BaseVec2f& size) { mSize = size; return static_cast<T&>(*this); }
        T& setCornerAndSize(const rio::BaseVec3f& p, const rio::BaseVec2f& size);

        T& setItemID(const ItemID& item_id) { mItemID = item_id; return static_cast<T&>(*this); }
        T& setSelection(bool is_selected) { mIsSelected = is_selected; return static_cast<T&>(*this); }

        const rio::BaseVec3f& getCenter() const { return mCenter; }
        const rio::BaseVec2f& getSize() const { return mSize; }

        const ItemID& getItemID() const { return mItemID; }
        bool isSelected() const { return mIsSelected; }

    protected:
        rio::BaseVec3f mCenter;
        rio::BaseVec2f mSize;

        ItemID mItemID;
        bool mIsSelected;
    };

public:
    class Arg : public ArgBase<Arg>
    {
    public:
        Arg(const rio::Color4f& color = rio::Color4f::cWhite)
            : mColor(color)
        {
        }

        const rio::Color4f& getColor() const { return mColor; }

    private:
        rio::Color4f mColor;
    };

    class TextureArg : public ArgBase<TextureArg>
    {
    public:
        TextureArg(const rio::Texture2D* texture)
            : mpTexture(texture)
        {
            RIO_ASSERT(texture);
        }

        const rio::Texture2D& getTexture() const { return *mpTexture; }

    private:
        const rio::Texture2D* mpTexture;
    };

public:
    static bool createSingleton();
    static void destroySingleton();
    static QuadRenderer* instance() { return sInstance; }

private:
    static QuadRenderer* sInstance;

    QuadRenderer();
    ~QuadRenderer();

    QuadRenderer(const QuadRenderer&);
    QuadRenderer& operator=(const QuadRenderer&);

private:
    void initialize_();

public:
    void setViewProjMtx(const rio::Camera& camera, const rio::Projection& projection)
    {
        rio::BaseMtx34f view_mtx;
        camera.getMatrix(&view_mtx);

        const rio::BaseMtx44f& proj_mtx = projection.getMatrix();

        setViewProjMtx(view_mtx, proj_mtx);
    }

    void setViewProjMtx(const rio::BaseMtx34f& view_mtx, const rio::BaseMtx44f& proj_mtx)
    {
        mViewProjMtx.setMul(static_cast<const rio::Matrix44f&>(proj_mtx), static_cast<const rio::Matrix34f&>(view_mtx));
    }

    void setViewProjMtx(const rio::BaseMtx44f& view_proj_mtx)
    {
        mViewProjMtx = static_cast<const rio::Matrix44f&>(view_proj_mtx);
    }

    void drawQuad(const Arg& arg);
    void drawQuad(const TextureArg& arg);
    void drawQuad(const TextureArg& arg, const rio::BaseVec2f& tex_scale, f32 tex_rotate, const rio::BaseVec2f& tex_trans);
    void drawBox(const Arg& arg);

private:
    void drawQuad_(const rio::BaseMtx44f& mvp_mtx, u32 item_id, bool is_selected, const rio::Color4f& color);
    void drawQuad_(const rio::BaseMtx44f& mvp_mtx, u32 item_id, bool is_selected, const rio::Texture2D& texture);
    void drawQuad_(const rio::BaseMtx44f& mvp_mtx, u32 item_id, bool is_selected, const rio::Texture2D& texture, const rio::BaseVec2f& tex_scale, f32 tex_rotate, const rio::BaseVec2f& tex_trans);
    void drawBox_(const rio::BaseMtx44f& mvp_mtx, u32 item_id, bool is_selected, const rio::Color4f& color);

    struct Vertex
    {
        rio::BaseVec3f pos;
        rio::BaseVec2f uv;
    };
    static_assert(sizeof(Vertex) == 0x14, "Vertex size mismatch");

    void drawTriangles_(const rio::BaseMtx44f& mvp_mtx, u32 item_id, bool is_selected, const rio::Color4f& c, Vertex* vtx, u32 vtx_num, u16* idx, u32 idx_num);
    void drawTriangles_(const rio::BaseMtx44f& mvp_mtx, u32 item_id, bool is_selected, const rio::Texture2D& texture, Vertex* vtx, u32 vtx_num, u16* idx, u32 idx_num);
    void drawTriangles_(const rio::BaseMtx44f& mvp_mtx, u32 item_id, bool is_selected, const rio::Texture2D& texture, const rio::BaseVec2f& tex_scale, f32 tex_rotate, const rio::BaseVec2f& tex_trans, Vertex* vtx, u32 vtx_num, u16* idx, u32 idx_num);
    void drawLines_(const rio::BaseMtx44f& mvp_mtx, u32 item_id, bool is_selected, const rio::Color4f& c, Vertex* vtx, u32 vtx_num, u16* idx, u32 idx_num);

    static inline void getQuadVertex(Vertex* vtx, u16* idx);

private:
    // View Projection
    rio::Matrix44f  mViewProjMtx;

    // Shader
    struct
    {
        rio::Shader shader;
        u32         mvp_uniform_loc;
        u32         item_id_uniform_loc;
        u32         is_selected_uniform_loc;
        u32         clr_uniform_loc;
    } mDrawClr;
    struct
    {
        rio::Shader shader;
        u32         mvp_uniform_loc;
        u32         item_id_uniform_loc;
        u32         is_selected_uniform_loc;
        u32         tex_sampler_loc;
    } mDrawTex;
    struct
    {
        rio::Shader shader;
        u32         mvp_uniform_loc;
        u32         tex_trans_uniform_loc;
        u32         tex_scale_uniform_loc;
        u32         tex_rotate_uniform_loc;
        u32         item_id_uniform_loc;
        u32         is_selected_uniform_loc;
        u32         tex_sampler_loc;
    } mDrawCrd;

    // Vertex Array Object
    rio::VertexArray        mVertexArray;

    // Vertex Buffer Object
    rio::VertexBuffer       mVertexBuffer;

    // Vertex Stream layouts
    rio::VertexStream       mPosStream;
    rio::VertexStream       mUVStream;

    // Quad Texture Sampler
    rio::TextureSampler2D   mDrawQuadSampler;

    // Quad, Box
    Vertex*                 mQuadVertexBuf;
    u16*                    mQuadIndexBuf;
    u16*                    mBoxIndexBuf;
};

template <typename T>
T& QuadRenderer::ArgBase<T>::setCornerAndSize(const rio::BaseVec3f& p, const rio::BaseVec2f& size)
{
    mCenter = p;
    reinterpret_cast<rio::Vector2f&>(mCenter.x) += static_cast<const rio::Vector2f&>(size) * 0.5f;
    mSize = size;
    return static_cast<T&>(*this);
}
