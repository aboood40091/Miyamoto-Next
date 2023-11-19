#pragma once

#include <math/rio_MathTypes.h>

class BasicModel;
class ShaderParamAnimation;
class TexturePatternAnimation;

class ObjDokan
{
public:
    enum Type
    {
        TYPE_NORMAL = 0,
        TYPE_KAIGA,
        TYPE_MAME,
        TYPE_BIG,
        TYPE_CB,
        TYPE_MAX
    };
    static_assert(TYPE_MAX == 5);

    enum Direction
    {
        DIRECTION_RIGHT = 0,
        DIRECTION_LEFT,
        DIRECTION_UP,
        DIRECTION_DOWN,
        DIRECTION_MAX
    };
    static_assert(DIRECTION_MAX == 4);

    enum Color
    {
        COLOR_INVALID = -1
    };

public:
    ObjDokan(Direction dir, Type type, f32 length, bool a_visible, Color color = COLOR_INVALID);
    ~ObjDokan();

    ObjDokan(const ObjDokan&) = delete;
    ObjDokan(ObjDokan&&) = delete;
    ObjDokan& operator=(const ObjDokan&) = delete;
    ObjDokan& operator=(ObjDokan&&) = delete;

    bool isCreated() const
    {
        return mA.p_model;
    }

    void update(const rio::BaseVec3f& position);

    void scheduleDraw() const;

private:
    struct
    {
        BasicModel*                 p_model;
        TexturePatternAnimation*    p_tex_pat_anim;
        ShaderParamAnimation*       p_tex_srt_anim;
        ShaderParamAnimation*       p_color_anim;
    }               mA,
                    mB;
    f32             mLength;
    rio::BaseVec3f  mScale;
    rio::BaseMtx34f mMtxRT;
    Type            mType;
    bool            mIsAVisible;
};
