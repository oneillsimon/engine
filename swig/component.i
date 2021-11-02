%module engine
%{
#include <component.h>
#include <scripting/lua.h>

#include "utils.h"
%};

%include "../src/component.h"

%inline %{
    class LuaComponent : public Component {
        public:
            using InitialiseCallback = std::function<void(InputProcessor&)>;
            using UpdateCallback = std::function<void(const double&, InputProcessor&)>;
            using RenderCallback = std::function<void(const double&)>;

            using MethodSignature = std::tuple<LuaComponent::InitialiseCallback, LuaComponent::UpdateCallback, LuaComponent::RenderCallback>;

            LuaComponent(LuaComponent::MethodSignature& c) {
                this->on_initialise(std::get<0>(c));
                this->on_update(std::get<1>(c));
                this->on_render(std::get<2>(c));
            }

            InitialiseCallback initialise_callback;
            UpdateCallback update_callback;
            RenderCallback render_callback;

            void on_initialise(const LuaComponent::InitialiseCallback &callback) {
                this->initialise_callback = callback;
            }

            void on_update(const LuaComponent::UpdateCallback &callback) {
                this->update_callback = callback;
            }

            void on_render(const LuaComponent::RenderCallback &callback) {
                this->render_callback = callback;
            }

            void initialise(InputProcessor &input) {
                Component::initialise(input);
                if (this->initialise_callback) {
                    this->initialise_callback(input);
                }
            }

            void update(double delta, InputProcessor &input) {
                Component::update(delta, input);
                if (this->update_callback) {
                    this->update_callback(delta, input);
                }
            }

            void render(double delta) {
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