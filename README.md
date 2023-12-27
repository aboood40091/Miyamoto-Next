# Miyamoto-Next
A complete rewrite of Miyamoto! Level Editor, with all-new features.  

# Dependencies
* NSMBU, NSLU or NSMBU+NSLU "content" folder. Set its path in `src/Globals.cpp`. For absolute path, prepend path with `native://`. Relative paths are relative to `fs/content/`.  
* OpenGL 4.3 or higher.  
* [RIO](https://github.com/aboood40091/rio) & its dependencies (g++ | GLEW | GLFW).  
* [ninTexUtils](https://github.com/aboood40091/nintexUtils/tree/cpp).  
* [NW4F G3d Windows Port](https://github.com/nw4f/G3d/tree/nsmbu-win-port).  
* [agl-next](https://github.com/aboood40091/agl-next).  
* [ModelStuff-next](https://github.com/aboood40091/ModelStuff-next).  
* [ImGui for RIO](https://github.com/aboood40091/imgui/tree/rio_docking).  

# Building
Currently, Miyamoto! Next is only buildable on Windows.  
Use instructions for building RIO as base. Additionally, define "NW_DEBUG" for debug builds and "NW_RELEASE" for release builds. Hopefully proper building instructions will be added in the future (with a proper setup).  