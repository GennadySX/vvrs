cmake_minimum_required(VERSION 3.16)
project(lab_1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp")

add_executable(lab_1 main.cpp)