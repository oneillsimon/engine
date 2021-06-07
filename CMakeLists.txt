cmake_minimum_required(VERSION 3.16)
project(engine VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(extern)
add_subdirectory(src)
add_subdirectory(swig)
add_subdirectory(applications)
add_subdirectory(tests)

add_executable(engine-exe main.cpp)

target_link_libraries(engine PUBLIC extern engine-swig-bindings)
target_link_libraries(engine-swig-bindings PUBLIC engine)

target_link_libraries(engine-exe PUBLIC engine applications)
