cmake_minimum_required(VERSION 3.20)
project(nbody)

set(CMAKE_CXX_STANDARD 14)

add_executable(nbody src/main.cpp src/Triplet.cpp src/Triplet.h)
