#pragma once

#include <item/MapActorItem.h>

#include <memory>
#include <unordered_map>

using ActorFactory = std::unique_ptr<MapActorItem> (*)(MapActorData&);

class ActorCreateMgr
{
public:
    static bool createSingleton();
    static void destroySingleton();
    static ActorCreateMgr* instance() { return sInstance; }

private:
    static ActorCreateMgr* sInstance;

    ActorCreateMgr();
    ~ActorCreateMgr();

    ActorCreateMgr(const ActorCreateMgr&);
    ActorCreateMgr& operator=(const ActorCreateMgr&);

public:
    void addActorFactory(u16 id, ActorFactory factory);
    std::unique_ptr<MapActorItem> create(MapActorData& map_actor_data);

private:
    std::unordered_map<u16, ActorFactory>   mActorFactoryMap;
};
