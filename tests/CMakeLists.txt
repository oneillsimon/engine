cmake_minimum_required(VERSION 3.16)
project(tests)

add_subdirectory(extern/googletest)

SET(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 --coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include_directories(
        extern/googletest/googletest/include
        extern/googletest/googletest
        ../gem/src
        ../src
)

set(
        engine_srcs
        ../src/scripting/lua.h
        ../src/scripting/lua.cpp
)

set(
        engine_tests
        gem/angle_test.cpp
        gem/constants_test.cpp
        gem/vector_test.cpp
        gem/vector2_test.cpp
        gem/vector3_test.cpp
        gem/vector4_test.cpp
        gem/vector_base_test.cpp
        gem/vector_iterator_test.cpp
        gem/quaternion_test.cpp
        gem/matrix_test.cpp
        gem/matrix4_test.cpp
        src/scripting/lua_test.cpp
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
        COMMAND lcov --remove ${COVERAGE_TOTAL_INFO_FILE} -o ${COVERAGE_TOTAL_INFO_FILE} '/usr/include/*' '/usr/lib/*' '*/tests/*'

        COMMAND genhtml --legend ${COVERAGE_TOTAL_INFO_FILE} -o ${COVERAGE_DIR}/html
        DEPENDS tests
)
add_custom_target(coverage DEPENDS coverage-cmd)