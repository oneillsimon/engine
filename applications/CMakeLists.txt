cmake_minimum_required(VERSION 3.16)
project(applications)

add_library(applications INTERFACE)

target_link_libraries(applications INTERFACE extern)
target_link_libraries(applications INTERFACE engine)
