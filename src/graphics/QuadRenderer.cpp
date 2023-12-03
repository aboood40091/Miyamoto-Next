#include <graphics/QuadRenderer.h>

#include <gpu/rio_Drawer.h>
#include <math/rio_Matrix.h>
#include <misc/rio_MemUtil.h>

QuadRenderer* QuadRenderer::sInstance = nullptr;

bool QuadRenderer::createSingleton()
{
    if (sInstance)
        return false;

    sInstance = new QuadRenderer();
    return true;
}

void QuadRenderer::destroySingleton()
{
    if (!sInstance)
        return;

    delete sInstance;
    sInstance = nullptr;
}

QuadRenderer::QuadRenderer()
{
    initialize_();
}

QuadRenderer::~QuadRenderer()
{
    rio::MemUtil::free(mQuadVertexBuf);
    rio::MemUtil::free(mQuadIndexBuf);
    rio::MemUtil::free(mBoxIndexBuf);
}

void QuadRenderer::initialize_()
{
    mDrawClr.shader.load("quad_renderer_color", rio::Shader::MODE_UNIFORM_REGISTER);
    mDrawTex.shader.load("quad_renderer_texture", rio::Shader::MODE_UNIFORM_REGISTER);
    mDrawCrd.shader.load("quad_renderer_texture_texcoord", rio::Shader::MODE_UNIFORM_REGISTER);

    // uMVP
    {
        mDrawClr.mvp_uniform_loc = mDrawClr.shader.getVertexUniformLocation("uMVP");
        RIO_ASSERT(mDrawClr.mvp_uniform_loc != 0xFFFFFFFF);
        mDrawTex.mvp_uniform_loc = mDrawTex.shader.getVertexUniformLocation("uMVP");
        RIO_ASSERT(mDrawTex.mvp_uniform_loc != 0xFFFFFFFF);
        mDrawCrd.mvp_uniform_loc = mDrawCrd.shader.getVertexUniformLocation("uMVP");
        RIO_ASSERT(mDrawCrd.mvp_uniform_loc != 0xFFFFFFFF);
    }
    // uTexTrans
    {
        mDrawCrd.tex_trans_uniform_loc = mDrawCrd.shader.getVertexUniformLocation("uTexTrans");
        RIO_ASSERT(mDrawCrd.tex_trans_uniform_loc != 0xFFFFFFFF);
    }
    // uTexScale
    {
        mDrawCrd.tex_scale_uniform_loc = mDrawCrd.shader.getVertexUniformLocation("uTexScale");
        RIO_ASSERT(mDrawCrd.tex_scale_uniform_loc != 0xFFFFFFFF);
    }
    // uTexRotate
    {
        mDrawCrd.tex_rotate_uniform_loc = mDrawCrd.shader.getVertexUniformLocation("uTexRotate");
        RIO_ASSERT(mDrawCrd.tex_rotate_uniform_loc != 0xFFFFFFFF);
    }
    // uItemID
    {
        mDrawClr.item_id_uniform_loc = mDrawClr.shader.getFragmentUniformLocation("uItemID");
        RIO_ASSERT(mDrawClr.item_id_uniform_loc != 0xFFFFFFFF);
        mDrawTex.item_id_uniform_loc = mDrawTex.shader.getFragmentUniformLocation("uItemID");
        RIO_ASSERT(mDrawTex.item_id_uniform_loc != 0xFFFFFFFF);
        mDrawCrd.item_id_uniform_loc = mDrawCrd.shader.getFragmentUniformLocation("uItemID");
        RIO_ASSERT(mDrawCrd.item_id_uniform_loc != 0xFFFFFFFF);
    }
    // uIsSelected
    {
        mDrawClr.is_selected_uniform_loc = mDrawClr.shader.getFragmentUniformLocation("uIsSelected");
        RIO_ASSERT(mDrawClr.is_selected_uniform_loc != 0xFFFFFFFF);
        mDrawTex.is_selected_uniform_loc = mDrawTex.shader.getFragmentUniformLocation("uIsSelected");
        RIO_ASSERT(mDrawTex.is_selected_uniform_loc != 0xFFFFFFFF);
        mDrawCrd.is_selected_uniform_loc = mDrawCrd.shader.getFragmentUniformLocation("uIsSelected");
        RIO_ASSERT(mDrawCrd.is_selected_uniform_loc != 0xFFFFFFFF);
    }
    // uColor
    {
        mDrawClr.clr_uniform_loc = mDrawClr.shader.getFragmentUniformLocation("uColor");
        RIO_ASSERT(mDrawClr.clr_uniform_loc != 0xFFFFFFFF);
    }
    // sTexture
    {
        mDrawTex.tex_sampler_loc = mDrawTex.shader.getFragmentSamplerLocation("sTexture");
        RIO_ASSERT(mDrawTex.tex_sampler_loc != 0xFFFFFFFF);
        mDrawCrd.tex_sampler_loc = mDrawCrd.shader.getFragmentSamplerLocation("sTexture");
        RIO_ASSERT(mDrawCrd.tex_sampler_loc != 0xFFFFFFFF);
    }

    mPosStream.setLayout(0, rio::VertexStream::FORMAT_32_32_32_FLOAT, offsetof(Vertex, pos));
    mUVStream .setLayout(1, rio::VertexStream::FORMAT_32_32_FLOAT,    offsetof(Vertex, uv));

    mVertexBuffer.setStride(sizeof(Vertex));

    mVertexArray.initialize();
    mVertexArray.addAttribute(mPosStream, mVertexBuffer);
    mVertexArray.addAttribute(mUVStream,  mVertexBuffer);
    mVertexArray.process();

    {
        // Quad
        mQuadVertexBuf = static_cast<Vertex*>(rio::MemUtil::alloc(4 * sizeof(Vertex), rio::Drawer::cVtxAlignment));
        mQuadIndexBuf  = static_cast<   u16*>(rio::MemUtil::alloc(6 * sizeof(   u16), rio::Drawer::cIdxAlignment));

        getQuadVertex(mQuadVertexBuf, mQuadIndexBuf);

        rio::VertexBuffer::invalidateCache(mQuadVertexBuf, 4 * sizeof(Vertex));
        rio::VertexBuffer::invalidateCache(mQuadIndexBuf,  6 * sizeof(   u16));

        // Box
        mBoxIndexBuf   = static_cast<   u16*>(rio::MemUtil::alloc(4 * sizeof(   u16), rio::Drawer::cIdxAlignment));

        static const u16 idx[4] = { 0, 1, 3, 2 };
        rio::MemUtil::copy(mBoxIndexBuf, idx, sizeof(idx));

        rio::VertexBuffer::invalidateCache(mBoxIndexBuf,   4 * sizeof(   u16));
    }

    mDrawQuadSampler.setWrap(rio::TEX_WRAP_MODE_CLAMP,
                             rio::TEX_WRAP_MODE_CLAMP,
                             rio::TEX_WRAP_MODE_CLAMP);

    mDrawQuadSampler.setFilter(rio::TEX_XY_FILTER_MODE_LINEAR,
                               rio::TEX_XY_FILTER_MODE_LINEAR,
                               rio::TEX_MIP_FILTER_MODE_NONE,
                               rio::TEX_ANISO_1_TO_1);
}

