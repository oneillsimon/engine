//
// Created by simon on 06/12/2020.
//

#ifndef ENGINE_GLFW_INPUT_PROCESSOR_H
#define ENGINE_GLFW_INPUT_PROCESSOR_H

#include <functional>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "input_processor.h"

class GlfwInputProcessor : public InputProcessor {
public:
    static const int KEYBOARD_SIZE = 512;
    static const int MOUSE_SIZE = 16;
    static const int NO_STATE = -1;

    std::array<int, KEYBOARD_SIZE> key_states;

    std::array<int, MOUSE_SIZE> mouse_button_states;
    std::array<bool, MOUSE_SIZE> active_mouse_buttons;

    int scroll_x = 0;
    int scroll_y = 0;

    explicit GlfwInputProcessor(void* window);

    void capture_input() const override;
    void set_cursor_position_callback(void* instance, void (*cursor_position_callback)(void* window, double x, double y)) const override;
    void set_input_mode(int mode, int value) const override;
    void set_scroll_callback(void* instance, void (*scroll_callback)(void* window, double x, double y)) const override;
    bool is_key_down(int key) override;
    bool is_key_pressed(int key) override;
    bool is_key_released(int key) override;
    bool is_key_repeating(int key) override;
    bool is_scrolling(const ScrollDirection& direction) const override;
};


#endif //ENGINE_GLFW_INPUT_PROCESSOR_H
