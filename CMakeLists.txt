cmake_minimum_required(VERSION 3.10)
project(elevator_system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compile the solution
add_executable(code solution.cpp)

# Set compiler flags for optimization
target_compile_options(code PRIVATE -O2 -Wall)