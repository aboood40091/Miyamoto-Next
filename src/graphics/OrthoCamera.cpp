#include <graphics/OrthoCamera.h>

void OrthoCamera::getMatrix(rio::BaseMtx34f* dst) const
{
    RIO_ASSERT(dst);

    dst->m[0][0] = mZoomScale;
    dst->m[0][1] = 0.0f;
    dst->m[0][2] = 0.0f;
    dst->m[0][3] = -mPos.x * mZoomScale;

    dst->m[1][0] = 0.0f;
    dst->m[1][1] = mZoomScale;
    dst->m[1][2] = 0.0f;
    dst->m[1][3] = -mPos.y * mZoomScale;

    dst->m[2][0] = 0.0f;
    dst->m[2][1] = 0.0f;
    dst->m[2][2] = 1.0f;
    dst->m[2][3] = -10000.0f;
}
