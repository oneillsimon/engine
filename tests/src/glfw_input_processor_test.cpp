//
// Created by simon on 15/04/2021.
//
#include <gtest/gtest.h>

#include <glfw_input_processor.h>
#include <rendering/glfw_window.h>

TEST(glfw_input_processor_test, capture_input) {
    auto window = new GlfwWindow("test", 800, 600);
    auto input = window->get_input_processor();

    ASSERT_EQ(input->get_input_mode(GLFW_CURSOR), GLFW_CURSOR_NORMAL);

    input->capture_input();

    ASSERT_EQ(input->get_input_mode(GLFW_CURSOR), GLFW_CURSOR_DISABLED);
}

TEST(glfw_input_processor_test, release_input) {
    auto window = new GlfwWindow("test", 800, 600);
    auto input = window->get_input_processor();
    input->capture_input();
    ASSERT_EQ(input->get_input_mode(GLFW_CURSOR), GLFW_CURSOR_DISABLED);

    input->release_input();
    ASSERT_EQ(input->get_input_mode(GLFW_CURSOR), GLFW_CURSOR_NORMAL);
}

TEST(glfw_input_processor_test, is_key_down) {
    auto window = new GlfwWindow("test", 800, 600);
    auto* input = dynamic_cast<GlfwInputProcessor*>(window->get_input_processor());

    ASSERT_FALSE(input->is_key_down(GLFW_KEY_SPACE));
    input->key_states[GLFW_KEY_SPACE] = GLFW_PRESS;
    ASSERT_TRUE(input->is_key_down(GLFW_KEY_SPACE));

    // Assert that the key is still pressed down.
    ASSERT_TRUE(input->is_key_down(GLFW_KEY_SPACE));
}

TEST(glfw_input_processor_test, is_key_pressed) {
    auto window = new GlfwWindow("test", 800, 600);
    auto* input = dynamic_cast<GlfwInputProcessor*>(window->get_input_processor());

    ASSERT_FALSE(input->is_key_pressed(GLFW_KEY_SPACE));
    input->key_states[GLFW_KEY_SPACE] = GLFW_PRESS;
    ASSERT_TRUE(input->is_key_pressed(GLFW_KEY_SPACE));

    // Assert that the key is no longer pressed.
    ASSERT_FALSE(input->is_key_pressed(GLFW_KEY_SPACE));
}

TEST(glfw_input_processor_test, is_key_repeating) {
    auto window = new GlfwWindow("test", 800, 600);
    auto* input = dynamic_cast<GlfwInputProcessor*>(window->get_input_processor());

    ASSERT_FALSE(input->is_key_repeating(GLFW_KEY_SPACE));
    input->key_states[GLFW_KEY_SPACE] = GLFW_REPEAT;
    ASSERT_TRUE(input->is_key_repeating(GLFW_KEY_SPACE));
}

TEST(glfw_input_processor_test, is_key_released) {
    auto window = new GlfwWindow("test", 800, 600);
    auto* input = dynamic_cast<GlfwInputProcessor*>(window->get_input_processor());

    ASSERT_TRUE(input->is_key_released(GLFW_KEY_SPACE));
    input->key_states[GLFW_KEY_SPACE] = GLFW_PRESS;
    ASSERT_FALSE(input->is_key_released(GLFW_KEY_SPACE));
}