void QuadRenderer::drawQuad(const Arg& arg)
{
    rio::Matrix34f mtx;
    mtx.makeST(
        { arg.getSize().x, arg.getSize().y, 1.0f },
        arg.getCenter()
    );

    rio::Matrix44f mvp;
    mvp.setMul(mViewProjMtx, mtx);

    drawQuad_(mvp, arg.getItemID(), arg.isSelected(), arg.getColor());
}

void QuadRenderer::drawQuad(const TextureArg& arg)
{
    rio::Matrix34f mtx;
    mtx.makeST(
        { arg.getSize().x, arg.getSize().y, 1.0f },
        arg.getCenter()
    );

    rio::Matrix44f mvp;
    mvp.setMul(mViewProjMtx, mtx);

    drawQuad_(mvp, arg.getItemID(), arg.isSelected(), arg.getTexture());
}

void QuadRenderer::drawQuad(const TextureArg& arg, const rio::BaseVec2f& tex_scale, f32 tex_rotate, const rio::BaseVec2f& tex_trans)
{
    rio::Matrix34f mtx;
    mtx.makeST(
        { arg.getSize().x, arg.getSize().y, 1.0f },
        arg.getCenter()
    );

    rio::Matrix44f mvp;
    mvp.setMul(mViewProjMtx, mtx);

    drawQuad_(mvp, arg.getItemID(), arg.isSelected(), arg.getTexture(), tex_scale, tex_rotate, tex_trans);
}

