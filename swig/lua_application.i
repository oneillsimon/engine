%module engine
%include "lua_fnptr.i"
%{
#include <functional>
#include <memory>
#include <tuple>
#include <lua.hpp>
#include <scripting/lua.h>
#include "utils.h"
%}
%include "lua_callbacks.i"
%typemap(in) LuaCallbacks::InitialiseCallback& (LuaCallbacks::InitialiseCallback callback) {
    auto refs = std::make_shared<RegistryRefs>();
    refs->L = L;
    refs->refs[0] = luaL_ref(L, LUA_REGISTRYINDEX);
    callback = [L, refs](InputProcessor& input) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, refs->refs[0]);
        SWIG_NewPointerObj(L, &input, SWIG_TypeQuery((type(input) + "*").c_str()), 0);
        lua_call(L, 1, 0);
    };
    $1 = &callback;
}
%typemap(in) LuaCallbacks::UpdateCallback& (LuaCallbacks::UpdateCallback callback) {
    auto refs = std::make_shared<RegistryRefs>();
    refs->L = L;
    refs->refs[0] = luaL_ref(L, LUA_REGISTRYINDEX);
    callback = [L, refs](const double& delta, InputProcessor& input) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, refs->refs[0]);
        lua_pushnumber(L, delta);
        SWIG_NewPointerObj(L, &input, SWIG_TypeQuery((type(input) + "*").c_str()), 0);
        lua_call(L, 2, 0);
    };
    $1 = &callback;
}
%typemap(in) LuaCallbacks::RenderCallback& (LuaCallbacks::RenderCallback callback) {
    auto refs = std::make_shared<RegistryRefs>();
    refs->L = L;
    refs->refs[0] = luaL_ref(L, LUA_REGISTRYINDEX);
    callback = [L, refs](const double& delta) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, refs->refs[0]);
        lua_pushnumber(L, delta);
        lua_call(L, 1, 0);
    };
    $1 = &callback;
}
%typemap(in) LuaCallbacks::StopCallback& (LuaCallbacks::StopCallback callback) {
    auto refs = std::make_shared<RegistryRefs>();
    refs->L = L;
    refs->refs[0] = luaL_ref(L, LUA_REGISTRYINDEX);
    callback = [L, refs]() {
        lua_rawgeti(L, LUA_REGISTRYINDEX, refs->refs[0]);
        lua_call(L, 0, 0);
    };
    $1 = &callback;
}
%inline %{
    class LuaApplication : public Application {
        public:
            LuaApplication(Entity entity, LuaCallbacks& callbacks) {
                this->root = new Entity(entity);
                this->on_initialise(callbacks.initialise_callback);
                this->on_update(callbacks.update_callback);
                this->on_render(callbacks.render_callback);
            }
            void on_initialise(const LuaCallbacks::InitialiseCallback& callback) {
                this->initialise_callback = callback;
            }
            void on_update(const LuaCallbacks::UpdateCallback& callback) {
                this->update_callback = callback;
            }
            void on_render(const LuaCallbacks::RenderCallback& callback) {
                this->render_callback = callback;
            }
            void on_stop(const LuaCallbacks::StopCallback& callback) {
                this->stop_callback = callback;
            }
            void initialise(InputProcessor &input) override {
                if (this->initialise_callback) {
                    this->initialise_callback(input);
                }
                Application::initialise(input);
            }
            void update(const double &delta, InputProcessor& input) override {
                if (this->update_callback) {
                    this->update_callback(delta, input);
                }
                Application::update(delta, input);
            }
            void render(const double &delta) override {
                if (this->render_callback) {
                    this->render_callback(delta);
                }
                Application::render(delta);
            }
            void stop() override {
                if (this->stop_callback) {
                    this->stop_callback();
                }
                Application::stop();
            }
        private:
            LuaCallbacks::InitialiseCallback initialise_callback;
            LuaCallbacks::UpdateCallback update_callback;
            LuaCallbacks::RenderCallback render_callback;
            LuaCallbacks::StopCallback stop_callback;
    };
%}
%luacode {
    Application = { root=engine.Entity() }
    function Application:new(o)
        o = o or {}
        setmetatable(o, self)
        self.__index = self
        return o
    end
    function Application:initialise(input)
    end
    function Application:update(delta, input)
    end
    function Application:render(delta)
    end
};
