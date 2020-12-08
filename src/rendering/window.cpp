//
// Created by simon on 13/11/2020.
//

#include "window.h"

#include <utility>

Window::Window(std::string  title, const unsigned int& width, const unsigned int& height) :
        window(nullptr),
        input_processor(nullptr),
        title(std::move(title)),
        width(width),
        height(height),
        close_requested(false) {

}

Window::~Window() = default;

bool Window::is_close_requested() const {
    return close_requested;
}

void Window::update() {

}

void Window::swap_buffers() {

}

InputProcessor *Window::get_input_processor() const {
    return this->input_processor;
}

unsigned int Window::get_width() const {
    return this->width;
}

unsigned int Window::get_height() const {
    return this->height;
}