void QuadRenderer::drawBox(const Arg& arg)
{
    rio::Matrix34f mtx;
    mtx.makeST(
        { arg.getSize().x, arg.getSize().y, 1.0f },
        arg.getCenter()
    );

    rio::Matrix44f mvp;
    mvp.setMul(mViewProjMtx, mtx);

    drawBox_(mvp, arg.getItemID(), arg.isSelected(), arg.getColor());
}

void QuadRenderer::drawQuad_(
    const rio::BaseMtx44f& mvp_mtx,
    u32 item_id, bool is_selected,
    const rio::Color4f& color
)
{
    drawTriangles_(mvp_mtx, item_id, is_selected, color, mQuadVertexBuf, 4, mQuadIndexBuf, 6);
}

void QuadRenderer::drawQuad_(
    const rio::BaseMtx44f& mvp_mtx,
    u32 item_id, bool is_selected,
    const rio::Texture2D& texture
)
{
    drawTriangles_(mvp_mtx, item_id, is_selected, texture, mQuadVertexBuf, 4, mQuadIndexBuf, 6);
}

void QuadRenderer::drawQuad_(
    const rio::BaseMtx44f& mvp_mtx,
    u32 item_id, bool is_selected,
    const rio::Texture2D& texture, const rio::BaseVec2f& tex_scale, f32 tex_rotate, const rio::BaseVec2f& tex_trans
)
{
    drawTriangles_(mvp_mtx, item_id, is_selected, texture, tex_scale, tex_rotate, tex_trans, mQuadVertexBuf, 4, mQuadIndexBuf, 6);
}

void QuadRenderer::drawBox_(
    const rio::BaseMtx44f& mvp_mtx,
    u32 item_id, bool is_selected,
    const rio::Color4f& color
)
{
    drawLines_(mvp_mtx, item_id, is_selected, color, mQuadVertexBuf, 4, mBoxIndexBuf, 4);
}

void QuadRenderer::drawTriangles_(
    const rio::BaseMtx44f& mvp_mtx,
    u32 item_id, bool is_selected,
    const rio::Color4f& c,
    Vertex* vtx, u32 vtx_num, u16* idx, u32 idx_num
)
{
    if (c.a < 0.0625f)
        return;

    mDrawClr.shader.bind();

    mDrawClr.shader.setUniformArray(4, mvp_mtx.v, mDrawClr.mvp_uniform_loc, 0xFFFFFFFF);

    mDrawClr.shader.setUniform(item_id, 0xFFFFFFFF, mDrawClr.item_id_uniform_loc);
    mDrawClr.shader.setUniform(is_selected, 0xFFFFFFFF, mDrawClr.is_selected_uniform_loc);

    mDrawClr.shader.setUniform(c.v, 0xFFFFFFFF, mDrawClr.clr_uniform_loc);

    mVertexBuffer.setData(vtx, vtx_num * sizeof(Vertex));
    mVertexArray.bind();

    rio::Drawer::DrawElements(rio::Drawer::TRIANGLES, idx_num, idx);
}

