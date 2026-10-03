cmake_minimum_required(VERSION 3.16)
project(tests)

include(GoogleTest)
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.18.0
)
FetchContent_MakeAvailable(googletest)

set(
        engine_tests
        unit/application_test.cpp
        unit/component_test.cpp
        unit/engine_test.cpp
        unit/entity_test.cpp

        integration/graphics/glfw_input_processor_test.cpp
        integration/graphics/glfw_window_test.cpp
        integration/graphics/glsl_program_test.cpp
        integration/graphics/components/camera_component_test.cpp

        integration/scripting/lua_test.cpp
        integration/scripting/lua_exception_test.cpp
)

add_executable(
        tests
        main.cpp
        ${engine_tests}
)

target_link_libraries(tests engine gtest gmock)

gtest_discover_tests(tests PROPERTIES TIMEOUT 10)