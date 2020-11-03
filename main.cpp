#include <iostream>

#include <gem/vector2.h>
#include <gem/vector4.h>

#include "src/scripting/lua.h"

extern "C" int luaopen_gem(lua_State* L);

int main() {
//    auto v = gem::vector2<int> { 1, 2 };
//    std::cout << v << std::endl;

//    auto v4 = gem::vector4<int>{ 101, 102, 304, 344 };
//    std::cout << v4 << std::endl;

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_gem(L);

//    std::cout << double_int(6) << std::endl;

    load_file(L, "../example.lua");

    lua_close(L);
}