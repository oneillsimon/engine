//
// Created by simon on 06/12/2020.
//

#include "glfw_input_processor.h"

void key_callback(void* window, int key, int scancode, int action, int mods) {
    auto instance = static_cast<GlfwInputProcessor*>(glfwGetWindowUserPointer(static_cast<GLFWwindow*>(window)));
    instance->key_states[key] = action;
}

void scroll_callback(void* window, double x, double y) {
    auto instance = static_cast<GlfwInputProcessor*>(glfwGetWindowUserPointer(static_cast<GLFWwindow*>(window)));
    std::cout << "X: " << x << " Y: " << y << std::endl;
    instance->scroll_x = x;
    instance->scroll_y = y;
}

GlfwInputProcessor::GlfwInputProcessor(void *window) : InputProcessor(window), key_states() {
    glfwSetWindowUserPointer(static_cast<GLFWwindow*>(this->window), this);
    glfwSetKeyCallback(static_cast<GLFWwindow*>(this->window), reinterpret_cast<GLFWkeyfun>(key_callback));
    glfwSetScrollCallback(static_cast<GLFWwindow*>(this->window), reinterpret_cast<GLFWscrollfun>(scroll_callback));
}

void GlfwInputProcessor::capture_input() const {
    glfwSetInputMode(static_cast<GLFWwindow*>(this->window), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void GlfwInputProcessor::set_cursor_position_callback(void* instance, void (*cursor_position_callback)(void* window, double x, double y)) const {
    glfwSetWindowUserPointer(static_cast<GLFWwindow*>(this->window), instance);
    glfwSetCursorPosCallback(static_cast<GLFWwindow*>(this->window), reinterpret_cast<GLFWcursorposfun>(cursor_position_callback));
}

void GlfwInputProcessor::set_input_mode(int mode, int value) const {
    glfwSetInputMode(static_cast<GLFWwindow*>(this->window), mode, value);
}

void GlfwInputProcessor::set_scroll_callback(void* instance, void (*scroll_callback)(void* window, double x, double y)) const {
    glfwSetWindowUserPointer(static_cast<GLFWwindow*>(this->window), instance);
//    glfwSetScrollCallback(static_cast<GLFWwindow*>(this->window), reinterpret_cast<GLFWscrollfun>(scroll_callback));
}

bool GlfwInputProcessor::is_key_down(int key) {
    return this->key_states[key] == GLFW_PRESS || this->key_states[key] == GLFW_REPEAT;
}

bool GlfwInputProcessor::is_key_pressed(int key) {
    auto result = this->key_states[key] == GLFW_PRESS;
    this->key_states[key] = NO_STATE;
    return result;
}

bool GlfwInputProcessor::is_key_released(int key) {
    return this->key_states[key] == GLFW_RELEASE;
}

bool GlfwInputProcessor::is_key_repeating(int key) {
    return this->key_states[key] == GLFW_REPEAT;
}

bool GlfwInputProcessor::is_scrolling(const ScrollDirection& direction) const {
    if (this->scroll_x == 1) {
        std::cout << "Scrolling UP" << std::endl;
        return direction == ScrollDirection::UP || direction == ScrollDirection::ANY;
    }

    if (this->scroll_x == -1) {
        std::cout << "Scrolling DOWN" << std::endl;
        return direction == ScrollDirection::DOWN || direction == ScrollDirection::ANY;
    }

    if (this->scroll_y == 1) {
        std::cout << "Scrolling RIGHT" << std::endl;
        return direction == ScrollDirection::RIGHT || direction == ScrollDirection::ANY;
    }

    if (this->scroll_y == -1) {
        std::cout << "Scrolling UP" << std::endl;
        return direction == ScrollDirection::LEFT || direction == ScrollDirection::ANY;
    }
    std::cout << "Not scrolling" << std::endl;
    return false;
}