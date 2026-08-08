# Miyamoto-Next
A complete rewrite of Miyamoto! Level Editor, with all-new features.

# Dependencies
* NSMBU, NSLU or NSMBU+NSLU `content` folder. See [Configuration](#configuration) below.
* OpenGL 4.3 or higher.
* GCC-compatible compiler.
* Premake5, along with GNU Make or MSBuild+Clang-cl.
* [GLEW](https://github.com/Perlmint/glew-cmake).
* [GLFW](https://github.com/glfw/glfw).
* [RIO](https://github.com/aboood40091/rio/tree/linux).
* [ninTexUtils](https://github.com/aboood40091/nintexUtils/tree/cpp).
* [NW4F G3d Windows Port](https://github.com/nw4f/G3d/tree/nsmbu-win-port).
* [agl-next](https://github.com/aboood40091/agl-next).
* [ModelStuff-next](https://github.com/aboood40091/ModelStuff-next).
* [ImGui for RIO](https://github.com/aboood40091/imgui/tree/rio_docking).
* [Native File Dialog Extended](https://github.com/btzy/nativefiledialog-extended).
* [Backward-cpp](https://github.com/bombela/backward-cpp).
* [SimpleIni](https://github.com/brofield/simpleini).
* [Tracy](https://github.com/wolfpld/tracy).

# Building
1. Clone this repository **recursively**.
2. Invoke Premake on your system as:  
    * GCC: `premake5 gmake`
    * Clang: `premake5 --cc=clang gmake`.
    * MSBuild+Clang-cl: `premake5 vs2022`
3. Compile:
    * GCC and Clang: Using `make` with `config={Config}_{Architecture}` (e.g., `make config=Release_x64`).
    * For MSBuild+Clang-cl: Using the command `msbuild Miyamoto-Next.sln /m /p:Configuration={Config} /p:Platform={Architecture} /p:PlatformToolset=ClangCl` (e.g., `msbuild Miyamoto-Next.sln /m /p:Configuration=Release /p:Platform=x64 /p:PlatformToolset=ClangCl`).

The output executable will be in `bin`.

# Configuration

Settings live in `preferences.ini`, next to the executable in `bin`. The file is created with defaults on first run.

| Key | Default | Meaning |
| --- | --- | --- |
| `ContentPath` | `game/nsmbu` | Path to the game's content root (the folder containing `Common`). |
| `StartupLevel` | `1-1.szs` | Level opened at startup, relative to `<ContentPath>/Common/course_res_pack/`. Leave empty to start with a blank course. |
| `ActorNameLanguage` | `0` | Actor names shown in the palette and inspector: `0` English, `1` Japanese, `2` both. |
| `ActorHideUnused` | `false` | Hide actors marked `[UNUSED]` from the actor palette. |
| `ActorHideNSLU` | `false` | Hide New Super Luigi U actors from the actor palette. |
| `MaxUndoHistory` | `100` | Maximum number of undo steps kept. `0` means unlimited. Applied when the next edit is made. |

Relative paths are resolved against `fs/content/`. For example, based on the default value of `<ContentPath>`, an example game file path would be `fs/content/game/nsmbu/Common/shader/shaderfb.szs`.

The content root is expected to look like this:

```
<ContentPath>/
└── Common/
    ├── actor/
    │   ├── jyotyuActorPack.szs
    │   ├── cobPack.szs
    │   └── ...
    ├── course_res_pack/
    │   ├── 1-1.szs
    │   └── ...
    ├── distant_view/
    │   └── ...
    └── shader/
        └── shaderfb.szs
```

If a required file is missing, the editor reports which path it tried and what the current `ContentPath` is.
