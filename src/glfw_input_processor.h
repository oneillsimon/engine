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

void key_callback(void* window, int key, int scancode, int action, int mods);
void scroll_callback(void* window, double x, double y);
void cursor_position_callback(void* window, double x, double y);

class GlfwInputProcessor : public InputProcessor {
public:
    static const int KEYBOARD_SIZE = 512;
    static const int MOUSE_SIZE = 16;
    static const int NO_STATE = 0;

    std::array<int, KEYBOARD_SIZE> key_states;

    std::array<int, MOUSE_SIZE> mouse_button_states;
    std::array<bool, MOUSE_SIZE> active_mouse_buttons;

    double scroll_x = 0;
    double scroll_y = 0;

    explicit GlfwInputProcessor(void* window);

    void capture_input() const override;
    void release_input() const override;
    void set_input_mode(int mode, int value) const override;
    int get_input_mode(int mode) const override;

    bool is_key_down(int key) override;
    bool is_key_pressed(int key) override;
    bool is_key_released(int key) override;
    bool is_key_repeating(int key) override;
    bool is_scrolling(const ScrollDirection& direction) override;
};

#endif //ENGINE_GLFW_INPUT_PROCESSOR_H
