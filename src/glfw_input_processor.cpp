//
// Created by simon on 06/12/2020.
//

#include "glfw_input_processor.h"

GlfwInputProcessor::GlfwInputProcessor(void *window) : InputProcessor(window) {

}

void GlfwInputProcessor::capture_input() const {
    glfwSetInputMode(static_cast<GLFWwindow*>(this->window), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

bool GlfwInputProcessor::get_key(int key, int state) const {
    return glfwGetKey(static_cast<GLFWwindow*>(this->window), key) == state;
}

void GlfwInputProcessor::set_cursor_position_callback(void* instance, void (*cursor_position_callback)(void* window, double x, double y)) const {
    glfwSetWindowUserPointer(static_cast<GLFWwindow*>(this->window), instance);
    glfwSetCursorPosCallback(static_cast<GLFWwindow*>(this->window), reinterpret_cast<GLFWcursorposfun>(cursor_position_callback));
}

void GlfwInputProcessor::set_scroll_callback(void* instance, void (*scroll_callback)(void* window, double x, double y)) const {
    glfwSetWindowUserPointer(static_cast<GLFWwindow*>(this->window), instance);
    glfwSetScrollCallback(static_cast<GLFWwindow*>(this->window), reinterpret_cast<GLFWscrollfun>(scroll_callback));
}

