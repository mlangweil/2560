cmake_minimum_required(VERSION 3.20)
project(2560)

set(CMAKE_CXX_STANDARD 14)

include_directories("Projects/Project 1/A")

add_executable(2560
        "Projects/Project 1/A/code.cpp"
        "Projects/Project 1/A/code.h"
        "Projects/Project 1/A/main.cpp")
