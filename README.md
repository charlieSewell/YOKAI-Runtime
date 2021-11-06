# YOKAI-Runtime

### Dependencies
* Linux: `apt install build-essential clang ninja-build libx11-dev \
   libxcursor-dev libxrandr-dev libxinerama-dev libxi-dev libxext-dev\
   libxfixes-dev libglu1-mesa-dev`
* macOS: `brew install cmake ninja llvm`
* Windows: `None` 
### Building

#### Linux & macOS:
```
CXX=clang++ cmake -S . -B build -G Ninja -D CMAKE_BUILD_TYPE=Release
```
Change directory to whatever you specified X as.
```
cmake --build . && ./ICT398-Game-Engine
```
#### Windows:
    * Open Visual Studio as Administrator (required to make symbolic links)
    * Press Continue without Code
    * In Visual Studio, select Open → CMake, Navigate to the project folder and select `CMakeLists.txt`
    * From the "Select Startup Item" menu, select `ICT398-Game-Engine.exe`
