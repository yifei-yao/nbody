cmake_minimum_required(VERSION 3.20)
project(nbody)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(matplotplusplus GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus GIT_TAG origin/master)

FetchContent_GetProperties(matplotplusplus)

if (NOT matplotplusplus_POPULATED)
    FetchContent_Populate(matplotplusplus)
    add_subdirectory(${matplotplusplus_SOURCE_DIR} ${matplotplusplus_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()

add_executable(nbody src/nbody.cpp src/triplet.cpp src/triplet.h src/body.cpp src/body.h src/system.cpp src/system.h src/engine.cpp src/engine.h src/string_tool.cpp src/string_tool.h src/solver.cpp src/solver.h src/euler.cpp src/euler_improved.cpp src/rk4.cpp src/rk_general.cpp src/rk4.cpp src/ralston4.cpp)

target_link_libraries(nbody PUBLIC matplot)