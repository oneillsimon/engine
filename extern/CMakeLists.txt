project(extern)
cmake_minimum_required(VERSION 3.16)

add_library(glad glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw-3.3.2)
include_directories(glfw-3.3.2/include)

add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE stb_image)

add_library(glm INTERFACE)
target_include_directories(glm INTERFACE glm)

add_subdirectory(assimp-5.0.1)
include_directories(assimp-5.0.1/include)

add_library(extern INTERFACE)
target_link_libraries(extern INTERFACE glad glfw stb_image glm assimp)