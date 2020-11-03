cmake_minimum_required(VERSION 3.16)
project(tests)

set(CMAKE_CXX_FLAGS "--coverage")

include_directories(../src ../gem/src)
add_library(
        tests
        gem/angle_test.cpp
        gem/vector2_test.cpp
        gem/vector3_test.cpp
        gem/vector4_test.cpp
        gem/quaternion_test.cpp
        gem/matrix_test.cpp
        gem/matrix4_test.cpp
)

target_include_directories(
        tests PUBLIC
        ../extern/googletest/googletest/include
        ../extern/googletest/googletest
)
