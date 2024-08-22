cmake_minimum_required(VERSION 3.13)  # CMake version check
project(sodoku_solver)                # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

include_directories(
        ${PROJECT_SOURCE_DIR}/lib
        ${PROJECT_SOURCE_DIR}/src
)
        
        file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/lib/*.hpp"
        "${PROJECT_SOURCE_DIR}/lib/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
)
        
add_executable(sodoku_solver ${all_SRCS})
add_executable(
        Mytest ${PROJECT_SOURCE_DIR}/test/test.cpp 
        ${PROJECT_SOURCE_DIR}/test/acutest.h 
        ${PROJECT_SOURCE_DIR}/lib/sodoku.hpp 
        ${PROJECT_SOURCE_DIR}/lib/sodoku.cpp
)