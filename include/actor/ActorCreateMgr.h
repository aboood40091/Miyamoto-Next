#pragma once

#include <item/MapActorItem.h>

#include <memory>
#include <unordered_map>

using ActorFactory = std::unique_ptr<MapActorItem> (*)(const MapActorData&, u32);

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
    void initialize();

    void setTypeMaxNum(u16 max_num);
    u16 getTypeMaxNum() const;

    void setName(u16 map_actor_type, const std::u8string& name);
    const std::u8string& getName(u16 map_actor_type) const;

    void setActorFactory(u16 map_actor_type, ActorFactory factory, const MapActorData* default_data = nullptr);
    const std::pair<ActorFactory, const MapActorData*>* getActorFactory(u16 map_actor_type) const;

    template <typename T>
    void setActorFactory(u16 map_actor_type)
    {
        setActorFactory(map_actor_type, &T::create, T::getDefaultData(map_actor_type));
    }

    std::unique_ptr<MapActorItem> create(const MapActorData& map_actor_data, u32 index) const;

private:
    u16                                     mTypeMaxNum;
    std::unordered_map<u16, std::u8string>  mMapActorNameMap;
    std::unordered_map<u16, std::pair<ActorFactory, const MapActorData*> >
                                            mActorFactoryMap;
};
