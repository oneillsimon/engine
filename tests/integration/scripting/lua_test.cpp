//
// Created by simon on 11/11/2020.
//

#include <fstream>
#include <iostream>

#include <gtest/gtest.h>

#include <scripting/lua.h>
#include <scripting/lua_exception.h>

TEST(lua_test, load_file) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // Create a simple lua file.
    std::ofstream lua_file;
    std::string file_name = "test.lua";
    lua_file.open(file_name);
    lua_file << "print(\"Hello, world!\")\n";
    lua_file.close();

    EXPECT_NO_THROW(load_file(L, file_name));

    lua_close(L);
    std::remove(file_name.c_str());
}

TEST(lua_test, load_file_not_found) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    EXPECT_THROW(load_file(L, "does_not_exist.lua"), lua_exception);

    lua_close(L);
}
