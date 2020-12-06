//
// Created by simon on 14/11/2020.
//

#include <iostream>
#include <utility>

#include "glfw_input_processor.h"
#include "glfw_window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GlfwWindow::GlfwWindow(std::string title, const unsigned int& width, const unsigned int& height) :
        Window(std::move(title), width, height) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialise GLFW" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(static_cast<GLFWwindow*>(this->window));

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialise GLAD" << std::endl;
    }

    glViewport(0, 0, this->width, this->height);
    glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(this->window), framebuffer_size_callback);

    this->input_processor = new GlfwInputProcessor(this->window);
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
