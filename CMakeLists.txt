cmake_minimum_required(VERSION 3.16)
project(engine VERSION 1.0.0)

option(ENGINE_USE_HEADLESS_GL "Use headless GLFW Null with EGL" OFF)
option(ENGINE_ENABLE_COVERAGE "Enable code coverage instrumentation" OFF)

if(ENGINE_ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
        add_link_options(-fprofile-instr-generate)
    else()
        add_compile_options(--coverage)
        add_link_options(--coverage)
    endif()
endif()

set(CMAKE_CXX_STANDARD 20)

include(CTest)

add_subdirectory(extern)
add_subdirectory(src)
add_subdirectory(swig)
add_subdirectory(applications)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_executable(engine-exe main.cpp)

target_link_libraries(engine PUBLIC extern engine-swig-bindings)
target_link_libraries(engine-swig-bindings PUBLIC engine)

target_link_libraries(engine-exe PUBLIC engine applications)
