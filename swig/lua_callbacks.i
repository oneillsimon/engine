// Shared typemap converting a Lua table with initialise/update/render
// methods into C++ callbacks that invoke back into the table. The table and
// its methods are pinned in the Lua registry with luaL_ref; the references
// are held by the callbacks via shared_ptr<RegistryRefs> and released with
// luaL_unref when the last callback copy is destroyed.

%{
#include <functional>
#include <memory>
#include <lua.hpp>
#include "utils.h"
%}

%inline %{
    // RegistryRefs pins the Lua table and its methods in the Lua registry.
    // The references are released with luaL_unref when the last shared
    // owner (i.e. the last callback copy) goes away.
    struct RegistryRefs {
        lua_State* L = nullptr;
        int refs[4] = {LUA_NOREF, LUA_NOREF, LUA_NOREF, LUA_NOREF};
        ~RegistryRefs() {
            if (L != nullptr) {
                for (int ref : refs) {
                    if (ref != LUA_NOREF && ref != LUA_REFNIL) {
                        luaL_unref(L, LUA_REGISTRYINDEX, ref);
                    }
                }
            }
        }
    };
    class LuaCallbacks {
        public:
            using InitialiseCallback = std::function<void(InputProcessor&)>;
            using UpdateCallback = std::function<void(const double&, InputProcessor&)>;
            using RenderCallback = std::function<void(const double&)>;
            using StopCallback = std::function<void()>;
            LuaCallbacks() = default;
            std::shared_ptr<RegistryRefs> refs;
            InitialiseCallback initialise_callback;
            UpdateCallback update_callback;
            RenderCallback render_callback;
            LuaCallbacks(
                const LuaCallbacks::InitialiseCallback& initialise_callback,
                const LuaCallbacks::UpdateCallback& update_callback,
                const LuaCallbacks::RenderCallback& render_callback,
                std::shared_ptr<RegistryRefs> refs
            ) : refs(std::move(refs)),
                initialise_callback(initialise_callback),
                update_callback(update_callback),
                render_callback(render_callback) {}
    };
%}

%typecheck(SWIG_TYPECHECK_POINTER) LuaCallbacks& {
    $1 = lua_istable(L, $input);
}

%typemap(in) LuaCallbacks& (LuaCallbacks callbacks) {
    auto refs = std::make_shared<RegistryRefs>();
    refs->L = L;
    lua_pushvalue(L, $input);
    lua_getfield(L, $input, "initialise");
    refs->refs[0] = luaL_ref(L, LUA_REGISTRYINDEX);
    lua_getfield(L, $input, "update");
    refs->refs[1] = luaL_ref(L, LUA_REGISTRYINDEX);
    lua_getfield(L, $input, "render");
    refs->refs[2] = luaL_ref(L, LUA_REGISTRYINDEX);
    refs->refs[3] = luaL_ref(L, LUA_REGISTRYINDEX);
    LuaCallbacks::InitialiseCallback initialise_callback = [](InputProcessor& input) {};
    LuaCallbacks::UpdateCallback update_callback = [](const double& delta, InputProcessor& input) {};
    LuaCallbacks::RenderCallback render_callback = [](const double& delta) {};
    if (refs->refs[0] != LUA_NOREF && refs->refs[0] != LUA_REFNIL) {
        initialise_callback = [L, refs](InputProcessor& input) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, refs->refs[0]);
            lua_rawgeti(L, LUA_REGISTRYINDEX, refs->refs[3]);
            SWIG_NewPointerObj(L, &input, SWIG_TypeQuery((type(input) + "*").c_str()), 0);
            lua_call(L, 2, 0);
        };
    }
    if (refs->refs[1] != LUA_NOREF && refs->refs[1] != LUA_REFNIL) {
        update_callback = [L, refs](const double& delta, InputProcessor& input) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, refs->refs[1]);
            lua_rawgeti(L, LUA_REGISTRYINDEX, refs->refs[3]);
            lua_pushnumber(L, delta);
            SWIG_NewPointerObj(L, &input, SWIG_TypeQuery((type(input) + "*").c_str()), 0);
            lua_call(L, 3, 0);
        };
    }
    if (refs->refs[2] != LUA_NOREF && refs->refs[2] != LUA_REFNIL) {
        render_callback = [L, refs](const double& delta) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, refs->refs[2]);
            lua_rawgeti(L, LUA_REGISTRYINDEX, refs->refs[3]);
            lua_pushnumber(L, delta);
            lua_call(L, 2, 0);
        };
    }
    callbacks = LuaCallbacks(initialise_callback, update_callback, render_callback, refs);
    $1 = &callbacks;
}
