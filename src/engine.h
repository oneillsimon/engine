//
// Created by simon on 14/11/2020.
//

#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include <chrono>
#include <ctime>

#include "application.h"
#include "rendering/window.h"

class Engine {
private:
    bool running;
    double frame_rate;

    Application* application;
    Window* window;

    void run();

protected:
public:
    Engine(Application* application, Window* window, const double& frame_rate);
    ~Engine();

    bool is_running() const;
    void start();
    void stop();
};

#endif //ENGINE_ENGINE_H
