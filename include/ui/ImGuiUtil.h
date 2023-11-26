#pragma once

#include <misc/rio_Types.h>

class ImGuiUtil
{
public:
    static void initialize();
    static void initialize(f32 width, f32 height);
    static void shutdown();

    static void setDisplaySize(f32 width, f32 height);

    static void newFrame();
    static void render();
};

inline void ImGuiUtil::initialize(f32 width, f32 height)
{
    initialize();
    setDisplaySize(width, height);
}
