//
// Created by simon on 13/12/2020.
//

#include "point_light.h"

PointLight::PointLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse,
                       const glm::vec3& specular, const Attenuation& attenuation) :
                       Light(ambient, diffuse, specular), position(position), attenuation(attenuation) {

}

PointLight::PointLight(const glm::vec3 &position, const glm::vec3 &ambient, const glm::vec3 &diffuse,
                       const glm::vec3 &specular, float constant, float linear, float quadratic) :
                       PointLight(position, ambient, diffuse, specular, Attenuation(constant, linear, quadratic)) {

}

glm::vec3 PointLight::get_position() const {
    return this->position;
}

Attenuation PointLight::get_attenuation() const {
    return this->attenuation;
}
