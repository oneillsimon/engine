project(extern)
cmake_minimum_required(VERSION 3.16)

include(FetchContent)

add_library(glad glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.5.1
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
        stb_image
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG 013ac3beddff3dbffafd5177e7972067cd2b5083
)
FetchContent_MakeAvailable(stb_image)

add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE ${stb_image_SOURCE_DIR})

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.3
)
FetchContent_MakeAvailable(glm)

add_library(extern INTERFACE)
target_link_libraries(extern INTERFACE glad glfw stb_image glm::glm)
