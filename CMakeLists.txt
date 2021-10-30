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

add_executable(nbody src/main.cpp src/Vector.cpp src/Vector.h src/Body.cpp src/Body.h src/System.cpp src/System.h src/Engine.cpp src/Engine.h src/StringTool.cpp src/StringTool.h src/Solver.cpp src/Solver.h src/Euler.cpp src/EulerImproved.cpp src/RK4.cpp src/RKGeneral.cpp src/RK4.cpp src/Ralston4.cpp)

target_link_libraries(nbody PUBLIC matplot)