void QuadRenderer::drawTriangles_(
    const rio::BaseMtx44f& mvp_mtx,
    u32 item_id, bool is_selected,
    const rio::Texture2D& texture,
    Vertex* vtx, u32 vtx_num, u16* idx, u32 idx_num
)
{
    mDrawTex.shader.bind();

    mDrawTex.shader.setUniformArray(4, mvp_mtx.v, mDrawTex.mvp_uniform_loc, 0xFFFFFFFF);

    mDrawTex.shader.setUniform(item_id, 0xFFFFFFFF, mDrawTex.item_id_uniform_loc);
    mDrawTex.shader.setUniform(is_selected, 0xFFFFFFFF, mDrawTex.is_selected_uniform_loc);

    mDrawQuadSampler.linkTexture2D(&texture);
    mDrawQuadSampler.bindFS(mDrawTex.tex_sampler_loc, 0);

    mVertexBuffer.setData(vtx, vtx_num * sizeof(Vertex));
    mVertexArray.bind();

    rio::Drawer::DrawElements(rio::Drawer::TRIANGLES, idx_num, idx);
}

void QuadRenderer::drawTriangles_(
    const rio::BaseMtx44f& mvp_mtx,
    u32 item_id, bool is_selected,
    const rio::Texture2D& texture, const rio::BaseVec2f& tex_scale, f32 tex_rotate, const rio::BaseVec2f& tex_trans,
    Vertex* vtx, u32 vtx_num, u16* idx, u32 idx_num
)
{
    mDrawCrd.shader.bind();

    mDrawCrd.shader.setUniformArray(4, mvp_mtx.v, mDrawCrd.mvp_uniform_loc, 0xFFFFFFFF);
    mDrawCrd.shader.setUniform(tex_scale, mDrawCrd.tex_scale_uniform_loc, 0xFFFFFFFF);
    mDrawCrd.shader.setUniform(tex_rotate, mDrawCrd.tex_rotate_uniform_loc, 0xFFFFFFFF);
    mDrawCrd.shader.setUniform(tex_trans, mDrawCrd.tex_trans_uniform_loc, 0xFFFFFFFF);

    mDrawCrd.shader.setUniform(item_id, 0xFFFFFFFF, mDrawCrd.item_id_uniform_loc);
    mDrawCrd.shader.setUniform(is_selected, 0xFFFFFFFF, mDrawCrd.is_selected_uniform_loc);

    mDrawQuadSampler.linkTexture2D(&texture);
    mDrawQuadSampler.bindFS(mDrawCrd.tex_sampler_loc, 0);

    mVertexBuffer.setData(vtx, vtx_num * sizeof(Vertex));
    mVertexArray.bind();

    rio::Drawer::DrawElements(rio::Drawer::TRIANGLES, idx_num, idx);
}

void QuadRenderer::drawLines_(
    const rio::BaseMtx44f& mvp_mtx,
    u32 item_id, bool is_selected,
    const rio::Color4f& c,
    Vertex* vtx, u32 vtx_num, u16* idx, u32 idx_num
)
{
    if (c.a < 0.0625f)
        return;

    mDrawClr.shader.bind();

    mDrawClr.shader.setUniformArray(4, mvp_mtx.v, mDrawClr.mvp_uniform_loc, 0xFFFFFFFF);

    mDrawClr.shader.setUniform(item_id, 0xFFFFFFFF, mDrawClr.item_id_uniform_loc);
    mDrawClr.shader.setUniform(is_selected, 0xFFFFFFFF, mDrawClr.is_selected_uniform_loc);

    mDrawClr.shader.setUniform(c.v, 0xFFFFFFFF, mDrawClr.clr_uniform_loc);

    mVertexBuffer.setData(vtx, vtx_num * sizeof(Vertex));
    mVertexArray.bind();

    rio::Drawer::DrawElements(rio::Drawer::LINE_LOOP, idx_num, idx);
}

void QuadRenderer::getQuadVertex(Vertex* vtx, u16* idx)
{
    static const Vertex cVtx[4] = {
        { { -0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f } },
        { {  0.5f,  0.5f, 0.0f }, { 1.0f, 0.0f } },
        { { -0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f } },
        { {  0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f } }
    };

    static const u16 cIdx[6] = {
        0, 2, 1,
        1, 2, 3
    };

    if (vtx)
        rio::MemUtil::copy(vtx, cVtx, sizeof(cVtx));

    if (idx)
        rio::MemUtil::copy(idx, cIdx, sizeof(cIdx));
}
