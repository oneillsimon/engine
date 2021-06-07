cmake_minimum_required(VERSION 3.16)

# SWIG setup.
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})
set(CMAKE_SWIG_FLAGS "")

#add_library(glad_2 ../extern/glad/src/glad.c)
#target_include_directories(glad_2 PUBLIC ../extern/glad/include)

set_source_files_properties("swig.i" PROPERTIES CPLUSPLUS ON)
set_source_files_properties("swig.i" PROPERTIES SWIG_FLAGS "-verbose")
swig_add_library(engine-swig-bindings TYPE USE_BUILD_SHARED_LIBS LANGUAGE lua SOURCES "swig.i")
target_include_directories(engine-swig-bindings PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET engine-swig-bindings PROPERTY SWIG_USE_LIBRARY_INCLUDE_DIRECTORIES TRUE)
set_target_properties(engine-swig-bindings PROPERTIES CXX_CLANG_TIDY "")

#add_library(swig-bindings PUBLIC engine-swig-bindings)
