cmake_minimum_required(VERSION 3.16)

# Lua setup.
find_package(Lua 5.4.0 REQUIRED)

include_directories(${LUA_INCLUDE_DIR})

# SWIG setup.
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})
set(CMAKE_SWIG_FLAGS "")

add_library(
        engine
        application.h
        application.cpp
        component.h
        component.cpp
        engine.h
        engine.cpp
        entity.h
        entity.cpp
        glfw_input_processor.h
        glfw_input_processor.cpp
        input_processor.h
        input_processor.cpp
        applications/logl/learn_opengl_application.h
        applications/logl/learn_opengl_application.cpp
        components/camera_component.h
        components/camera_component.cpp
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
        applications/logl-lighting/lighting_app.cpp applications/logl-lighting/lighting_app.h)

set_source_files_properties("swig/swig.i" PROPERTIES CPLUSPLUS ON)
set_source_files_properties("swig/swig.i" PROPERTIES SWIG_FLAGS "-verbose")
swig_add_library(engine-swig-bindings TYPE SHARED LANGUAGE lua SOURCES "swig/swig.i")
target_include_directories(engine-swig-bindings PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET engine-swig-bindings PROPERTY SWIG_USE_LIBRARY_INCLUDE_DIRECTORIES TRUE)

set(SHADERS_DIR shaders)
set(TEXTURES_DIR resources/textures)

add_custom_target(
    copy-resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/${SHADERS_DIR} ${CMAKE_CURRENT_BINARY_DIR}/../${SHADERS_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/${TEXTURES_DIR} ${CMAKE_CURRENT_BINARY_DIR}/../${TEXTURES_DIR}
)

add_dependencies(engine copy-resources)

target_include_directories(engine PUBLIC ${LUA_INCLUDE_DIR})
target_link_libraries(engine PUBLIC ${LUA_LIBRARIES} engine-swig-bindings)