cmake_minimum_required(VERSION 3.16)
project(extern)

include(FetchContent)

# GLFW - windowing and input.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_X11 ON CACHE BOOL "" FORCE)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

# GLM - maths library.
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

# stb_image - image loading.
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
)
FetchContent_MakeAvailable(stb)
add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE ${stb_SOURCE_DIR})

# GLAD - OpenGL loader, generated at configure time for OpenGL 4.5 core
# with glad2 (https://github.com/Dav1dde/glad).
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.8
)
FetchContent_MakeAvailable(glad)
set(GLAD_CMAKE_DIR "${glad_SOURCE_DIR}/cmake" CACHE STRING "" FORCE)
set(GLAD_SOURCES_DIR "${glad_SOURCE_DIR}" CACHE STRING "" FORCE)
include(${GLAD_CMAKE_DIR}/GladConfig.cmake)
glad_add_library(glad STATIC API gl:core=4.5 EXTENSIONS NONE)
set_target_properties(glad PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(extern INTERFACE)
target_link_libraries(extern INTERFACE glad glfw glm::glm stb_image)
