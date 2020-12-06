//
// Created by simon on 14/11/2020.
//

#include "application.h"

Application::Application() = default;

void Application::initialise() {
    this->root = new Entity();
}

void Application::update(const double& delta) {
}

void Application::render(const double& delta) {
}

void Application::stop() {
}

void Application::input(const double& delta) {
}
