cmake_minimum_required(VERSION 3.20)
project(nbody)

set(CMAKE_CXX_STANDARD 14)

add_executable(nbody src/main.cpp src/Triplet.cpp src/Triplet.h src/Body.cpp src/Body.h src/System.cpp src/System.h src/Engine.cpp src/Engine.h src/Constants.h src/StringTool.h src/StringTool.cpp)
