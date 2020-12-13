//
// Created by simon on 13/12/2020.
//

#ifndef ENGINE_DIRECTIONAL_LIGHT_H
#define ENGINE_DIRECTIONAL_LIGHT_H

#include "light.h"

class DirectionalLight : public Light {
private:
    glm::vec3 direction;

public:
    DirectionalLight(const glm::vec3 &direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);

    glm::vec3 get_direction() const;
};


#endif //ENGINE_DIRECTIONAL_LIGHT_H
