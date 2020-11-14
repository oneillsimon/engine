//
// Created by simon on 14/11/2020.
//

#ifndef ENGINE_GLFW_WINDOW_H
#define ENGINE_GLFW_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"

class GlfwWindow : public Window {
public:
    GlfwWindow(std::string  title, const unsigned int& width, const unsigned int& height);
    ~GlfwWindow() override;

    void update() override;
    void swap_buffers() override;
};

#endif //ENGINE_GLFW_WINDOW_H
