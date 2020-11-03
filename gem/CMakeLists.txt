project(gem)
cmake_minimum_required(VERSION 3.16)

find_package(Lua 5.3.5 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

find_package(SWIG REQUIRED)
message(SWIG_USE_FILE ${SWIG_USE_FILE})
include(${SWIG_USE_FILE})
set(CMAKE_SWIG_FLAGS "")

set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/src/swig/gem.i" PROPERTIES CPLUSPLUS ON)
set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/src/swig/gem.i" PROPERTIES SWIG_FLAGS "-verbose")
swig_add_library(gem-lua TYPE STATIC LANGUAGE lua SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/swig/gem.i")
swig_link_libraries(gem-lua ${LUA_LIBRARIES})
set_property(TARGET gem-lua PROPERTY SWIG_USE_LIBRARY_INCLUDE_DIRECTORIES TRUE)
target_include_directories(gem-lua INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(gem INTERFACE)
target_include_directories(gem INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")