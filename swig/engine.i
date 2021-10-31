%module engine
%{
#include <engine.h>
//#include <lua_application.h>
%};

%include "lua_application.i"

%typemap(typecheck) std::tuple<LuaApplication::InitialiseCallback, LuaApplication::UpdateCallback, LuaApplication::RenderCallback>& {
    $1 = 1;
}

%typemap(in) std::tuple<LuaApplication::InitialiseCallback, LuaApplication::UpdateCallback, LuaApplication::RenderCallback>& {
    LuaApplication::InitialiseCallback initialise_callback = [](InputProcessor& input) {};
    LuaApplication::UpdateCallback update_callback = [](const double& delta, InputProcessor& input) {};
    LuaApplication::RenderCallback render_callback = [](const double& delta) {};

    // Push table to top of stack to work with.
    lua_pushvalue(L, $input);

    lua_getfield(L, $input, "initialise");
    int initialise_reference = luaL_ref(L, LUA_REGISTRYINDEX);
    lua_getfield(L, $input, "update");
    int update_reference = luaL_ref(L, LUA_REGISTRYINDEX);
    lua_getfield(L, $input, "render");
    int render_reference = luaL_ref(L, LUA_REGISTRYINDEX);

    // Make sure we capture references to everything in the table we want before we get the reference to the table
    // itself because luaL_ref pops the value fromm the stack.
    int table_reference = luaL_ref(L, LUA_REGISTRYINDEX);

    if (initialise_reference != -1) {
        initialise_callback = [L, initialise_reference, table_reference](InputProcessor& input) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, initialise_reference);
            lua_rawgeti(L, LUA_REGISTRYINDEX, table_reference);
            SWIG_NewPointerObj(L, &input, SWIG_TypeQuery((type(input) + "*").c_str()), 0);
            lua_call(L, 2, 0);
        };
    }

    if (update_reference != -1) {
        update_callback = [L, update_reference, table_reference](const double& delta, InputProcessor& input) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, update_reference);
            lua_rawgeti(L, LUA_REGISTRYINDEX, table_reference);
            lua_pushnumber(L, delta);
            SWIG_NewPointerObj(L, &input, SWIG_TypeQuery((type(input) + "*").c_str()), 0);
            lua_call(L, 3, 0);
        };
    }

    if (render_reference != 1) {
        render_callback = [L, render_reference, table_reference](const double& delta) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, render_reference);
            lua_rawgeti(L, LUA_REGISTRYINDEX, table_reference);
            lua_pushnumber(L, delta);
            lua_call(L, 2, 0);
        };
    }

    auto t = std::make_tuple(initialise_callback, update_callback, render_callback);
    $1 = &t;
}

%include "../src/engine.h"

%inline %{
    class LuaEngine : public Engine {
        public:
            LuaEngine(LuaApplication application, Window* window, double frame_ate) :
                Engine(new LuaApplication(application), window, frame_ate) {
            }
    };
%};

%luacode {
    Engine = {};

    function Engine:new(application, window, frame_rate)
        print("here")
        a = engine.LuaApplication(application.root, application)
                print("here 2")
        application.root = a.root
        return engine.LuaEngine(a, window, frame_rate)
    end
};
