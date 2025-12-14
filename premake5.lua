-- premake5.lua
workspace "Miyamoto-Next"
    architecture "x86"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    --warnings "Extra"
    configurations { "Debug", "Release" }
    startproject "Miyamoto-Next"

    filter "configurations:Debug"
        optimize "debug"
        symbols "on"
        defines {
            "RIO_DEBUG",
            "NW_DEBUG",
            "_DEBUG"
        }
    
    filter "configurations:Release"
        optimize "speed"
        linktimeoptimization "on"
        symbols "off"
        defines {
            "RIO_RELEASE",
            "NW_RELEASE"
        }

project "Miyamoto-Next"
    targetdir "./bin"
    objdir "build/bin/%{prj.name}-%{cfg.buildcfg}/int"
    debugdir "./bin"
    
    includedirs {
        "include",
        
        "lib/glew/include",
        "lib/glfw/include",
        "lib/ModelStuff-next/lib/agl/lib/rio/include",
        "lib/ModelStuff-next/lib/agl/lib/ninTexUtils/include",
        "lib/ModelStuff-next/lib/agl/lib/g3d/CafeSDKWrappers/cafe_win",
        "lib/ModelStuff-next/lib/agl/lib/g3d/include",
        "lib/ModelStuff-next/lib/agl/lib/rio_utils/include",
        "lib/ModelStuff-next/lib/agl/include",
        "lib/ModelStuff-next/include",
        "lib/imgui",
        "lib/imgui/backends",
        "lib/nfd/src/include",
        "lib/backward-cpp"
    }

    files {
        "src/**",
        
        "lib/ModelStuff-next/lib/agl/lib/rio/src/**",
        "lib/ModelStuff-next/lib/agl/lib/ninTexUtils/**",
        "lib/ModelStuff-next/lib/agl/lib/g3d/src/**",
        "lib/ModelStuff-next/lib/agl/lib/rio_utils/src/**",
        "lib/ModelStuff-next/lib/agl/src/**",
        "lib/ModelStuff-next/src/**",
        
        "lib/imgui/*",
        "lib/imgui/backends/imgui_impl_glfw.cpp",
        "lib/imgui/backends/imgui_impl_opengl3.cpp",
        
        "lib/glew/src/glew.c",
        
        "lib/glfw/include/GLFW/glfw3.h",
        "lib/glfw/include/GLFW/glfw3native.h",
        "lib/glfw/src/glfw_config.h",
        "lib/glfw/src/context.c",
        "lib/glfw/src/init.c",
        "lib/glfw/src/input.c",
        "lib/glfw/src/monitor.c",

        "lib/glfw/src/null_init.c",
        "lib/glfw/src/null_joystick.c",
        "lib/glfw/src/null_monitor.c",
        "lib/glfw/src/null_window.c",

        "lib/glfw/src/platform.c",
        "lib/glfw/src/vulkan.c",
        "lib/glfw/src/window.c",
        
        "lib/backward-cpp/backward.cpp",
    }

    filter "system:linux"
        pic "On"
        
        toolset "clang"
        stl "libc++"

        systemversion "latest"
        
        links {
            "GL",
            "dbus-1"
        }
        
        files {
            "lib/glfw/src/x11_init.c",
            "lib/glfw/src/x11_monitor.c",
            "lib/glfw/src/x11_window.c",
            "lib/glfw/src/xkb_unicode.c",
            "lib/glfw/src/posix_module.c",
            "lib/glfw/src/posix_time.c",
            "lib/glfw/src/posix_thread.c",
            "lib/glfw/src/posix_module.c",
            "lib/glfw/src/posix_poll.c",
            "lib/glfw/src/glx_context.c",
            "lib/glfw/src/egl_context.c",
            "lib/glfw/src/osmesa_context.c",
            "lib/glfw/src/linux_joystick.c",
            
            "lib/nfd/src/nfd_portal.cpp"
        }
        
        includedirs {
            "/usr/include/dbus-1.0",
            "/usr/lib64/dbus-1.0/include"
        }

        defines {
            "_GLFW_X11",
            "NFD_PLATFORM_LINUX"
        }
        
        buildoptions { "-stdlib=libc++" }
        linkoptions  { "-stdlib=libc++" }

    filter "system:macosx"
        pic "On"

        files {
            "lib/glfw/src/cocoa_init.m",
            "lib/glfw/src/cocoa_monitor.m",
            "lib/glfw/src/cocoa_window.m",
            "lib/glfw/src/cocoa_joystick.m",
            "lib/glfw/src/cocoa_time.c",
            "lib/glfw/src/nsgl_context.m",
            "lib/glfw/src/posix_thread.c",
            "lib/glfw/src/posix_module.c",
            "lib/glfw/src/osmesa_context.c",
            "lib/glfw/src/egl_context.c"
        }

        defines {
            "_GLFW_COCOA"
        }

    filter "system:windows"
        systemversion "latest"

        links {
            "opengl32"
        }

        files {
            "lib/glfw/src/win32_init.c",
            "lib/glfw/src/win32_joystick.c",
            "lib/glfw/src/win32_module.c",
            "lib/glfw/src/win32_monitor.c",
            "lib/glfw/src/win32_time.c",
            "lib/glfw/src/win32_thread.c",
            "lib/glfw/src/win32_window.c",
            "lib/glfw/src/wgl_context.c",
            "lib/glfw/src/egl_context.c",
            "lib/glfw/src/osmesa_context.c",
            
            "lib/nfd/src/nfd_win.cpp"
        }

        defines {
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS",
            "NFD_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        kind "ConsoleApp"
        targetname "Miyamoto-Next-Debug"

    filter "configurations:Release"
        kind "WindowedApp"
        targetname "Miyamoto-Next"
