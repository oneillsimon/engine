#include <iostream>

#include "src/gem/vector2.h"
#include "src/gem/vector4.h"

#include "src/scripting/lua.h"

#include "applications/logl/learn_opengl_application.h"
#include "engine.h"
#include "rendering/glfw_window.h"

extern "C" int luaopen_gem(lua_State* L);

int main() {
//    auto v = gem::vector2<int> { 1, 2 };
//    std::cout << v << std::endl;

    auto v4 = gem::vector4<int>{ 101, 102, 304, 344 };
//    std::cout << v4 << std::endl;

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_gem(L);

    std::cout << v4<< std::endl;

    try {
        load_file(L, "../example.lua");
    } catch (const std::exception& e) {
        std::cerr << "Error running file " << e.what() << std::endl;
    }

    lua_close(L);

    auto window = new GlfwWindow("This is a window", 800, 600);
    auto application = new LearnOpenGlApp();
    auto engine = new Engine(application, window, 60);
    engine->start();
}