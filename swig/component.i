%module engine
%{
#include <component.h>
#include <scripting/lua.h>

#include "utils.h"
%}

%include "lua_callbacks.i"
%include "../src/component.h"

%inline %{
    class LuaComponent : public Component {
        public:
            LuaComponent(LuaCallbacks& c) {
                this->on_initialise(c.initialise_callback);
                this->on_update(c.update_callback);
                this->on_render(c.render_callback);
            }

            LuaCallbacks::InitialiseCallback initialise_callback;
            LuaCallbacks::UpdateCallback update_callback;
            LuaCallbacks::RenderCallback render_callback;

            void on_initialise(const LuaCallbacks::InitialiseCallback &callback) {
                this->initialise_callback = callback;
            }

            void on_update(const LuaCallbacks::UpdateCallback &callback) {
                this->update_callback = callback;
            }

            void on_render(const LuaCallbacks::RenderCallback &callback) {
                this->render_callback = callback;
            }

            void initialise(InputProcessor &input) override {
                Component::initialise(input);
                if (this->initialise_callback) {
                    this->initialise_callback(input);
                }
            }

            void update(double delta, InputProcessor &input) override {
                Component::update(delta, input);
                if (this->update_callback) {
                    this->update_callback(delta, input);
                }
            }

            void render(double delta) override {
                Component::render(delta);
                if (this->render_callback) {
                    this->render_callback(delta);
                }
            }
    };
%}

%luacode {
    Component = {}

    function Component:new(o)
        o = o or {}
        setmetatable(o, self)
        self.__index = self
        return o
    end

    function Component:initialise(input)
    end

    function Component:update(delta, input)
    end

    function Component:render(delta)
    end
};
