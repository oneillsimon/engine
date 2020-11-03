cmake_minimum_required(VERSION 3.16)
project(engine VERSION 1.0.0)


add_subdirectory(src)
add_subdirectory(gem)

add_executable(engine-exe main.cpp)

target_link_libraries(engine-exe PUBLIC engine)

target_link_libraries(engine-exe PUBLIC gem-lua)
target_link_libraries(engine-exe PUBLIC gem)

add_subdirectory(extern/googletest)
add_subdirectory(tests)

add_executable(tests-exe tests/main.cpp)
target_link_libraries(tests-exe PUBLIC tests)
target_link_libraries(tests-exe PUBLIC engine)
target_link_libraries(tests-exe PUBLIC gem)
target_link_libraries(tests-exe PUBLIC gtest gtest_main)
