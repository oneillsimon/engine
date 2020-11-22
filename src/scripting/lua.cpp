//
// Created by simon on 03/11/2020.
//

#include "lua.h"
#include "lua_exception.h"

void load_file(lua_State* L, const std::string& filename) {
    if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) {
        throw lua_exception(L);
    }
}
