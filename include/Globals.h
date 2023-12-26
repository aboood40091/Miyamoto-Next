#pragma once

#include <misc/rio_Types.h>

#include <string>

class Globals
{
public:
    static std::string  sContentPath;
    static bool         sForceSharcfb;
    static f32          sBigItemScale;
    static bool         sUseRealZoom;
    static bool         sPreserveUnitSize;          // Ignored if real zoom
    static bool         sApplyDistantViewScissor;
};
