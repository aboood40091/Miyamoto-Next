#include <map_obj/BlockCoinBase.h>

#include <MainWindow.h>
#include <rio.h>

void BlockCoinBase::scheduleDraw()
{
    rio::Vector3f offs { f32(mMapActorData.offset.x), -f32(mMapActorData.offset.y), getZPos_() };

    static_cast<MainWindow*>(rio::sRootTask)->getBgRenderer().drawUnit(
        offs, getUnitID_(), mMapActorData.layer
    );
}
