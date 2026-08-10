#pragma once

#include <ConfigMgr.h>

#include <string>

enum ActorNameLanguage : s32;
enum GridType : s32;

class Preferences
{
public:
    static bool createSingleton();
    static void destroySingleton();
    static Preferences* instance() { return sInstance; }

private:
    static constexpr const char* cSection = "Preferences";
    static inline Preferences* sInstance = nullptr;

    Preferences();
    ~Preferences() = default;

    Preferences(const Preferences&) = delete;
    Preferences& operator=(const Preferences&) = delete;

public:
    [[nodiscard]]
    std::string getTheme();
    void setTheme(const std::string& value);
    
    [[nodiscard]]
    std::string getContentPathRaw();
    [[nodiscard]]
    std::string getContentPath();
    void setContentPath(const std::string& value);

    [[nodiscard]]
    std::string getStartupLevel();
    void setStartupLevel(const std::string& value);
    
    [[nodiscard]]
    bool getForceSharcfb();
    void setForceSharcfb(bool value);
    
    [[nodiscard]]
    f32 getBigItemScale();
    void setBigItemScale(f32 value);
    
    [[nodiscard]]
    f32 getZoomUnitSize();
    void setZoomUnitSize(f32 value);
    
    [[nodiscard]]
    bool getApplyDistantViewScissor();
    void setApplyDistantViewScissor(bool value);
    
    [[nodiscard]]
    f32 getScrollMovementSpeed();
    void setScrollMovementSpeed(f32 value);
    
    [[nodiscard]]
    f32 getArrowMovementSpeed();
    void setArrowMovementSpeed(f32 value);
    
    [[nodiscard]]
    f32 getFastArrowMovementSpeed();
    void setFastArrowMovementSpeed(f32 value);
    
    [[nodiscard]]
    bool getSmoothZoom();
    void setSmoothZoom(bool value);
    
    [[nodiscard]]
    bool getUnlockedFPS();
    void setUnlockedFPS(bool value);

    [[nodiscard]]
    ActorNameLanguage getActorNameLanguage();
    void setActorNameLanguage(ActorNameLanguage value);

    [[nodiscard]]
    bool getActorHideUnused();
    void setActorHideUnused(bool value);

    [[nodiscard]]
    bool getActorHideNSLU();
    void setActorHideNSLU(bool value);

    [[nodiscard]]
    u32 getMaxUndoHistory();
    void setMaxUndoHistory(u32 value);

    [[nodiscard]]
    GridType getGridType();
    void setGridType(GridType value);

private:
    ConfigMgr mConfig;
};
