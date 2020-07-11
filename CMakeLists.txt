cmake_minimum_required(VERSION 3.5)

project(radixtree)

add_executable(radix radixtree.h radixtree.cpp main.cpp)

set_target_properties(radix PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wall;-Wpedantic;-Wextra"
)