#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "src/scripting/lua.h"

#include "applications/cookbook/Chapter_1/CB_Chapter1_blob_app.h"
#include "applications/cookbook/Chapter_2/DiffuseShadingApp.h"
#include "applications/cookbook/Chapter_2/ADSShadingApp.h"
#include "applications/cookbook/Chapter_2/TwoSideShadingApp.h"
//#include "applications/cookbook/Chapter_2/FlatADSShadingApp.h"
#include "applications/cookbook/Chapter_2/SubroutineApp.h"
#include "applications/cookbook/Chapter_2/DiscardShadingApp.h"
#include "src/engine.h"
#include "src/rendering/glfw_window.h"

#define LUA_GAME true

extern "C" int luaopen_engine(lua_State* L);

int main() {
//    auto v = gem::vector2<int> { 1, 2 };
//    std::cout << v << std::endl;
//
//    auto v4 = gem::vector4<int>{ 101, 102, 304, 344 };
//    std::cout << v4 << std::endl;

#if LUA_GAME
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_engine(L);

//    std::cout << v4<< std::endl;

    try {
        load_file(L, "../example.lua");
    } catch (const std::exception& e) {
        std::cerr << "Error running file " << e.what() << std::endl;
        exit(1);
    }

    lua_close(L);
#else
    auto window = new GlfwWindow("This is a window", 800, 600);
//    auto application = new LearnOpenGlApp();
//    auto application = new LightingApp();
//    auto application = new DiffuseShadingApp();
//    auto application = new ADSShadingApp();
//    auto application = new TwoSideShadingApp();
//    auto application = new FlatADSShadingApp();
//    auto application = new SubroutineApp();
    auto application = new DiscardShadingApp();
    auto engine = new Engine(application, window, 120);


    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);

    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    std::cout << "GL Vendor: " << vendor << std::endl;
    std::cout << "GL Renderer: " << renderer << std::endl;
    std::cout << "GL Version (string): " << version << std::endl;
    std::cout << "GL Version (number): " << major << "." << minor << std::endl;
    std::cout << "GLSL Version: " << glsl_version << std::endl;


    engine->start();
#endif
}