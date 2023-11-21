#include <map_obj/BlockCoinBase.h>

#include <MainWindow.h>
#include <rio.h>

void BlockCoinBase::onDataChange(DataChangeFlag flag)
{
    if (flag & DATA_CHANGE_FLAG_OFFSET)
        updatePositionXY_();

    if (flag & DATA_CHANGE_FLAG_LAYER)
        updatePositionZ_();
}

void BlockCoinBase::scheduleDraw()
{
    static_cast<MainWindow*>(rio::sRootTask)->getBgRenderer().drawUnit(
        mPosition, getUnitID_(), mMapActorData.layer
    );
}
