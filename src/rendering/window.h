//
// Created by simon on 13/11/2020.
//

#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

#include <string>

#include "input_processor.h"

class Window {
private:
protected:
    void* window;
    unsigned int width;
    unsigned int height;
    std::string title;
    bool close_requested;
    InputProcessor* input_processor;

public:
    Window(std::string  title, const unsigned int& width, const unsigned int& height);
    virtual ~Window();

    virtual void update();
    virtual void swap_buffers();

    bool is_close_requested() const;
    InputProcessor* get_input_processor() const;
    unsigned int get_width() const;
    unsigned int get_height() const;
};

#endif //ENGINE_WINDOW_H
