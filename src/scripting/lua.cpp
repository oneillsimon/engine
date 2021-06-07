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

void dump_stack(lua_State *L) {
    int top=lua_gettop(L);
    std::cout << "Dumping stack from top: " << top << std::endl;
    for (int i=top; i >= 1; i--) {
        printf("%d\t%s\t", i, luaL_typename(L,i));
        switch (lua_type(L, i)) {
            case LUA_TNUMBER:
                printf("%g\n",lua_tonumber(L,i));
                break;
            case LUA_TSTRING:
                printf("%s\n",lua_tostring(L,i));
                break;
            case LUA_TBOOLEAN:
                printf("%s\n", (lua_toboolean(L, i) ? "true" : "false"));
                break;
            case LUA_TNIL:
                printf("%s\n", "nil");
                break;
            default:
                printf("%p\n", lua_topointer(L,i));
                break;
        }
    }
};
