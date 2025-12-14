# Miyamoto-Next
A complete rewrite of Miyamoto! Level Editor, with all-new features.  

# Dependencies
* NSMBU, NSLU or NSMBU+NSLU "content" folder. Set its path in `src/Globals.cpp`. For absolute path, prepend path with `native://`. Relative paths are relative to `fs/content/`.  
* OpenGL 4.3 or higher.  
* GCC-compatible compiler
* Premake5 + GNU Make or MSBuild with Clang-cl
* [GLEW](https://github.com/Perlmint/glew-cmake)
* [GLFW](https://github.com/glfw/glfw)
* [RIO](https://github.com/aboood40091/rio).
* [ninTexUtils](https://github.com/aboood40091/nintexUtils/tree/cpp).  
* [NW4F G3d Windows Port](https://github.com/nw4f/G3d/tree/nsmbu-win-port).  
* [agl-next](https://github.com/aboood40091/agl-next).  
* [ModelStuff-next](https://github.com/aboood40091/ModelStuff-next).  
* [ImGui for RIO](https://github.com/aboood40091/imgui/tree/rio_docking).  
* [Native File Dialog Extended](https://github.com/btzy/nativefiledialog-extended)
* [Backward-cpp](https://github.com/bombela/backward-cpp)

# Building
1. Clone this repository **recursively**.
2. Invoke Premake on your system as: `premake5 gmake`.
3. Compile the resulting Makefile using `make`, the output executable will be in `bin`.
