#pragma once

#include <misc/rio_Types.h>

#include <string>

class Globals
{
public:
    static const std::string& getContentPath();
    static bool forceSharcfb() { return true; }
    static f32 getBigItemScale() { return 16; }
    static bool useRealZoom() { return true; }
    static bool preserveUnitSize() { return false; }    // Ignored if real zoom
    static bool applyDistantViewScissor() { return true; }
};
