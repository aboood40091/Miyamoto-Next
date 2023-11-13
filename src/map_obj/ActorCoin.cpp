#include <map_obj/ActorCoin.h>

#include <MainWindow.h>
#include <rio.h>

ActorCoin::ActorCoin(MapActorData& map_actor_data)
    : MapActorItem(map_actor_data)
{
}

void ActorCoin::scheduleDraw()
{
    rio::Vector3f offs { f32(mMapActorData.offset.x), -f32(mMapActorData.offset.y), getZPos_() };

    static_cast<MainWindow*>(rio::sRootTask)->getBgRenderer().drawUnit(
        offs, cUnitID_Coin, mMapActorData.layer
    );
}
