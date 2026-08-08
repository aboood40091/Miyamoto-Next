#pragma once

#include <item/MapActorItem.h>

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

using ActorFactory = std::unique_ptr<MapActorItem> (*)(const MapActorData&, u32);

enum ActorNameLanguage : s32
{
    ACTOR_NAME_LANGUAGE_ENGLISH = 0,
    ACTOR_NAME_LANGUAGE_JAPANESE,
    ACTOR_NAME_LANGUAGE_BOTH,           // "English (Japanese)"

    ACTOR_NAME_LANGUAGE_MAX_NUM
};

class ActorCreateMgr
{
public:
    enum NameFlag : u32
    {
        NAME_FLAG_NONE      = 0,

        NAME_FLAG_UNUSED    = 1 << 0,   // Unused by any retail level.
        NAME_FLAG_CRASHES   = 1 << 1,   // Known to crash the game.
        NAME_FLAG_NSLU      = 1 << 2    // New Super Luigi U only.
    };

    friend NameFlag operator|(const NameFlag& lhs, const NameFlag& rhs)
    {
        return (NameFlag)((u32)lhs | (u32)rhs);
    }

    friend NameFlag& operator|=(NameFlag& lhs, const NameFlag& rhs)
    {
        lhs = lhs | rhs;
        return lhs;
    }

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

    void setName(u16 map_actor_type, std::u8string_view name_japanese, std::string_view name_english = {});

    // Name in the language currently selected, falling back to the other one.
    const std::string& getName(u16 map_actor_type) const;

    const std::string& getNameJapanese(u16 map_actor_type) const;
    const std::string& getNameEnglish(u16 map_actor_type) const;

    // "123: Some Actor", ready to use as a list row and as an ImGui ID.
    const std::string& getLabel(u16 map_actor_type) const;

    // Type number plus *both* names, so a filter matches either language regardless of which one is currently displayed.
    const std::string& getSearchKey(u16 map_actor_type) const;

    NameFlag getNameFlags(u16 map_actor_type) const;

    ActorNameLanguage getNameLanguage() const { return mNameLanguage; }
    void setNameLanguage(ActorNameLanguage language);

    void setActorFactory(u16 map_actor_type, ActorFactory factory, const MapActorData* default_data = nullptr);
    const std::pair<ActorFactory, const MapActorData*>* getActorFactory(u16 map_actor_type) const;

    template <typename T>
    void setActorFactory(u16 map_actor_type)
    {
        setActorFactory(map_actor_type, &T::create, T::getDefaultData(map_actor_type));
    }

    std::unique_ptr<MapActorItem> create(const MapActorData& map_actor_data, u32 index) const;

private:
    struct NameEntry
    {
        std::string japanese;   // UTF-8
        std::string english;    // UTF-8, ASCII in practice
        NameFlag    flags;

        // Rebuilt by updateNameEntry_() whenever the language changes.
        std::string display;
        std::string label;
        std::string search;
    };

    static NameFlag deriveNameFlags_(std::string_view name_english);
    void updateNameEntry_(u16 map_actor_type, NameEntry& entry) const;
    void updateNameEntries_();

    const NameEntry* findNameEntry_(u16 map_actor_type) const;

private:
    u16                                     mTypeMaxNum;
    ActorNameLanguage                       mNameLanguage;
    std::unordered_map<u16, NameEntry>      mMapActorNameMap;
    std::unordered_map<u16, std::pair<
        ActorFactory,
        const MapActorData*
    > >                                     mActorFactoryMap;
};
