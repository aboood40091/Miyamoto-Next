#include <actor/ActorCreateMgr.h>
#include <enemy/Kuribo.h>
#include <enemy/Nokonoko.h>
#include <map_obj/ActorBlockBigHatena.h>
#include <map_obj/ActorBlockBigRenga.h>
#include <map_obj/ActorBlockHatena.h>
#include <map_obj/ActorBlockRenga.h>
#include <map_obj/ActorCoin.h>
#include <map_obj/CollectionCoin.h>
#include <map_obj/DokanJoint.h>
#include <map_obj/GoalPole.h>
#include <map_obj/ObjDokanActorDown.h>
#include <map_obj/ObjDokanActorDownNextGoto.h>
#include <map_obj/ObjDokanActorLeft.h>
#include <map_obj/ObjDokanActorLeftNextGoto.h>
#include <map_obj/ObjDokanActorRight.h>
#include <map_obj/ObjDokanActorRightNextGoto.h>
#include <map_obj/ObjDokanActorUp.h>
#include <map_obj/ObjDokanActorUpNextGoto.h>

ActorCreateMgr* ActorCreateMgr::sInstance = nullptr;

bool ActorCreateMgr::createSingleton()
{
    if (sInstance)
        return false;

    sInstance = new ActorCreateMgr();
    return true;
}

void ActorCreateMgr::destroySingleton()
{
    if (!sInstance)
        return;

    delete sInstance;
    sInstance = nullptr;
}

ActorCreateMgr::ActorCreateMgr()
{
    addActorFactory(0, &Kuribo::create);

    addActorFactory(19, &Nokonoko::create);

    addActorFactory(31, &GoalPole::create);

    addActorFactory(45, &CollectionCoin::create);

    addActorFactory(47, &CollectionCoin::create);

    addActorFactory(55, &Nokonoko::create);

    addActorFactory(59, &ActorBlockHatena::create);
    addActorFactory(60, &ActorBlockRenga::create);

    addActorFactory(65, &ActorCoin::create);
    addActorFactory(66, &ActorCoin::create);

    addActorFactory(139, &ObjDokanActorUp::create);
    addActorFactory(140, &ObjDokanActorDown::create);
    addActorFactory(141, &ObjDokanActorLeft::create);
    addActorFactory(142, &ObjDokanActorRight::create);

    addActorFactory(147, &ActorBlockHatena::create);
    addActorFactory(148, &ActorBlockRenga::create);

    addActorFactory(149, &ActorCoin::create);

    addActorFactory(205, &ActorBlockHatena::create);

    addActorFactory(233, &ActorBlockHatena::create);
    addActorFactory(234, &ActorBlockRenga::create);

    addActorFactory(279, &ActorCoin::create);

    addActorFactory(325, &ActorCoin::create);

    addActorFactory(328, &ActorCoin::create);

    addActorFactory(397, &ActorBlockHatena::create);
    addActorFactory(398, &ActorBlockRenga::create);

    addActorFactory(404, &ObjDokanActorUpNextGoto::create);

    addActorFactory(422, &ActorBlockBigRenga::create);

    addActorFactory(437, &Kuribo::create);
    addActorFactory(438, &Kuribo::create);

    addActorFactory(475, &ActorBlockBigHatena::create);
    addActorFactory(476, &Nokonoko::create);

    addActorFactory(480, &CollectionCoin::create);

    addActorFactory(496, &ActorCoin::create);

    addActorFactory(503, &GoalPole::create);

    addActorFactory(509, &ObjDokanActorRightNextGoto::create);
    addActorFactory(510, &ObjDokanActorLeftNextGoto::create);
    addActorFactory(511, &ObjDokanActorDownNextGoto::create);

    addActorFactory(513, &DokanJoint::create);

    addActorFactory(525, &ActorBlockHatena::create);
    addActorFactory(526, &ActorBlockRenga::create);

    addActorFactory(575, &ObjDokanActorLeft::create);
    addActorFactory(576, &ObjDokanActorRight::create);
    addActorFactory(577, &ObjDokanActorUp::create);
    addActorFactory(578, &ObjDokanActorDown::create);

    addActorFactory(595, &Kuribo::create);

    addActorFactory(630, &GoalPole::create);
    addActorFactory(631, &GoalPole::create);

    addActorFactory(663, &ActorCoin::create);

    addActorFactory(683, &ActorBlockHatena::create);

    addActorFactory(692, &ActorBlockRenga::create);

    addActorFactory(701, &ActorBlockRenga::create);

    addActorFactory(704, &ActorBlockRenga::create);
}

ActorCreateMgr::~ActorCreateMgr()
{
}

void ActorCreateMgr::addActorFactory(u16 id, ActorFactory factory)
{
    mActorFactoryMap[id] = factory;
}

std::unique_ptr<MapActorItem> ActorCreateMgr::create(MapActorData& map_actor_data)
{
    const auto& itr = mActorFactoryMap.find(map_actor_data.id);
    if (itr != mActorFactoryMap.end())
        return (*itr->second)(map_actor_data);

    return std::make_unique<MapActorItem>(map_actor_data);
}
