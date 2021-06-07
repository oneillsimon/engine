//
// Created by simon on 03/06/2021.
//

#include "lua_component.h"

LuaComponent::LuaComponent(
        std::tuple<LuaComponent::InitialiseCallback, LuaComponent::UpdateCallback, LuaComponent::RenderCallback> &c) {
    this->on_initialise(std::get<0>(c));
    this->on_update(std::get<1>(c));
    this->on_render(std::get<2>(c));
}

void LuaComponent::on_initialise(const LuaComponent::InitialiseCallback &callback) {
    this->initialise_callback = callback;
}

void LuaComponent::on_update(const LuaComponent::UpdateCallback &callback) {
    this->update_callback = callback;
}

void LuaComponent::on_render(const LuaComponent::RenderCallback &callback) {
    this->render_callback = callback;
}

void LuaComponent::initialise(InputProcessor &input) {
    Component::initialise(input);
    if (this->initialise_callback) {
        this->initialise_callback(input);
    }
}

void LuaComponent::update(double delta, InputProcessor &input) {
    Component::update(delta, input);
    if (this->update_callback) {
        this->update_callback(delta, input);
    }
}

void LuaComponent::render(double delta) {
    Component::render(delta);
    if (this->render_callback) {
        this->render_callback(delta);
    }
}
