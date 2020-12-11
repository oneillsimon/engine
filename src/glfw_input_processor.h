//
// Created by simon on 06/12/2020.
//

#ifndef ENGINE_GLFW_INPUT_PROCESSOR_H
#define ENGINE_GLFW_INPUT_PROCESSOR_H

#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "input_processor.h"

class GlfwInputProcessor : public InputProcessor {
public:
    explicit GlfwInputProcessor(void* window);

    void capture_input() const override;
    bool get_key(int key, int state) const override;
    void set_cursor_position_callback(void* instance, void (*cursor_position_callback)(void* window, double x, double y)) const override;
    void set_scroll_callback(void* instance, void (*scroll_callback)(void* window, double x, double y)) const override;
};


#endif //ENGINE_GLFW_INPUT_PROCESSOR_H