TEST(glfw_input_processor_test, is_scrolling) {
    auto window = new GlfwWindow("test", 800, 600);
    auto* input = dynamic_cast<GlfwInputProcessor*>(window->get_input_processor());

    ASSERT_FALSE(input->is_scrolling(ScrollDirection::ANY));

    input->scroll_x = 1;
    ASSERT_TRUE(input->is_scrolling(ScrollDirection::LEFT));
    ASSERT_EQ(input->scroll_x, 0);

    input->scroll_x = -1;
    ASSERT_TRUE(input->is_scrolling(ScrollDirection::RIGHT));
    ASSERT_EQ(input->scroll_x, 0);

    input->scroll_y = 1;
    ASSERT_TRUE(input->is_scrolling(ScrollDirection::UP));
    ASSERT_EQ(input->scroll_y, 0);

    input->scroll_y = -1;
    ASSERT_TRUE(input->is_scrolling(ScrollDirection::DOWN));
    ASSERT_EQ(input->scroll_y, 0);

    input->scroll_x = 1;
    ASSERT_TRUE(input->is_scrolling(ScrollDirection::ANY));
    ASSERT_EQ(input->scroll_x, 0);

    input->scroll_x = -1;
    ASSERT_TRUE(input->is_scrolling(ScrollDirection::ANY));
    ASSERT_EQ(input->scroll_x, 0);

    input->scroll_y = 1;
    ASSERT_TRUE(input->is_scrolling(ScrollDirection::ANY));
    ASSERT_EQ(input->scroll_y, 0);

    input->scroll_y = -1;
    ASSERT_TRUE(input->is_scrolling(ScrollDirection::ANY));
    ASSERT_EQ(input->scroll_y, 0);
}

TEST(glfw_input_processor_test, key_callback) {
    auto window = new GlfwWindow("test", 800, 600);
    auto* input = dynamic_cast<GlfwInputProcessor*>(window->get_input_processor());

    auto key = GLFW_KEY_A;

    ASSERT_TRUE(input->is_key_released(key));
    key_callback(input->get_window(), key, 0, GLFW_PRESS, 0);
    ASSERT_TRUE(input->is_key_pressed(key));
}

TEST(glfw_input_processor_test, scroll_callback) {
    auto window = new GlfwWindow("test", 800, 600);
    auto* input = dynamic_cast<GlfwInputProcessor*>(window->get_input_processor());

    scroll_callback(input->get_window(), 1, -1);
    ASSERT_EQ(input->scroll_x, 1);
    ASSERT_EQ(input->scroll_y, -1);

    scroll_callback(input->get_window(), -1, 1);
    ASSERT_EQ(input->scroll_x, -1);
    ASSERT_EQ(input->scroll_y, 1);

    scroll_callback(input->get_window(), 0, 0);
    ASSERT_EQ(input->scroll_x, 0);
    ASSERT_EQ(input->scroll_y, 0);

    double result = 0;
    double expected = -2;

    input->on_scroll([&result](double x, double y) { result = x + y; });
    scroll_callback(input->get_window(), -1, -1);
    ASSERT_EQ(result, expected);

    class Doubler {
    public:
        int value = 0;
        explicit Doubler(int value) : value(value) {}
        void on_scroll(int x, int y) { value = value * 2; }
    };

    auto d = Doubler(10);

    ASSERT_EQ(d.value, 10);
    input->on_scroll(&Doubler::on_scroll, &d);
    scroll_callback(input->get_window(), 0, 0);
    ASSERT_EQ(d.value, 20);

    scroll_callback(input->get_window(), 0, 0);
    ASSERT_EQ(d.value, 40);
}

TEST(glfw_input_processor_test, cursor_position_callback) {
    auto window = new GlfwWindow("test", 800, 600);
    auto* input = dynamic_cast<GlfwInputProcessor*>(window->get_input_processor());

    double result = 0;
    double expected = 3;

    input->on_cursor_position([&result](double x, double y) { result = x + y; });
    cursor_position_callback(input->get_window(), 1, 2);

    std::cout << "Result is " << result << std::endl;
    ASSERT_EQ(result, expected);

    class Halver {
    public:
        int value = 0;
        explicit Halver(int value) : value(value) {}
        void on_cursor(int x, int y) { value = value / 2; }
    };

    auto h = Halver(100);

    ASSERT_EQ(h.value, 100);
    input->on_cursor_position(&Halver::on_cursor, &h);
    cursor_position_callback(input->get_window(), 0, 0);
    ASSERT_EQ(h.value, 50);

    cursor_position_callback(input->get_window(), 0, 0);
    ASSERT_EQ(h.value, 25);
}