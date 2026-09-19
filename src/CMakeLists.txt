cmake_minimum_required(VERSION 3.16)

# Lua.
find_package(Lua 5.4 REQUIRED)

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
    rendering/material/material.h
    rendering/material/material.cpp
    rendering/mesh/mesh.h
    rendering/mesh/examples/teapot.cpp
    rendering/mesh/examples/teapot.h
    rendering/mesh/examples/torus.cpp
    rendering/mesh/examples/torus.h
    rendering/mesh/triangle_mesh.h
    rendering/mesh/triangle_mesh.cpp
    scripting/lua.h
    scripting/lua.cpp
    scripting/lua_exception.h
    scripting/lua_exception.cpp
    ../swig/utils.h
    ../swig/utils.cpp
)

target_link_libraries(engine PUBLIC extern ${LUA_LIBRARIES})
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${LUA_INCLUDE_DIR})
set_target_properties(engine PROPERTIES POSITION_INDEPENDENT_CODE ON)

set(SHADERS_DIR shaders)
set(TEXTURES_DIR resources/textures)
add_custom_target(
    copy-resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/${SHADERS_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${SHADERS_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/${TEXTURES_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${TEXTURES_DIR}
)
add_dependencies(engine copy-resources)
