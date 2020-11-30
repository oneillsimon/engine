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
        applications/logl/learn_opengl_application.h
        applications/logl/learn_opengl_application.cpp
        rendering/glfw_window.h
        rendering/glfw_window.cpp
        rendering/shader_program.h
        rendering/shader_program.cpp
        rendering/window.h
        rendering/window.cpp
        scripting/lua.h
        scripting/lua.cpp
        scripting/lua_exception.h
        scripting/lua_exception.cpp
        rendering/shader.h
        rendering/shader.cpp
        rendering/stb_image_implementation.cpp
)

set_source_files_properties("swig/swig.i" PROPERTIES CPLUSPLUS ON)
set_source_files_properties("swig/swig.i" PROPERTIES SWIG_FLAGS "-verbose")
swig_add_library(engine-swig-bindings TYPE SHARED LANGUAGE lua SOURCES "swig/swig.i")
target_include_directories(engine-swig-bindings PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET engine-swig-bindings PROPERTY SWIG_USE_LIBRARY_INCLUDE_DIRECTORIES TRUE)


add_custom_target(
    copy-resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${CMAKE_CURRENT_BINARY_DIR}/../shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/textures ${CMAKE_CURRENT_BINARY_DIR}/../textures
)

add_dependencies(engine copy-resources)

target_link_libraries(engine PUBLIC ${LUA_LIBRARIES} engine-swig-bindings)