cmake_minimum_required(VERSION 3.16)

# Lua setup.
find_package(Lua 5.4.0 REQUIRED)

include_directories(${LUA_INCLUDE_DIR})
#link_libraries(${LUA_LIBRARIES})

## SWIG setup.
#find_package(SWIG REQUIRED)
#include(${SWIG_USE_FILE})
#set(CMAKE_SWIG_FLAGS "")

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
  scripting/lua.h
  scripting/lua.cpp
  scripting/lua_exception.h
  scripting/lua_exception.cpp
  ../swig/utils.h
  ../swig/utils.cpp)

if(ENGINE_USE_HEADLESS_GL)
  target_compile_definitions(engine PRIVATE ENGINE_USE_HEADLESS_GL)
endif()

add_custom_target(copy-resources ALL)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SHADERS_DIR}")
  add_custom_command(
    TARGET copy-resources
    POST_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy_directory
      "${CMAKE_CURRENT_SOURCE_DIR}/${SHADERS_DIR}"
      "${CMAKE_CURRENT_BINARY_DIR}/../${SHADERS_DIR}"
    COMMENT "Copying shaders...")
else()
  message(STATUS "Shaders directory not found; skipping copy.")
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${TEXTURES_DIR}")
  add_custom_command(
    TARGET copy-resources
    POST_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy_directory
      "${CMAKE_CURRENT_SOURCE_DIR}/${TEXTURES_DIR}"
      "${CMAKE_CURRENT_BINARY_DIR}/../${TEXTURES_DIR}"
    COMMENT "Copying textures...")
else()
  message(STATUS "Textures directory not found; skipping copy.")
endif()

add_dependencies(engine copy-resources)

target_link_libraries(engine PUBLIC ${LUA_LIBRARIES})
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(engine PUBLIC ${LUA_INCLUDE_DIR})
