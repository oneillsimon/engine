//
// Created by simon on 17/04/2021.
//

#include <gtest/gtest.h>

#include <glfw_input_processor.h>
#include <components/camera_component.h>
#include <rendering/glfw_window.h>

TEST(camera_component_test, constructor) {
    auto position = glm::vec3(5.0f, 6.0f, -5.0f);
    auto up = glm::vec3(10.0f, 0.0f, 1.0f);
    auto yaw = 4.3f;
    auto pitch = 129.0f;
    auto camera = CameraComponent(position, up);

    ASSERT_EQ(position, camera.get_position());
    ASSERT_EQ(up, camera.get_up());
//    ASSERT_EQ(yaw, camera.get_yaw());
}

TEST(camera_component, update) {
    auto* window = new GlfwWindow("test", 800, 600);
    auto* camera = new CameraComponent();
    camera->initialise(*window->get_input_processor());
    window->get_input_processor()->release_input();

    auto initial_position = camera->get_position();
    camera->speed = 5;
    auto expected_position = glm::vec3(initial_position.x, initial_position.y, initial_position.z - camera->speed);
    dynamic_cast<GlfwInputProcessor*>(window->get_input_processor())->key_states[GLFW_KEY_W] = GLFW_PRESS;
    camera->update(1, *window->get_input_processor());
    dynamic_cast<GlfwInputProcessor*>(window->get_input_processor())->key_states[GLFW_KEY_W] = GLFW_RELEASE;

    ASSERT_NEAR(expected_position.x, camera->get_position().x, 0.000001);
    ASSERT_NEAR(expected_position.y, camera->get_position().y, 0.000001);
    ASSERT_NEAR(expected_position.z, camera->get_position().z, 0.000001);

    dynamic_cast<GlfwInputProcessor*>(window->get_input_processor())->key_states[GLFW_KEY_S] = GLFW_PRESS;
    dynamic_cast<GlfwInputProcessor*>(window->get_input_processor())->key_states[GLFW_KEY_A] = GLFW_PRESS;
    dynamic_cast<GlfwInputProcessor*>(window->get_input_processor())->key_states[GLFW_KEY_D] = GLFW_PRESS;

    camera->update(1, *window->get_input_processor());

    ASSERT_NEAR(initial_position.x, camera->get_position().x, 0.000001);
    ASSERT_EQ(initial_position.y, camera->get_position().y);
    ASSERT_EQ(initial_position.z, camera->get_position().z);
}


TEST(camera_component_test, scroll_callback) {
    auto* window = new GlfwWindow("test", 800, 600);
    auto* camera = new CameraComponent();
    camera->initialise(*window->get_input_processor());
    window->get_input_processor()->release_input();

    auto original_zoom = camera->zoom;
    scroll_callback(window->get_input_processor()->get_window(), 0, 0.5f);
    ASSERT_EQ(original_zoom - 0.5f, camera->zoom);

    scroll_callback(window->get_input_processor()->get_window(), 0, 100000000.0f);
    ASSERT_EQ(1.0f, camera->zoom);

    scroll_callback(window->get_input_processor()->get_window(), 0, -100000000.0f);
    ASSERT_EQ(45.0f, camera->zoom);
}

TEST(camera_component, cursor_position_callback) {
    auto* window = new GlfwWindow("test", 800, 600);
    auto* camera = new CameraComponent();
    camera->initialise(*window->get_input_processor());
    window->get_input_processor()->release_input();

    cursor_position_callback(window->get_input_processor()->get_window(), 10, 20);

    ASSERT_EQ(camera->get_cursor_coordinates(), glm::vec2(10, 20));

    cursor_position_callback(window->get_input_processor()->get_window(), 0, 0);

    auto expected_yaw = camera->get_yaw() + (camera->sensitivity * (-5));
    auto expected_pitch = camera->get_pitch() - camera->sensitivity * (10);

    cursor_position_callback(window->get_input_processor()->get_window(), -5, 10);

    ASSERT_EQ(expected_yaw, camera->get_yaw());
    ASSERT_EQ(expected_pitch, camera->get_pitch());
}

TEST(camera_component, get_front) {
    auto* window = new GlfwWindow("test", 800, 600);
    auto* camera = new CameraComponent();
    camera->initialise(*window->get_input_processor());
    window->get_input_processor()->release_input();

    auto straight_ahead = glm::vec3(0.0F, 0.0F, -1.0F);
    ASSERT_NEAR(camera->get_front().x, straight_ahead.x, 0.0000001);
    ASSERT_NEAR(camera->get_front().y, straight_ahead.y, 0.0000001);
    ASSERT_NEAR(camera->get_front().z, straight_ahead.z, 0.0000001);
}

TEST(camera_component, get_view_matrix) {
    auto* window = new GlfwWindow("test", 800, 600);
    auto* camera = new CameraComponent();
    camera->initialise(*window->get_input_processor());
    window->get_input_processor()->release_input();
    auto expected_view_matrix = glm::lookAt(camera->get_position(), camera->get_position() + camera->get_front(), camera->get_up());

    ASSERT_EQ(expected_view_matrix, camera->get_view_matrix());
}
