//
// Created by simon on 08/12/2020.
//

#ifndef ENGINE_CAMERA_COMPONENT_H
#define ENGINE_CAMERA_COMPONENT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "component.h"

enum CameraMovement {
    Forward,
    Backward,
    Left,
    Right
};

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

    // Camera options.
    float speed;
    float sensitivity;
    float zoom;

    // Cursor attributes.
    bool init_cursor = true;
    glm::vec2 cursor_coords{};

    void update_vectors();
    void scroll_callback(double x, double y);
    void cursor_position_callback(double x, double y);

public:
    explicit CameraComponent(
            const glm::vec3& position = glm::vec3(0.0f, 0.0f, 3.0f),
            const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
            const float& yaw = -90.0f,
            const float& pitch = 0.0f
    );

    void initialise(InputProcessor& input) override;
    void update(double delta, InputProcessor& input) override;

    glm::vec3 get_front() const;
    glm::vec3 get_position() const;
    glm::mat4 get_view_matrix() const;
    float get_zoom() const;
};


#endif //ENGINE_CAMERA_COMPONENT_H
