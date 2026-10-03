cmake_minimum_required(VERSION 3.22)
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
        tests_unit
        unit/application_test.cpp
        unit/component_test.cpp
        unit/engine_test.cpp
        unit/entity_test.cpp
)

set(
        tests_integration_graphics
        integration/graphics/glfw_input_processor_test.cpp
        integration/graphics/glfw_window_test.cpp
        integration/graphics/glsl_program_test.cpp
        integration/graphics/components/camera_component_test.cpp
)

set(
        tests_integration_scripting
        integration/scripting/lua_test.cpp
        integration/scripting/lua_exception_test.cpp
)

add_executable(tests_unit main.cpp ${tests_unit})
add_executable(tests_integration_graphics main.cpp  ${tests_integration_graphics})
add_executable(tests_integration_scripting main.cpp ${tests_integration_scripting})

target_link_libraries(tests_unit engine gtest gmock)
target_link_libraries(tests_integration_graphics engine gtest gmock)
target_link_libraries(tests_integration_scripting engine gtest gmock)

set(test_unit_properties
        LABELS headless
        LABELS unit
        TIMEOUT 10
)

set(test_integration_graphics_properties
        LABELS graphics
        LABELS integration
        TIMEOUT 10
)

set(test_integration_scripting_properties
        LABELS headless
        LABELS integration
        LABELS scripting
        TIMEOUT 10
)

if(ENGINE_USE_HEADLESS_GL)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(MESA_EGL REQUIRED egl)

    list(APPEND test_integration_graphics_properties ENVIRONMENT_MODIFICATION "DYLD_LIBRARY_PATH=path_list_prepend:${MESA_EGL_LIBDIR}")
    list(APPEND test_integration_graphics_properties ENVIRONMENT_MODIFICATION "LIBGL_ALWAYS_SOFTWARE=set:true")
    list(APPEND test_integration_graphics_properties ENVIRONMENT_MODIFICATION "GALLIUM_DRIVER=set:llvmpipe")
endif()

gtest_discover_tests(tests_unit PROPERTIES ${test_unit_properties})
gtest_discover_tests(tests_integration_graphics PROPERTIES ${test_integration_graphics_properties})
gtest_discover_tests(tests_integration_scripting PROPERTIES ${test_integration_scripting_properties})