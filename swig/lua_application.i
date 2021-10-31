%module engine
%include <lua_fnptr.i>
%{
#include <functional>
#include <lua.hpp>
//#include <lua_application.h>
#include <scripting/lua.h>

#include "utils.h"
%}

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

//%include "../src/lua_application.h"
%inline %{
    class LuaApplication : public Application {
        public:
            using InitialiseCallback = std::function<void(InputProcessor&)>;
            using UpdateCallback = std::function<void(const double&, InputProcessor&)>;
            using RenderCallback = std::function<void(const double&)>;
            using StopCallback = std::function<void()>;


            InitialiseCallback initialise_callback;
            UpdateCallback update_callback;
            RenderCallback render_callback;
            StopCallback stop_callback;

            LuaApplication(Entity entity, std::tuple<LuaApplication::InitialiseCallback, LuaApplication::UpdateCallback, LuaApplication::RenderCallback>& application) {
                this->root = new Entity(entity);
                this->on_initialise(std::get<0>(application));
                this->on_update(std::get<1>(application));
                this->on_render(std::get<2>(application));
            }

            void on_initialise(const LuaApplication::InitialiseCallback& callback) {
                this->initialise_callback = callback;
            }

            void on_update(const LuaApplication::UpdateCallback& callback) {
                this->update_callback = callback;
            }

            void on_render(const LuaApplication::RenderCallback& callback) {
                this->render_callback = callback;
            }

            void on_stop(const LuaApplication::StopCallback& callback) {
                this->stop_callback = callback;
            }

            void initialise(InputProcessor &input) {
                if (this->initialise_callback) {
                    this->initialise_callback(input);
                }
                Application::initialise(input);
            }

            void update(const double &delta, InputProcessor& input) {
                if (this->update_callback) {
                    this->update_callback(delta, input);
                }
                Application::update(delta, input);
            }

            void render(const double &delta) {
                if (this->render_callback) {
                    this->render_callback(delta);
                }
                Application::render(delta);
            }

            void stop() {
                if (this->stop_callback) {
                    this->stop_callback();
                }
                Application::stop();
            }
    };
%};

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
