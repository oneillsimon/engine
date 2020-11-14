//
// Created by simon on 14/11/2020.
//

#include <iostream>
#include "engine.h"

Engine::Engine(Application* application, Window* window, const double& frame_rate) :
    application(application),
    is_running(false),
    window(window),
    frame_rate(1.0 / frame_rate) {
}

Engine::~Engine() {
    delete application;
    delete window;
}

void Engine::run() {
    this->is_running = true;
    this->application->initialise();

    auto first_tick = std::chrono::steady_clock::now();
    double unprocessed_time = 0;

    while (is_running) {
        bool should_render = false;
        auto next_tick = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_time = next_tick - first_tick;

        first_tick = next_tick;
        unprocessed_time += elapsed_time.count();

        while (unprocessed_time > frame_rate) {
            should_render = true;

            if (this->window->is_close_requested()) {
                this->stop();
            }

            this->application->update(frame_rate);
            this->window->update();

            unprocessed_time -= frame_rate;
        }

        if (should_render) {
            this->application->render(frame_rate);
            this->window->swap_buffers();
        }
    }
}

void Engine::start() {
    if (!this->is_running) {
        this->run();
    }
}

void Engine::stop() {
    this->is_running = false;
    this->application->stop();
}
