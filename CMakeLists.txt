cmake_minimum_required(VERSION 3.14)

# Set the project name. This is not the executable program's name!
project(graphical_template)

# Try to find a locally installed raylib, but don't quit on fail
find_package(raylib 5.0 QUIET)

# This code downloads raylib into a directory called _deps and adds it as a subdirectory, compiling it with the program when running the build command
include(FetchContent)
if (NOT raylib_FOUND)
    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP True #This option is not required but suppresses a warning
    )
    FetchContent_MakeAvailable(raylib)
endif()

# We don't want raylib's examples built. This option is picked up by raylib's CMakeLists.txt
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Here, the executable is declared with its sources. "main", or "main.exe" on windows will be the program's name
add_executable(main "main.c")

# Link raylib to main
target_link_libraries(main 
    raylib
)
# Make main find the <raylib.h> header (and others)
target_include_directories(main PUBLIC "${raylib_SOURCE_DIR}/src")

if (EMSCRIPTEN)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lidbfs.js -s USE_GLFW=3 --shell-file ${CMAKE_CURRENT_LIST_DIR}/web/minshell.html --preload-file ${CMAKE_CURRENT_LIST_DIR}/resources/@resources/ -s GL_ENABLE_GET_PROC_ADDRESS=1")
    set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so that you can directly open it.
endif ()