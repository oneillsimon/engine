//
// Created by simon on 14/11/2020.
//

#include "glfw_window.h"

#include <utility>

GlfwWindow::GlfwWindow(std::string title, const unsigned int& width, const unsigned int& height) :
        Window(std::move(title), width, height) {
    if (!glfwInit()) {
        fprintf(stderr, "Error in window initialisation");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(static_cast<GLFWwindow*>(this->window));
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

GlfwWindow::~GlfwWindow() {
    glfwTerminate();
}

void GlfwWindow::update() {
    this->close_requested = glfwWindowShouldClose(static_cast<GLFWwindow*>(this->window));
    glfwPollEvents();
}

void GlfwWindow::swap_buffers() {
    glfwSwapBuffers(static_cast<GLFWwindow*>(this->window));
}
