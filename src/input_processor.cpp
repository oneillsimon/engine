//
// Created by simon on 06/12/2020.
//

#include "input_processor.h"

InputProcessor::InputProcessor(void* window) : window(window) {

}

void* InputProcessor::get_window() const {
    return this->window;
}
