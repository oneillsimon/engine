cmake_minimum_required(VERSION 3.16)

# Lua setup.
find_package(Lua 5.3.5 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

# SWIG setup.
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})
set(CMAKE_SWIG_FLAGS "")

add_library(
        engine
        application.h
        application.cpp
        engine.h
        engine.cpp
        gem/angle.h
        gem/constants.h
        gem/matrix.h
        gem/matrix4.h
        gem/quaternion.h
        gem/vector.h
        gem/vector2.h
        gem/vector3.h
        gem/vector4.h
        gem/vector_base.h
        gem/vector_iterator.h
        rendering/glfw_window.h
        rendering/glfw_window.cpp
        rendering/window.h
        rendering/window.cpp
        scripting/lua.h
        scripting/lua.cpp
        scripting/lua_exception.h
        scripting/lua_exception.cpp
)

set_source_files_properties("../swig-files/gem.i" PROPERTIES CPLUSPLUS ON)
set_source_files_properties("../swig-files/gem.i" PROPERTIES SWIG_FLAGS "-verbose")
swig_add_library(gem-swig-bindings TYPE STATIC LANGUAGE lua SOURCES "../swig-files/gem.i")
target_include_directories(gem-swig-bindings PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET gem-swig-bindings PROPERTY SWIG_USE_LIBRARY_INCLUDE_DIRECTORIES TRUE)


target_link_libraries(engine PUBLIC ${LUA_LIBRARIES} gem-swig-bindings)