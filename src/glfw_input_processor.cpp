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

void GlfwInputProcessor::set_cursor_position_callback(void (*cursor_position_callback)(void* window, double x, double y)) const {
    // This is weird and I don't like it, is there a better way to do this?
    auto cb = (void(*)(GLFWwindow* window, double x, double y))cursor_position_callback;
    glfwSetCursorPosCallback(static_cast<GLFWwindow*>(this->window), cb);
}

void GlfwInputProcessor::set_scroll_callback(void (*scroll_callback)(void *, double, double)) const {
    // This is also weird and I still don't like it.
    auto cb = (void(*)(GLFWwindow* window, double x, double y))scroll_callback;
    glfwSetScrollCallback(static_cast<GLFWwindow*>(this->window), cb);
}

