#pragma once

#include <item/ItemID.h>

#include <math/rio_MathTypes.h>

class BasicModel;
class ModelResource;

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
    ObjDokan(Direction dir);
    ~ObjDokan();

    ObjDokan(const ObjDokan&) = delete;
    ObjDokan(ObjDokan&&) = delete;
    ObjDokan& operator=(const ObjDokan&) = delete;
    ObjDokan& operator=(ObjDokan&&) = delete;

    bool initialize(Type type, f32 length = 16, bool draw_a = true, Color color = COLOR_INVALID);
    bool update(f32 length, bool draw_a, Color color);
    void destroy();

    bool isCreated() const
    {
        return mpModelResource;
    }

    void setModelItemID(ItemID item_id);
    void setModelSelection(bool is_selected);

    void move(const rio::BaseVec3f& position);
    void onSceneUpdate() const;

    void scheduleDraw() const;

private:
    void setLength_(f32 length)
    {
        RIO_ASSERT(length > 0);
        mLength = length;
        mScale.y = mLength / 16;
    }

    void setModelMtxSRT_();

private:
    const ModelResource*    mpModelResource;
    BasicModel*             mpModelA;
    BasicModel*             mpModelB;

    f32                     mBaseFrame;
    rio::BaseMtx34f         mMtxRT;

    Type                    mType;
    f32                     mLength;
    rio::BaseVec3f          mScale;
    bool                    mIsEnableDrawA;
    Color                   mColor;
};
