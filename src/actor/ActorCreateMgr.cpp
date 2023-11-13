#include <actor/ActorCreateMgr.h>
#include <map_obj/ActorCoin.h>

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
    addActorFactory(65, &ActorCoin::create);
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
