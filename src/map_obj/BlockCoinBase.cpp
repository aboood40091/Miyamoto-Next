#include <course/BgRenderer.h>
#include <map_obj/BlockCoinBase.h>

void BlockCoinBase::onDataChange(DataChangeFlag flag)
{
    if (flag & DATA_CHANGE_FLAG_OFFSET)
        updatePositionXY_();

    if (flag & DATA_CHANGE_FLAG_LAYER)
        updatePositionZ_();
}

void BlockCoinBase::scheduleDraw()
{
    BgRenderer::instance()->drawUnit(
        mPosition, getUnitID_(), mMapActorData.layer
    );
}
