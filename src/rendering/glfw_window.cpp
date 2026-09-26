//
// Created by simon on 14/11/2020.
//

#include <iostream>
#include <utility>

#include "glfw_input_processor.h"
#include "glfw_window.h"

const int GLFW_VERSION_INFO_MAJOR_NUMBER = 4;
const int GLFW_VERSION_INFO_MINOR_NUMBER = 1;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GlfwWindow::GlfwWindow(std::string title, const unsigned int& width, const unsigned int& height) :
        Window(std::move(title), width, height) {

    if (glfwInit() == GLFW_FALSE) {
        throw std::runtime_error("Failed to initialize GLFW.");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_VERSION_INFO_MAJOR_NUMBER);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_VERSION_INFO_MINOR_NUMBER);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);
    if (!this->window) {
        throw std::runtime_error("Failed to create GLFW window.");
    }

    glfwMakeContextCurrent(static_cast<GLFWwindow*>(this->window));

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD.");
    }

    glViewport(0, 0, this->width, this->height);
    glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(this->window), framebuffer_size_callback);

    this->input_processor = new GlfwInputProcessor(this->window);
}

GlfwWindow::~GlfwWindow() {
    glfwTerminate();
}

void GlfwWindow::update() {
    this->close_requested = glfwWindowShouldClose(static_cast<GLFWwindow*>(this->window)) != 0;
    glfwPollEvents();
}

void GlfwWindow::swap_buffers() {
    glfwSwapBuffers(static_cast<GLFWwindow*>(this->window));
}
