%module engine
%include <lua_fnptr.i>
%{
#include <functional>
#include <lua.hpp>
#include <lua_application.h>
#include <scripting/lua.h>

#include "utils.h"
%}

%typemap(in) LuaApplication::InitialiseCallback& (LuaApplication::InitialiseCallback callback) {
    int reference = luaL_ref(L, LUA_REGISTRYINDEX);

    callback = [L, reference](InputProcessor& input) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, reference);
        SWIG_NewPointerObj(L, &input, SWIG_TypeQuery((type(input) + "*").c_str()), 0);

        lua_call(L, 1, 0);
    };

    $1 = &callback;
}

%typemap(in) LuaApplication::UpdateCallback& (LuaApplication::UpdateCallback callback) {
    int reference = luaL_ref(L, LUA_REGISTRYINDEX);

    callback = [L, reference](const double& delta, InputProcessor& input) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, reference);
        lua_pushnumber(L, delta);
        SWIG_NewPointerObj(L, &input, SWIG_TypeQuery((type(input) + "*").c_str()), 0);

        lua_call(L, 2, 0);
    };

    $1 = &callback;
}

%typemap(in) LuaApplication::RenderCallback& (LuaApplication::RenderCallback callback) {
    int reference = luaL_ref(L, LUA_REGISTRYINDEX);

    callback = [L, reference](const double& delta) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, reference);
        lua_pushnumber(L, delta);

        lua_call(L, 1, 0);
    };

    $1 = &callback;
}

%typemap(in) LuaApplication::StopCallback& (LuaApplication::StopCallback callback) {
    int reference = luaL_ref(L, LUA_REGISTRYINDEX);

    callback = [L, reference]() {
        lua_rawgeti(L, LUA_REGISTRYINDEX, reference);

        lua_call(L, 0, 0);
    };

    $1 = &callback;
}

%include "../src/lua_application.h"

%luacode {
    Application = { root=engine.Entity() }

    function Application:new(o)
        o = o or {}
        setmetatable(o, self)
        self.__index = self
        return o
    end

    function Application:sets(s)
    end

    function Application:initialise(input)
    end

    function Application:update(delta, input)
    end

    function Application:render(delta)
    end
};
