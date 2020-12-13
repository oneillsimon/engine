#include <iostream>

#include "src/scripting/lua.h"

#include "src/applications/logl/learn_opengl_application.h"
#include "src/applications/logl-lighting/lighting_app.h"
#include "src/engine.h"
#include "src/rendering/glfw_window.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern "C" int luaopen_engine(lua_State* L);

int main() {
//    auto v = gem::vector2<int> { 1, 2 };
//    std::cout << v << std::endl;

//    auto v4 = gem::vector4<int>{ 101, 102, 304, 344 };
//    std::cout << v4 << std::endl;
//
//    lua_State* L = luaL_newstate();
//    luaL_openlibs(L);
//    luaopen_engine(L);
//
////    std::cout << v4<< std::endl;
//
//    try {
//        load_file(L, "../example.lua");
//    } catch (const std::exception& e) {
//        std::cerr << "Error running file " << e.what() << std::endl;
//    }
//
//    lua_close(L);
    auto window = new GlfwWindow("This is a window", 800, 600);
//    auto application = new LearnOpenGlApp();
    auto application = new LightingApp();
    auto engine = new Engine(application, window, 120);
    engine->start();
}