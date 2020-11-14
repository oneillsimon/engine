//
// Created by simon on 14/11/2020.
//

#include <iostream>
#include "application.h"

Application::Application() = default;

void Application::initialise() {
    std::cout << "App init" << std::endl;
}

void Application::update(const double& delta) {
    std::cout << "App update" << std::endl;
}

void Application::render(const double& delta) {
    std::cout << "App render" << std::endl;
}

void Application::stop() {
    std::cout << "App stop" << std::endl;
}
