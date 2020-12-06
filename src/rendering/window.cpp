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
