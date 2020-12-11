cmake_minimum_required(VERSION 3.16)
project(tests)

add_subdirectory(extern/googletest)

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
        ../src/engine.h
        ../src/engine.cpp
        ../src/rendering/glfw_window.h
        ../src/rendering/glfw_window.cpp
        ../src/rendering/shader.h
        ../src/rendering/shader.cpp
        ../src/rendering/shader_program.h
        ../src/rendering/shader_program.cpp
        ../src/rendering/window.h
        ../src/rendering/window.cpp
        ../src/scripting/lua.h
        ../src/scripting/lua.cpp
        ../src/scripting/lua_exception.h
        ../src/scripting/lua_exception.cpp
        ../src/rendering/stb_image_implementation.cpp ../src/entity.cpp ../src/entity.h ../src/component.cpp ../src/component.h ../src/input_processor.cpp ../src/input_processor.h ../src/glfw_input_processor.cpp ../src/glfw_input_processor.h ../src/components/camera_component.cpp ../src/components/camera_component.h)

set(
        engine_tests
        src/engine_test.cpp
        src/scripting/lua_test.cpp
        src/scripting/lua_exception_test.cpp
)

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
        COMMAND lcov --remove ${COVERAGE_TOTAL_INFO_FILE} -o ${COVERAGE_TOTAL_INFO_FILE} '/usr/include/*' '/usr/lib/*' '*/tests/*' '*/extern/*'

        COMMAND genhtml --legend ${COVERAGE_TOTAL_INFO_FILE} -o ${COVERAGE_DIR}/html
        DEPENDS tests
)
add_custom_target(coverage DEPENDS coverage-cmd)