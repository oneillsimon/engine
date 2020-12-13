//
// Created by simon on 13/12/2020.
//

#include "spot_light.h"

SpotLight::SpotLight(const glm::vec3& position, const glm::vec3& direction, float cut_off, float outer_cut_off, const glm::vec3& ambient,
                     const glm::vec3& diffuse, const glm::vec3& specular, const Attenuation& attenuation) :
                     Light(ambient, diffuse, specular), position(position), direction(direction), cut_off(glm::cos(cut_off)),
                     outer_cut_off(glm::cos(outer_cut_off)), attenuation(attenuation) {

}

Attenuation SpotLight::get_attenuation() const {
    return this->attenuation;
}

glm::vec3 SpotLight::get_position() const {
    return this->position;
}

glm::vec3 SpotLight::get_direction() const {
    return this->direction;
}

float SpotLight::get_cut_off() const {
    return this->cut_off;
}

float SpotLight::get_outer_cut_off() const {
    return this->outer_cut_off;
}
