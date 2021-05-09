cmake_minimum_required(VERSION 3.16)
project(tests)

add_subdirectory(extern/googletest)

find_package(GTest REQUIRED)

SET(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 --coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include_directories(
        extern/googletest/googletest/include
        extern/googletest/googletest
        ../src
)

set(
        engine_srcs
        ../src/application.h
        ../src/application.cpp
        ../src/component.h
        ../src/component.cpp
        ../src/engine.h
        ../src/engine.cpp
        ../src/entity.h
        ../src/entity.cpp
        ../src/glfw_input_processor.h
        ../src/glfw_input_processor.cpp
        ../src/input_processor.h
        ../src/input_processor.cpp

        ../src/components/camera_component.h
        ../src/components/camera_component.cpp

        ../src/rendering/glfw_window.h
        ../src/rendering/glfw_window.cpp
        ../src/rendering/glsl_exception.h
        ../src/rendering/glsl_exception.cpp
        ../src/rendering/glsl_program.h
        ../src/rendering/glsl_program.cpp
        ../src/rendering/stb_image_implementation.cpp
        ../src/rendering/window.h
        ../src/rendering/window.cpp
        ../src/rendering/lights/attenuation.h
        ../src/rendering/lights/attenuation.cpp
        ../src/rendering/lights/directional_light.h
        ../src/rendering/lights/directional_light.cpp
        ../src/rendering/lights/light.h
        ../src/rendering/lights/light.cpp
        ../src/rendering/lights/point_light.h
        ../src/rendering/lights/point_light.cpp
        ../src/rendering/lights/spot_light.h
        ../src/rendering/lights/spot_light.cpp
        ../src/rendering/material/material.h
        ../src/rendering/material/material.cpp
        ../src/rendering/mesh/mesh.h

        ../src/scripting/lua.h
        ../src/scripting/lua.cpp
        ../src/scripting/lua_exception.h
        ../src/scripting/lua_exception.cpp
)

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
        src/application_test.cpp
        src/engine_test.cpp
        src/entity_test.cpp
        src/component_test.cpp
        src/glfw_input_processor_test.cpp
        src/components/camera_component_test.cpp
        src/scripting/lua_test.cpp
        src/scripting/lua_exception_test.cpp
        src/rendering/glfw_window_test.cpp src/rendering/glsl_program_test.cpp)

add_executable(
        tests
        main.cpp
        ${engine_srcs}
        ${engine_tests}
)

target_link_libraries(tests engine gtest)

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