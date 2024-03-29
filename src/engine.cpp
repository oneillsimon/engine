//
// Created by simon on 14/11/2020.
//

#include <cassert>
#include <iostream>
#include "engine.h"

Engine::Engine(Application* application, Window* window, double frame_rate) :
    application(application),
    running(false),
    window(window),
    frame_rate(1.0 / frame_rate) {
    assert(("Frame rate must be greater than zero.", frame_rate > 0));
}

Engine::~Engine() {
    delete application;
    delete window;
}

void Engine::run() {
    this->running = true;
    this->application->initialise(*this->window->get_input_processor());

    auto first_tick = std::chrono::steady_clock::now();
    double unprocessed_time = 0;

    while (this->running) {
        bool should_render = false;
        auto next_tick = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_time = next_tick - first_tick;

        first_tick = next_tick;
        unprocessed_time += elapsed_time.count();

        while (unprocessed_time > frame_rate) {
            should_render = true;

            if (this->window->is_close_requested() || this->application->is_close_requested()) {
                std::cout << "Close requested from " << (this->window->is_close_requested() ? "the window" : "not the window") << std::endl;
                std::cout << "Close requested from " << (this->application->is_close_requested() ? "the app" : "not the app") << std::endl;
                this->stop();
            }

            this->application->update(frame_rate, *this->window->get_input_processor());

            unprocessed_time -= frame_rate;
        }

        if (should_render) {
            this->window->update();
            this->window->swap_buffers();
            this->application->render(frame_rate);
        }
    }
}

bool Engine::is_running() const {
    return this->running;
}

void Engine::start() {
    if (!this->is_running()) {
        this->run();
    }
}

void Engine::stop() {
    this->running = false;
    this->application->stop();
}
