cmake_minimum_required(VERSION 3.20)
project(nbody)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/matplotplusplus)

#add_executable(nbody src/main.cpp)


add_executable(nbody src/main.cpp src/Vector.cpp src/Vector.h src/Body.cpp src/Body.h src/System.cpp src/System.h src/Engine.cpp src/Engine.h src/StringTool.cpp src/StringTool.h src/Solver.cpp src/Solver.h src/Euler.cpp src/EulerImproved.cpp src/RK4.cpp src/RKGeneral.cpp src/RK4.cpp src/Ralston4.cpp)

target_link_libraries(nbody PUBLIC matplot)