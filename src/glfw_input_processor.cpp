//// Created by simon on 06/12/2020.//
#include <algorithm>
#include "glfw_input_processor.h"

void key_callback(void *window, int key, int scancode, int action, int mods) {
    auto* instance = static_cast<GlfwInputProcessor*>(glfwGetWindowUserPointer(static_cast<GLFWwindow*>(window)));
    instance->key_states[key] = action;
}

void scroll_callback(void* window, double x, double y) {
    auto* instance = static_cast<GlfwInputProcessor*>(glfwGetWindowUserPointer(static_cast<GLFWwindow*>(window)));
    instance->scroll_x = x;
    instance->scroll_y = y;
    for (const auto& callback : instance->scroll_callbacks) {
        callback(x, y);
    }
}

void cursor_position_callback(void* window, double x, double y) {
    auto* instance = static_cast<GlfwInputProcessor*>(glfwGetWindowUserPointer(static_cast<GLFWwindow*>(window)));
    for (const auto& callback : instance->cursor_position_callbacks) {
        callback(x, y);
    }
}

GlfwInputProcessor::GlfwInputProcessor(void* window) : InputProcessor(window), key_states() {
    glfwSetWindowUserPointer(static_cast<GLFWwindow*>(this->window), this);
    glfwSetKeyCallback(static_cast<GLFWwindow*>(this->window), reinterpret_cast<GLFWkeyfun>(key_callback));
    glfwSetScrollCallback(static_cast<GLFWwindow*>(this->window), reinterpret_cast<GLFWscrollfun>(scroll_callback));
    glfwSetCursorPosCallback(static_cast<GLFWwindow*>(this->window), reinterpret_cast<GLFWcursorposfun>(cursor_position_callback));
}

void GlfwInputProcessor::capture_input() const {
    this->set_input_mode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void GlfwInputProcessor::release_input() const {
    this->set_input_mode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void GlfwInputProcessor::set_input_mode(int mode, int value) const {
    glfwSetInputMode(static_cast<GLFWwindow*>(this->window), mode, value);
}

bool GlfwInputProcessor::is_key_down(int key) {
    return this->key_states[key] == GLFW_PRESS || this->is_key_repeating(key);
}

bool GlfwInputProcessor::is_key_pressed(int key) {
    // The first poll of a press records it for the rest of the frame so that
    // every caller sees the edge exactly once per frame, and never across
    // frames.
    if (this->key_states[key] == GLFW_PRESS) {
        this->key_states[key] = GLFW_REPEAT;
        this->pressed_this_frame.push_back(key);
        return true;
    }
    return std::find(this->pressed_this_frame.begin(), this->pressed_this_frame.end(), key) != this->pressed_this_frame.end();
}

bool GlfwInputProcessor::is_key_released(int key) {
    return this->key_states[key] == GLFW_RELEASE;
}

bool GlfwInputProcessor::is_key_repeating(int key) {
    return this->key_states[key] == GLFW_REPEAT;
}

bool GlfwInputProcessor::is_scrolling(const ScrollDirection& direction) {
    // GLFW reports positive horizontal offsets for rightward scrolls and
    // positive vertical offsets for upward scrolls.
    if (this->scroll_x > 0) {
        this->scroll_x = 0;
        return direction == ScrollDirection::RIGHT || direction == ScrollDirection::ANY;
    }
    if (this->scroll_x < 0) {
        this->scroll_x = 0;
        return direction == ScrollDirection::LEFT || direction == ScrollDirection::ANY;
    }
    if (this->scroll_y > 0) {
        this->scroll_y = 0;
        return direction == ScrollDirection::UP || direction == ScrollDirection::ANY;
    }
    if (this->scroll_y < 0) {
        this->scroll_y = 0;
        return direction == ScrollDirection::DOWN || direction == ScrollDirection::ANY;
    }
    return false;
}

void GlfwInputProcessor::begin_frame() {
    this->pressed_this_frame.clear();
}

int GlfwInputProcessor::get_input_mode(int mode) const {
    return glfwGetInputMode(static_cast<GLFWwindow*>(this->window), mode);
}
