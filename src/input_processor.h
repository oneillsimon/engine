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

class InputProcessor {
protected:
    void* window;
public:
    InputProcessor(void* window);

    virtual void capture_input() const = 0;
    virtual bool get_key(int key, int state) const = 0;
    virtual void set_cursor_position_callback(void* instance, void (*cursor_position_callback)(void* window, double x, double y)) const = 0;
    virtual void set_scroll_callback(void* instance, void (*scroll_callback)(void* window, double x, double y)) const = 0;

    void* get_window() const;
};


#endif //ENGINE_INPUT_PROCESSOR_H
