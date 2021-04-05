//
// Created by simon on 06/12/2020.
//

#ifndef ENGINE_INPUT_PROCESSOR_H
#define ENGINE_INPUT_PROCESSOR_H

#include <functional>
#include <iostream>

class CameraInput {
public:
    virtual void on_scroll(void* window, double x, double y) = 0;
};

enum ScrollDirection {
    UP, DOWN, LEFT, RIGHT, ANY
};

class InputProcessor {
protected:
    void* window;
public:
    explicit InputProcessor(void* window);
    ~InputProcessor();

    virtual void capture_input() const = 0;
    virtual void set_cursor_position_callback(void* instance, void (*cursor_position_callback)(void* window, double x, double y)) const = 0;
    virtual void set_input_mode(int mode, int value) const = 0;
    virtual void set_scroll_callback(void* instance, void (*scroll_callback)(void* window, double x, double y)) const = 0;
    virtual bool is_key_down(int key) = 0;
    virtual bool is_key_pressed(int key) = 0;
    virtual bool is_key_released(int key) = 0;
    virtual bool is_key_repeating(int key) = 0;
    [[nodiscard]] virtual bool is_scrolling(const ScrollDirection& direction) const = 0;

    [[nodiscard]] void* get_window() const;
};


#endif //ENGINE_INPUT_PROCESSOR_H
