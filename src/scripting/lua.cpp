//
// Created by simon on 03/11/2020.
//

#include "lua.h"

void error(lua_State* L, const char* message, ...)  {
    va_list argp;
    va_start(argp, message);
    vfprintf(stderr, message, argp);
    va_end(argp);
    // TODO: rewrite to throw an exception instead of just exiting.
    exit(EXIT_FAILURE);
}

void load_file(lua_State* L, const std::string& filename) {
    if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) {
        error(L, "Error in file: '%s'\n", lua_tostring(L, -1));
    }
}