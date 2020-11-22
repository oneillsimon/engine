//
// Created by simon on 28/10/2020.
//

#ifndef ENGINE_LUA_H
#define ENGINE_LUA_H

#include <string>

#include <lua.hpp>

void load_file(lua_State* L, const std::string& filename);

#endif //ENGINE_LUA_H
