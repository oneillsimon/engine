//
// Created by simon on 13/12/2020.
//

#ifndef ENGINE_POINT_LIGHT_H
#define ENGINE_POINT_LIGHT_H

#include "attenuation.h"
#include "light.h"

class PointLight : public Light {
private:
    glm::vec3 position;
    Attenuation attenuation;

public:
    PointLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const Attenuation& attenuation);
    PointLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float constant, float linear, float quadratic);

    glm::vec3 get_position() const;
    Attenuation get_attenuation() const;
};


#endif //ENGINE_POINT_LIGHT_H
