//
// Created by simon on 19/04/2021.
//

#include <gtest/gtest.h>

#include <rendering/glfw_window.h>

TEST(glfw_window_test, window_size) {
    auto window = GlfwWindow("test", 800, 600);
    ASSERT_EQ(800, window.get_width());
    ASSERT_EQ(600, window.get_height());

    int glfw_width, glfw_height;
    glfwGetWindowSize(static_cast<GLFWwindow*>(window.get_input_processor()->get_window()), &glfw_width, &glfw_height);

    ASSERT_EQ(window.get_width(), glfw_width);
    ASSERT_EQ(window.get_height(), glfw_height);
}

TEST(glfw_window_test, should_close_flag) {
    auto window = GlfwWindow("test", 800, 600);

    // Assert the window should not be immediately closed.
    ASSERT_FALSE(window.is_close_requested());

    glfwSetWindowShouldClose(static_cast<GLFWwindow*>(window.get_input_processor()->get_window()), GLFW_TRUE);

    // Window hasn't been updated so should close flag hasn't changed.
    ASSERT_FALSE(window.is_close_requested());
    window.update();

    // Window has been updated so the should close flag should be updated.
    ASSERT_TRUE(window.is_close_requested());
}
