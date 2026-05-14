cmake_minimum_required(VERSION 3.14)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
project(first_lab)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(third_lab
        matrix/matrix.h
        hand_work/hand_work.cpp
        hand_work/hand_work.h
        decompositions/gauss.h
        decompositions/LU.h
        math_ops/math_ops.cpp
        math_ops/math_ops.h
        tests/tests.cpp
        tests/tests.h
        main.cpp
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)
add_compile_options(-U__STRICT_ANSI__)
FetchContent_MakeAvailable(googletest)

add_executable(run_gtests
        tests/test_dynamic_array.cpp
        tests/test_vector.cpp
        tests/test_decompositions.cpp
        tests/test_matrix_types_gtest.cpp
        math_ops/math_ops.cpp
)
target_link_libraries(run_gtests gtest_main)