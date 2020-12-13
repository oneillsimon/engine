//
// Created by simon on 13/12/2020.
//

#include "directional_light.h"

DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular) :
Light(ambient, diffuse, specular), direction(direction) {

}

glm::vec3 DirectionalLight::get_direction() const {
    return this->direction;
}
