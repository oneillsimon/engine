//
// Created by simon on 14/11/2020.
//

#include <gtest/gtest.h>

#include <scripting/lua.h>
#include <scripting/lua_exception.h>

TEST(lua_exception_test, throw_exception) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    std::string exception_str = std::string();

    try {
        load_file(L, "does_not_exist.lua");
    } catch (const lua_exception& e) {
        exception_str = e.what();
    }

    lua_close(L);
    EXPECT_STREQ("cannot open does_not_exist.lua: No such file or directory", exception_str.c_str());
};