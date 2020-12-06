//
// Created by simon on 06/12/2020.
//

#include "glfw_input_processor.h"

GlfwInputProcessor::GlfwInputProcessor(void *window) : InputProcessor(window) {

}

bool GlfwInputProcessor::get_key(int key, int state) const {
    return glfwGetKey(static_cast<GLFWwindow*>(this->window), key) == state;
}
