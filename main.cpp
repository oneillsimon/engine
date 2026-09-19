#include <iostream>
#include <lua.hpp>
#include "src/scripting/lua.h"
#include "src/engine.h"
#include "src/rendering/glfw_window.h"

extern "C" int luaopen_engine(lua_State* L);

// Runs the Lua example (example.lua), which builds the window, application
// and components from script via the SWIG bindings.
int run_lua_game() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_engine(L);
    int result = 0;
    try {
        load_file(L, "example.lua");
    } catch (const std::exception& e) {
        std::cerr << "Error running file " << e.what() << std::endl;
        result = 1;
    }
    lua_close(L);
    return result;
}

int main() {
    return run_lua_game();
}
