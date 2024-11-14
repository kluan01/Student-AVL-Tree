cmake_minimum_required(VERSION 3.28)
project(Gator_AVL)

set(CMAKE_CXX_STANDARD 17)

add_executable(Gator_AVL AVL.cpp
        AVL.h
        test-unit/test.cpp
)
