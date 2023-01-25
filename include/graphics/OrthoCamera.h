#pragma once

#include <gfx/rio_Camera.h>

class OrthoCamera : public rio::Camera
{
public:
    OrthoCamera()
        : mPos{ 0.0f, 0.0f }
        , mZoomScale(1.0f)
    {
    }

    rio::BaseVec2f& pos() { return mPos; }
    const rio::BaseVec2f& pos() const { return mPos; }

    f32 getZoomScale() const { return mZoomScale; }
    void setZoomScale(f32 zoom_scale) { mZoomScale = zoom_scale; }

    void getMatrix(rio::BaseMtx34f* dst) const override;

private:
    rio::BaseVec2f mPos;
    f32 mZoomScale;
};
