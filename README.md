# YOKAI-Runtime

### Dependencies
* Linux: `apt install build-essential clang ninja-build clang-9 \
  libstdc++-9-dev ninja-build libgl1-mesa-dev libx11-dev \
  libxrandr-dev libudev-dev libfreetype6-dev \
  libopenal-dev libflac++-dev libvorbis-dev \
  libxinerama-dev libxcursor-dev libxi-dev`
* macOS: `brew install cmake ninja llvm`
* Windows: `None` 
### Building

#### Linux & macOS:
```
CXX=clang++ cmake -S . -B build -G Ninja -D CMAKE_BUILD_TYPE=Release
```
Change directory to whatever you specified X as.
```
cmake --build . && ./YOKAI_RUNTIME
```
#### Windows:
    * Open Visual Studio as Administrator (required to make symbolic links)
    * Press Continue without Code
    * In Visual Studio, select Open → CMake, Navigate to the project folder and select `CMakeLists.txt`
    * From the "Select Startup Item" menu, select `YOKAI_RUNTIME.exe`
