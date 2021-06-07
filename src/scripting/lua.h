//
// Created by simon on 28/10/2020.
//

#ifndef ENGINE_LUA_H
#define ENGINE_LUA_H

#include <iostream>
#include <string>

#include <lua.hpp>

void load_file(lua_State* L, const std::string& filename);
void dump_stack(lua_State* L);

#endif //ENGINE_LUA_H
