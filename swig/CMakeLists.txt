cmake_minimum_required(VERSION 3.16)

# SWIG Lua bindings, generated with a custom command so the build works with
# any SWIG that has Lua support, independent of CMake's SWIG module version.
find_program(SWIG_EXECUTABLE NAMES swig REQUIRED)

set(SWIG_GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${SWIG_GENERATED_DIR})
set(SWIG_WRAP_FILE ${SWIG_GENERATED_DIR}/engine_wrap.cxx)

add_custom_command(
    OUTPUT ${SWIG_WRAP_FILE}
    COMMAND ${SWIG_EXECUTABLE} -lua -c++ -o ${SWIG_WRAP_FILE} ${CMAKE_CURRENT_SOURCE_DIR}/swig.i
    DEPENDS
        swig.i
        application.i
        component.i
        engine.i
        entity.i
        glfw_input_processor.i
        input_processor.i
        lua_application.i
        lua_callbacks.i
        components/camera_component.i
        rendering/glfw_window.i
        rendering/window.i
        utils.h
        utils.cpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating SWIG Lua bindings"
    VERBATIM
)

add_library(engine-swig-bindings SHARED ${SWIG_WRAP_FILE})
target_include_directories(engine-swig-bindings PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(engine-swig-bindings PUBLIC engine)
set_property(TARGET engine-swig-bindings PROPERTY CXX_CLANG_TIDY "")
