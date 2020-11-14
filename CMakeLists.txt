cmake_minimum_required(VERSION 3.16)
project(engine VERSION 1.0.0)

add_subdirectory(extern)
add_subdirectory(src)
add_subdirectory(tests)

add_executable(engine-exe main.cpp)

target_link_libraries(engine PUBLIC extern)
target_link_libraries(engine-exe PUBLIC engine)
