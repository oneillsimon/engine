//
// Created by simon on 08/12/2020.
//

#ifndef ENGINE_CAMERA_COMPONENT_H
#define ENGINE_CAMERA_COMPONENT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "component.h"

class CameraComponent : public Component {
private:
    // Camera attributes.
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right{};
    glm::vec3 world_up{};

    // Euler angles.
    float yaw;
    float pitch;

    // Cursor attributes.
    glm::vec2 cursor_coords{};

    void update_vectors();
    void scroll_callback(double x, double y);
    void cursor_position_callback(double x, double y);

public:
    constexpr static glm::vec3 DEFAULT_POSITION = glm::vec3(0.0F, 0.0F, 3.0F);
    constexpr static glm::vec3 DEFAULT_UP = glm::vec3(0.0F, 1.0F, 0.0F);
    constexpr static float DEFAULT_YAW = -90.0F;
    constexpr static float DEFAULT_PITCH = 0.0F;

    // Camera options.
    float speed;
    float sensitivity;
    float zoom;

    explicit CameraComponent(
            const glm::vec3& position = DEFAULT_POSITION,
            const glm::vec3& up = DEFAULT_UP,
            const float& yaw = DEFAULT_YAW,
            const float& pitch = DEFAULT_PITCH
    );

    void initialise(InputProcessor& input) override;
    void update(double delta, InputProcessor& input) override;

    glm::vec2 get_cursor_coordinates() const;
    glm::vec3 get_front() const;
    float get_pitch() const;
    glm::vec3 get_position() const;
    glm::vec3 get_up() const;
    glm::mat4 get_view_matrix() const;
    float get_yaw() const;
};


#endif //ENGINE_CAMERA_COMPONENT_H
