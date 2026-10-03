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
        excluded_engine_srcs
        ../src/rendering/mesh/triangle_mesh.cpp
        ../src/rendering/mesh/triangle_mesh.h
        ../src/rendering/mesh/examples/torus.h
        ../src/rendering/mesh/examples/torus.cpp
)
# Adjust the file paths to work with lcov --remove option.
string(REPLACE "../src" "*/src" excluded_engine_srcs "${excluded_engine_srcs}")

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

set(COVERAGE_DIR ${PROJECT_BINARY_DIR}/CMakeFiles/coverage.dir)
set(COVERAGE_BASE_INFO_FILE ${COVERAGE_DIR}/coverage_base.info)
set(COVERAGE_INFO_FILE ${COVERAGE_DIR}/coverage.info)
set(COVERAGE_TOTAL_INFO_FILE ${COVERAGE_DIR}/coverage_total.info)

add_custom_command(
        OUTPUT  coverage-cmd

        COMMAND lcov -c -i -d . -o ${COVERAGE_BASE_INFO_FILE}
        COMMAND ./tests
        COMMAND lcov --directory . --capture --output-file ${COVERAGE_INFO_FILE}

        COMMAND lcov -a ${COVERAGE_BASE_INFO_FILE} -a ${COVERAGE_INFO_FILE} -o ${COVERAGE_TOTAL_INFO_FILE}
        COMMAND lcov --remove ${COVERAGE_TOTAL_INFO_FILE} -o ${COVERAGE_TOTAL_INFO_FILE} '/usr/include/*' '/usr/lib/*' '*/tests/*' '*/extern/*' ${excluded_engine_srcs}

        COMMAND genhtml --legend ${COVERAGE_TOTAL_INFO_FILE} -o ${COVERAGE_DIR}/html
        DEPENDS tests
)
add_custom_target(coverage DEPENDS coverage-cmd)