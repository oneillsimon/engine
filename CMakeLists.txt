cmake_minimum_required(VERSION 3.16)
project(engine VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENGINE_BUILD_TESTS "Build the engine test suite" ON)
option(ENGINE_BUILD_APPLICATIONS "Build the cookbook sample applications" ON)
option(ENGINE_ENABLE_CLANG_TIDY "Run clang-tidy during compilation" OFF)

if(ENGINE_ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if(CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
    endif()
endif()

add_subdirectory(extern)
add_subdirectory(src)
add_subdirectory(swig)

if(ENGINE_BUILD_APPLICATIONS)
    add_subdirectory(applications)
endif()

if(ENGINE_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

add_executable(engine-exe main.cpp)
target_link_libraries(engine-exe PRIVATE engine applications engine-swig-bindings)
