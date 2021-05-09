//
// Created by simon on 08/12/2020.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera_component.h"

const float DEFAULT_CAMERA_SPEED = 2.5F;
const float DEFAULT_CAMERA_SENSITIVITY = 0.1F;
const float DEFAULT_CAMERA_ZOOM = 45.0F;

CameraComponent::CameraComponent(const glm::vec3 &position, const glm::vec3 &up, const float &yaw, const float &pitch) :
    position(position), up(up), yaw(yaw), pitch(pitch), front(glm::vec3(0.0F, 0.0F, -1.0F)),
    speed(DEFAULT_CAMERA_SPEED), sensitivity(DEFAULT_CAMERA_SENSITIVITY), zoom(DEFAULT_CAMERA_ZOOM) {
    this->world_up = glm::vec3(0.0F, 1.0F, 0.0F);
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

void CameraComponent::scroll_callback(double x, double y) {
    this->zoom -= (float)y;

    if (this->zoom < 1.0F) {
        this->zoom = 1.0F;
    }

    if (this->zoom > DEFAULT_CAMERA_ZOOM) {
        this->zoom = DEFAULT_CAMERA_ZOOM;
    }
}

void CameraComponent::cursor_position_callback(double x, double y) {
    auto x_offset = x - this->cursor_coords.x;
    auto y_offset = y - this->cursor_coords.y;
    this->cursor_coords = glm::vec2(x, y);

    x_offset *= this->sensitivity;
    y_offset *= this->sensitivity;

    this->yaw += static_cast<float>(x_offset);
    this->pitch -= static_cast<float>(y_offset);

    this->update_vectors();
}

void CameraComponent::initialise(InputProcessor& input) {
    int width;
    int height;
    glfwGetWindowSize(static_cast<GLFWwindow*>(input.get_window()), &width, &height);
    this->cursor_coords = glm::vec2(width / 2, height / 2);

//    input.capture_input();
    input.on_cursor_position(&CameraComponent::cursor_position_callback, this);
    input.on_scroll(&CameraComponent::scroll_callback, this);
    this->update_vectors();
}


void CameraComponent::update(double delta, InputProcessor& input) {
    Component::update(delta, input);

    float velocity = this->speed * (float)delta;
    if (input.is_key_down(GLFW_KEY_W)) {
        this->position += this->front * velocity;
    }

    if (input.is_key_down(GLFW_KEY_S)) {
        this->position -= this->front * velocity;
    }

    if (input.is_key_down(GLFW_KEY_A)) {
        this->position -= this->right * velocity;
    }

    if (input.is_key_down(GLFW_KEY_D)) {
        this->position += this->right * velocity;
    }
}

glm::vec2 CameraComponent::get_cursor_coordinates() const {
    return this->cursor_coords;
}

float CameraComponent::get_pitch() const {
    return this->pitch;
}

glm::vec3 CameraComponent::get_front() const {
    return this->front;
}

glm::vec3 CameraComponent::get_position() const {
    return this->position;
}

glm::vec3 CameraComponent::get_up() const {
    return this->up;
}

glm::mat4 CameraComponent::get_view_matrix() const {
    return glm::lookAt(this->position, this->position + this->front, this->up);
}

float CameraComponent::get_yaw() const {
    return this->yaw;
}
