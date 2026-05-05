cmake_minimum_required(VERSION 4.1)
project(first_lab)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(first_lab
        matrix/matrix.h
        hand_work/hand_work.cpp
        hand_work/hand_work.h
        decompositions/gauss.cpp
        decompositions/gauss.h
        decompositions/LU.cpp
        decompositions/LU.h
        math_ops/math_ops.cpp
        math_ops/math_ops.h
        tests/tests.cpp
        tests/tests.h
        main.cpp
)