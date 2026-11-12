cmake_minimum_required(VERSION 3.20)

project(3d_spatial_engine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(raylib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main
    app/main.cpp
    src/particle.cpp
    src/grid.cpp
)

target_include_directories(main PRIVATE include)
target_link_libraries(main PRIVATE raylib)
