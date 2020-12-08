//
// Created by simon on 06/12/2020.
//

#ifndef ENGINE_INPUT_PROCESSOR_H
#define ENGINE_INPUT_PROCESSOR_H

#include <iostream>

class InputProcessor {
protected:
    void* window;
public:
    InputProcessor(void* window);

    virtual void capture_input() const = 0;
    virtual bool get_key(int key, int state) const = 0;
    virtual void set_cursor_position_callback(void (*cursor_position_callback)(void* window, double x, double y)) const = 0;
    virtual void set_scroll_callback(void (*scroll_callback)(void* window, double x, double y)) const = 0;
};


#endif //ENGINE_INPUT_PROCESSOR_H
