//
// Created by simon on 14/11/2020.
//

#include "application.h"

Application::Application() {
    this->root = new Entity();
}

void Application::initialise(const InputProcessor& input) {
    this->root->initialise(input);
}

void Application::update(const double& delta, const InputProcessor& input) {
    this->root->update(delta, input);
}

void Application::render(const double& delta) {
    this->root->render(delta);
}

void Application::stop() {
    this->close_requested = true;
}

bool Application::is_close_requested() const {
    return this->close_requested;
}
