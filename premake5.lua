-- premake5.lua
workspace "Miyamoto-Next"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    warnings "Extra"
    platforms { "x86", "x64", "ARM64" }
    configurations { "Debug", "Release" }

    stl "libc++"
    linkgroups "On"

    targetdir "./bin"
    objdir "build"
    targetname "%{prj.name}-%{cfg.buildcfg}-%{cfg.architecture}"
    debugdir "./bin"

    startproject "Miyamoto-Next"

    defines {
        "GLEW_STATIC"
    }

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
        "lib/simpleini"
    }

    disablewarnings {
        "unused-parameter",
        "missing-field-initializers"
    }

    filter { "toolset:clang", "platforms:x86" }
        stl "gnu"

    filter { "toolset:gcc", "files:**.cpp" }
        disablewarnings {
            "invalid-offsetof",
            "class-memaccess"
        }

    filter "toolset:clang"
        disablewarnings {
            "unused-private-field",
            "missing-braces",
            "invalid-offsetof"
        }

    filter { "system:linux", "toolset:clang" }
        disablewarnings {
            "missing-designated-field-initializers",
            "nontrivial-memaccess"
        }

    filter { "system:windows", "toolset:clang" }
        disablewarnings {
            "missing-designated-field-initializers",
            "nontrivial-memcall"
        }

    filter "platforms:x86"
        architecture "x86"

    filter "platforms:x64"
        architecture "x64"
        vectorextensions "AVX2"

    filter "platforms:ARM64"
        architecture "ARM64"

    filter "configurations:Debug"
        optimize "debug"
        omitframepointer "off"
        symbols "on"
        defines {
            "RIO_DEBUG",
            "NW_DEBUG",
            "_DEBUG"
        }

    filter "configurations:Release"
        optimize "speed"
        omitframepointer "on"
        symbols "off"
        defines {
            "RIO_RELEASE",
            "NW_RELEASE"
        }
        linktimeoptimization "On"

    filter { "configurations:Debug", "platforms:x64", "toolset:clang" }
        sanitize { "Address", "UndefinedBehavior" }

    filter "system:linux"
        systemversion "latest"

    filter "system:windows"
        systemversion "latest"

        defines {
            "NOMINMAX",
            "WIN32_LEAN_AND_MEAN",
            "_CRT_SECURE_NO_WARNINGS"
        }

project "Lib_GLEW"
    kind "StaticLib"
    language "C"
    warnings "off"

    files {
        "lib/glew/src/glew.c"
    }

project "Lib_GLFW"
    kind "StaticLib"
    language "C"
    warnings "off"

    files {
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
        "lib/glfw/src/window.c"
    }

    filter "system:linux"
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
            "lib/glfw/src/linux_joystick.c"
        }

        defines {
            "_GLFW_X11"
        }

    filter "system:windows"
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
            "lib/glfw/src/osmesa_context.c"
        }

        defines {
            "_GLFW_WIN32"
        }

    filter "system:macosx"
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

project "Lib_ImGui"
    kind "StaticLib"
    warnings "off"

    files {
        "lib/imgui/*",
        "lib/imgui/backends/imgui_impl_glfw.cpp",
        "lib/imgui/backends/imgui_impl_opengl3.cpp"
    }

project "Lib_BackwardCpp"
    kind "StaticLib"
    warnings "off"

    filter "system:linux"
        includedirs {
            "lib/backward-cpp"
        }

        files {
            "lib/backward-cpp/backward.cpp"
        }

project "Lib_NFD"
    kind "StaticLib"
    warnings "off"

    filter "system:linux"
        files {
            "lib/nfd/src/nfd_portal.cpp"
        }

        defines {
            "NFD_PLATFORM_LINUX"
        }

        buildoptions { "`pkg-config --cflags dbus-1`" }
        linkoptions  { "`pkg-config --libs dbus-1`" }

    filter "system:windows"
        files {
            "lib/nfd/src/nfd_win.cpp"
        }

        defines {
            "NFD_PLATFORM_WINDOWS"
        }

    filter "system:macosx"
        files {
            "lib/nfd/src/nfd_cocoa.m"
        }

project "Lib_RIO"
    kind "StaticLib"

    files {
        "lib/ModelStuff-next/lib/agl/lib/rio/src/**",
        "lib/ModelStuff-next/lib/agl/lib/rio_utils/src/**"
    }

project "Lib_ninTexUtils"
    kind "StaticLib"

    files {
        "lib/ModelStuff-next/lib/agl/lib/ninTexUtils/**"
    }

project "Lib_G3d"
    kind "StaticLib"

    files {
        "lib/ModelStuff-next/lib/agl/lib/g3d/src/**"
    }

project "Lib_AGL"
    kind "StaticLib"

    files {
        "lib/ModelStuff-next/lib/agl/src/**"
    }

    filter "toolset:gcc"
        disablewarnings {
            "maybe-uninitialized"
        }

    filter "toolset:clang"
        disablewarnings {
            "invalid-source-encoding"
        }

project "Lib_ModelStuff"
    kind "StaticLib"

    files {
        "lib/ModelStuff-next/src/**"
    }

project "Miyamoto-Next"
    files {
        "src/**"
    }

    links {
        "Lib_RIO",
        "Lib_ninTexUtils",
        "Lib_G3d",
        "Lib_AGL",
        "Lib_ModelStuff",

        "Lib_ImGui",
        "Lib_NFD",
        "Lib_GLEW",
        "Lib_GLFW"
    }

    filter "toolset:clang"
        disablewarnings {
            "invalid-source-encoding"
        }

    filter "system:linux"
        links {
            "Lib_BackwardCpp",
            "GL"
        }

        buildoptions { "`pkg-config --cflags dbus-1`" }
        linkoptions  { "`pkg-config --libs dbus-1`" }

    filter "system:windows"
        links {
            "opengl32",
            "gdi32",
            "ole32",
            "uuid",
            "shell32"
        }

        linkoptions { "-static" }

    filter "system:macosx"
        links {
            "Cocoa.framework",
            "IOKit.framework",
            "CoreVideo.framework",
            "OpenGL.framework",
            "QuartzCore.framework",
            "UniformTypeIdentifiers.framework"
        }

    filter "configurations:Debug"
        kind "ConsoleApp"

    filter "configurations:Release"
        kind "WindowedApp"

    filter { "system:windows", "configurations:Release" }
        entrypoint "mainCRTStartup"

    filter "action:gmake*"
        postbuildcommands {
            'cd "%{cfg.targetdir}" && rm -f *.a *.lib'
        }

    filter "action:vs*"
        postbuildcommands {
            'cd /d "%{cfg.targetdir}"',
            'del /q *.lib 2>nul',
            'del /q *.a 2>nul'
        }
