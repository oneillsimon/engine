//
// Created by simon on 10/05/2021.
//

#include "lua_application.h"

LuaApplication::LuaApplication(
        Entity entity, std::tuple<LuaApplication::InitialiseCallback, LuaApplication::UpdateCallback, LuaApplication::RenderCallback> &application) {
    this->root = new Entity(entity);
    this->on_initialise(std::get<0>(application));
    this->on_update(std::get<1>(application));
    this->on_render(std::get<2>(application));
}

void LuaApplication::on_initialise(const LuaApplication::InitialiseCallback& callback) {
    this->initialise_callback = callback;
}

void LuaApplication::on_update(const LuaApplication::UpdateCallback& callback) {
    this->update_callback = callback;
}

void LuaApplication::on_render(const LuaApplication::RenderCallback& callback) {
    this->render_callback = callback;
}

void LuaApplication::on_stop(const LuaApplication::StopCallback& callback) {
    this->stop_callback = callback;
}

void LuaApplication::initialise(InputProcessor &input) {
    if (this->initialise_callback) {
        this->initialise_callback(input);
    }
    Application::initialise(input);
}

void LuaApplication::update(const double &delta, InputProcessor& input) {
    if (this->update_callback) {
        this->update_callback(delta, input);
    }
    Application::update(delta, input);
}

void LuaApplication::render(const double &delta) {
    if (this->render_callback) {
        this->render_callback(delta);
    }
    Application::render(delta);
}

void LuaApplication::stop() {
    if (this->stop_callback) {
        this->stop_callback();
    }
    Application::stop();
}
