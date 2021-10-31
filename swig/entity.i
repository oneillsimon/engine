%module engine
%{
#include <entity.h>

#include "utils.h"
%}

%include "component.i"

%typemap(out) Component* {
    if (!$1) {
        lua_pushnil(L);
    } else {
        SWIG_NewPointerObj(L, $1, SWIG_TypeQuery((type(*$1) + "*").c_str()), 0);
    }
    SWIG_arg++;
};

%typemap(typecheck) std::tuple<LuaComponent::InitialiseCallback, LuaComponent::UpdateCallback, LuaComponent::RenderCallback>& {
    $1 = 1;
}

%typemap(in) std::tuple<LuaComponent::InitialiseCallback, LuaComponent::UpdateCallback, LuaComponent::RenderCallback>& {
    LuaComponent::InitialiseCallback initialise_callback = [](InputProcessor& input) {};
    LuaComponent::UpdateCallback update_callback = [](double delta, InputProcessor& input) {};
    LuaComponent::RenderCallback render_callback = [](double delta) {};

    // Push table to top of stack to work with.
    lua_pushvalue(L, $input);

    lua_getfield(L, $input, "initialise");
    int initialise_reference = luaL_ref(L, LUA_REGISTRYINDEX);
    lua_getfield(L, $input, "update");
    int update_reference = luaL_ref(L, LUA_REGISTRYINDEX);
    lua_getfield(L, $input, "render");
    int render_reference = luaL_ref(L, LUA_REGISTRYINDEX);

    // Make sure we capture references to everything in the table we want before we get the reference to the table
    // itself because luaL_ref pops the value from the stack.
    int table_reference = luaL_ref(L, LUA_REGISTRYINDEX);

    if(initialise_reference != -1) {
        initialise_callback = [L, initialise_reference, table_reference](InputProcessor& input) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, initialise_reference);
            lua_rawgeti(L, LUA_REGISTRYINDEX, table_reference);
            SWIG_NewPointerObj(L, &input, SWIG_TypeQuery((type(input) + "*").c_str()), 0);
            lua_call(L, 2, 0);
        };
    }

    if (update_reference != -1) {
        update_callback = [L, update_reference, table_reference](double delta, InputProcessor& input) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, update_reference);
            lua_rawgeti(L, LUA_REGISTRYINDEX, table_reference);
            lua_pushnumber(L, delta);
            SWIG_NewPointerObj(L, &input, SWIG_TypeQuery((type(input) + "*").c_str()), 0);
            lua_call(L, 3, 0);
        };
    }

    if (render_reference != -1) {
        render_callback = [L, render_reference, table_reference](double delta) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, render_reference);
            lua_rawgeti(L, LUA_REGISTRYINDEX, table_reference);
            lua_pushnumber(L, delta);
            lua_call(L, 2, 0);
        };
    }

    auto t = std::make_tuple(initialise_callback, update_callback, render_callback);
    $1 = &t;
}

%include "../src/entity.h"

%extend Entity {
    void add_component(const std::string& name, std::tuple<LuaComponent::InitialiseCallback, LuaComponent::UpdateCallback, LuaComponent::RenderCallback>& c) {
        $self->add_component(name, new LuaComponent(c));
    }

    Component* get_component(const std::string& name) {
        return $self->all_components()[name];
    }
};