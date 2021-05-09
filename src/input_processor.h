//
// Created by simon on 06/12/2020.
//

#ifndef ENGINE_INPUT_PROCESSOR_H
#define ENGINE_INPUT_PROCESSOR_H

#include <functional>
#include <iostream>

enum ScrollDirection {
    UP, DOWN, LEFT, RIGHT, ANY
};

class InputProcessor {
protected:
    void* window;
public:
    std::vector<std::function<void(double, double)>> cursor_position_callbacks;
    std::vector<std::function<void(double, double)>> scroll_callbacks;

    explicit InputProcessor(void* window);

    virtual void capture_input() const = 0;
    virtual void release_input() const = 0;
    virtual void set_input_mode(int mode, int value) const = 0;
    [[nodiscard]] virtual int get_input_mode(int mode) const = 0;

    virtual bool is_key_down(int key) = 0;
    virtual bool is_key_pressed(int key) = 0;
    virtual bool is_key_released(int key) = 0;
    virtual bool is_key_repeating(int key) = 0;
    [[nodiscard]] virtual bool is_scrolling(const ScrollDirection& direction) = 0;

    [[nodiscard]] void* get_window() const;

    template<typename Callback>
    void on_cursor_position(Callback callback) {
        this->cursor_position_callbacks.push_back(callback);
    }

    template<typename Callback, typename Object>
    void on_cursor_position(Callback callback, Object obj_ptr) {
        auto _cb = std::bind(callback, obj_ptr, std::placeholders::_1, std::placeholders::_2);
        this->on_cursor_position(_cb);
    }

    template<typename Callback>
    void on_scroll(Callback callback) {
        this->scroll_callbacks.push_back(callback);
    };

    template<typename Callback, typename Object>
    void on_scroll(Callback callback, Object obj_ptr) {
        auto _cb = std::bind(callback, obj_ptr, std::placeholders::_1, std::placeholders::_2);
        this->on_scroll(_cb);
    };
};


#endif //ENGINE_INPUT_PROCESSOR_H
