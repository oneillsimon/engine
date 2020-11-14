//
// Created by simon on 14/11/2020.
//

#include <gtest/gtest.h>

#include <scripting/lua.h>
#include <scripting/lua_exception.h>

TEST(lua_exception_test, throw_exception) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    EXPECT_THROW({ load_file(L, "does-not-exist.lua"); }, lua_exception);

    lua_close(L);
}