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

        applications/cookbook/Chapter_1/CB_Chapter1_app.h
        applications/cookbook/Chapter_1/CB_Chapter1_app.cpp
        applications/cookbook/Chapter_1/CB_Chapter1_blob_app.h
        applications/cookbook/Chapter_1/CB_Chapter1_blob_app.cpp

        components/camera_component.h
        components/camera_component.cpp

        rendering/glfw_window.h
        rendering/glfw_window.cpp
        rendering/glsl_program.h
        rendering/glsl_program.cpp
        rendering/glsl_exception.h
        rendering/glsl_exception.cpp
        rendering/stb_image_implementation.cpp
        rendering/window.h
        rendering/window.cpp
        rendering/lights/attenuation.h
        rendering/lights/attenuation.cpp
        rendering/lights/directional_light.h
        rendering/lights/directional_light.cpp
        rendering/lights/light.h
        rendering/lights/light.cpp
        rendering/lights/point_light.h
        rendering/lights/point_light.cpp
        rendering/lights/spot_light.h
        rendering/lights/spot_light.cpp

        scripting/lua.h
        scripting/lua.cpp
        scripting/lua_exception.h
        scripting/lua_exception.cpp
        rendering/mesh/mesh.h rendering/mesh/triangle_mesh.cpp rendering/mesh/triangle_mesh.h rendering/mesh/examples/torus.cpp rendering/mesh/examples/torus.h applications/cookbook/Chapter_2/DiffuseShadingApp.cpp applications/cookbook/Chapter_2/DiffuseShadingApp.h applications/cookbook/Chapter_2/ADSShadingApp.cpp applications/cookbook/Chapter_2/ADSShadingApp.h rendering/material/material.cpp rendering/material/material.h applications/cookbook/Chapter_2/TwoSideShadingApp.cpp applications/cookbook/Chapter_2/TwoSideShadingApp.h rendering/mesh/examples/teapot.cpp rendering/mesh/examples/teapot.h applications/cookbook/Chapter_2/FlatADSShadingApp.cpp applications/cookbook/Chapter_2/FlatADSShadingApp.h)

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