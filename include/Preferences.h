#pragma once

#include <misc/rio_Types.h>
#include <string>

class Preferences
{
private:
    static constexpr const char* cSection = "Preferences";

public:
    static std::string  getTheme();
    static std::string  getContentPath();
    static bool         getForceSharcfb();
    static f32          getBigItemScale();
    static bool         getUseRealZoom();
    static bool         getPreserveUnitSize();
    static bool         getApplyDistantViewScissor();
    static f32          getScrollMovementSpeed();
    static f32          getArrowMovementSpeed();
    static f32          getFastArrowMovementSpeed();
    
    static void setTheme(const std::string& value);
    static void setContentPath(const std::string& value);
    static void setForceSharcfb(bool value);
    static void setBigItemScale(f32 value);
    static void setUseRealZoom(bool value);
    static void setPreserveUnitSize(bool value);
    static void setApplyDistantViewScissor(bool value);
    static void setScrollMovementSpeed(f32 value);
    static void setArrowMovementSpeed(f32 value);
    static void setFastArrowMovementSpeed(f32 value);
};
