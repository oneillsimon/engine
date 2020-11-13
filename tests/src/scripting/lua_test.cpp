//
// Created by simon on 11/11/2020.
//

#include <gtest/gtest.h>

#include <scripting/lua.h>

TEST(lua_test, error) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

//    load_file(L, "");

    lua_close(L);
}