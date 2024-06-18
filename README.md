# Extent
Demonstrates a the build process of a **simple & portable** raylib application for Desktop / Web.

- (Static) assets passed via `--preload-file` for Web
- Dynamic files using IDBFS (browser storage)

# Usage
```sh
git clone https://github.com/manuel5975p/raylib-cmake-template.git
cd raylib-cmake-template
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug #Can also be =Release, =RelWithDebInfo, nothing defaults to Debug
make -j4
./main
```
## Usage for Web
Requires [emscripten](https://emscripten.org/docs/getting_started/downloads.html).

```sh
mkdir build_web && cd build_web
emcmake cmake .. -DCMAKE_BUILD_TYPE=Release -DPLATFORM=Web
make -j4
```
## Usage with VSCode

- Open the `raylib-cmake-template` directory in VSCode
- Make sure the "C/C++" extension as well "CMake Tools" are installed
- Also have a compiler installed (e.g. [the latest w64devkit](https://github.com/skeeto/w64devkit/releases))
- Hit the debug, build button or hit Ctrl+Shift+P for the command menu and run "CMake: Debug" or something similar

