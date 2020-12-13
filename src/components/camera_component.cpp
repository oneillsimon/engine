//
// Created by simon on 08/12/2020.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera_component.h"

CameraComponent::CameraComponent(const glm::vec3 &position, const glm::vec3 &up, const float &yaw, const float &pitch) :
    position(position), up(up), yaw(yaw), pitch(pitch), front(glm::vec3(0.0f, 0.0f, -1.0f)), speed(2.5f), sensitivity(0.1f), zoom(45.0f) {
    this->world_up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->update_vectors();
}

void CameraComponent::update_vectors() {
    // Calculate the new new_front vector.
    auto new_front = glm::vec3(
            cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)),
            sin(glm::radians(this->pitch)),
            sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch))
    );

    this->front = glm::normalize(new_front);

    // Also re-calculate the right and up vector.
    this->right = glm::normalize(glm::cross(this->front, this->world_up));
    this->up = glm::normalize(glm::cross(this->right, this->front));
}

void CameraComponent::scroll_callback(void* window, double x, double y) {
    auto instance = static_cast<CameraComponent*>(glfwGetWindowUserPointer(static_cast<GLFWwindow*>(window)));
    instance->zoom -= (float)y;

    if (instance->zoom < 1.0f) {
        instance->zoom = 1.0f;
    }

    if (instance->zoom > 45.0f) {
        instance->zoom = 45.0f;
    }
}

void CameraComponent::cursor_position_callback(void* window, double x, double y) {
    auto instance = static_cast<CameraComponent*>(glfwGetWindowUserPointer(static_cast<GLFWwindow*>(window)));

    if (instance->init_cursor) {
        instance->cursor_coords = glm::vec2(x, y);
        instance->init_cursor = false;
    }

    auto x_offset = x - instance->cursor_coords.x;
    auto y_offset = y - instance->cursor_coords.y;
    instance->cursor_coords = glm::vec2(x, y);

    x_offset *= instance->sensitivity;
    y_offset *= instance->sensitivity;

    instance->yaw += x_offset;
    instance->pitch -= y_offset;

    if (instance->pitch > 89.0f) {
        instance->pitch =  89.0f;
    }

    if (instance->pitch < -89.0f) {
        instance->pitch = -89.0f;
    }

    instance->update_vectors();
}

void CameraComponent::initialise(const InputProcessor &input) {
    int width, height;
    glfwGetWindowSize(static_cast<GLFWwindow*>(input.get_window()), &width, &height);
    this->cursor_coords = glm::vec2(width / 2, height / 2);

    input.capture_input();
    input.set_scroll_callback(this, scroll_callback);
    input.set_cursor_position_callback(this, cursor_position_callback);
    this->update_vectors();
}


void CameraComponent::update(double delta, const InputProcessor &input) {
    Component::update(delta, input);

    float velocity = this->speed * (float)delta;
    if (input.get_key(GLFW_KEY_W, GLFW_PRESS)) {
        this->position += this->front * velocity;
    }

    if (input.get_key(GLFW_KEY_S, GLFW_PRESS)) {
        this->position -= this->front * velocity;
    }

    if (input.get_key(GLFW_KEY_A, GLFW_PRESS)) {
        this->position -= this->right * velocity;
    }

    if (input.get_key(GLFW_KEY_D, GLFW_PRESS)) {
        this->position += this->right * velocity;
    }
}

glm::vec3 CameraComponent::get_front() const {
    return this->front;
}

glm::vec3 CameraComponent::get_position() const {
    return this->position;
}

glm::mat4 CameraComponent::get_view_matrix() const {
    return glm::lookAt(this->position, this->position + this->front, this->up);
}

float CameraComponent::get_zoom() const {
    return this->zoom;
}
