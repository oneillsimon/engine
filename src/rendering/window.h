//
// Created by simon on 13/11/2020.
//

#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

#include <string>

class Window {
private:
protected:
    unsigned int width;
    unsigned int height;
    std::string title;
    void* window;
    bool close_requested;
public:
    Window(std::string  title, const unsigned int&, const unsigned int& height);
    virtual ~Window();

    virtual void update() = 0;
    virtual void swap_buffers() = 0;

    bool is_close_requested() const;
};

#endif //ENGINE_WINDOW_H
