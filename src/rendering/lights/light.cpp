//
// Created by simon on 13/12/2020.
//

#include "light.h"

Light::Light(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular) : ambient(ambient), diffuse(diffuse), specular(specular) {

}

glm::vec3 Light::get_ambient() const {
    return this->ambient;
}

glm::vec3 Light::get_diffuse() const {
    return this->diffuse;
}

glm::vec3 Light::get_specular() const {
    return this->specular;
}
