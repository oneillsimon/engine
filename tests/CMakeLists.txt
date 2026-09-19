cmake_minimum_required(VERSION 3.16)
project(tests)

include(FetchContent)

option(ENGINE_ENABLE_COVERAGE "Build the tests with code coverage instrumentation" OFF)

if(ENGINE_ENABLE_COVERAGE)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        message(FATAL_ERROR "Coverage is only supported on GCC/Clang.")
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
endif()

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_executable(
    engine-tests
    main.cpp
    src/application_test.cpp
    src/components/camera_component_test.cpp
    src/component_test.cpp
    src/engine_test.cpp
    src/entity_test.cpp
    src/glfw_input_processor_test.cpp
    src/rendering/glfw_window_test.cpp
    src/rendering/glsl_program_test.cpp
    src/scripting/lua_exception_test.cpp
    src/scripting/lua_test.cpp
)

target_link_libraries(engine-tests PRIVATE engine GTest::gtest)
target_include_directories(engine-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(engine-tests)
