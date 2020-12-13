//
// Created by simon on 13/12/2020.
//

#ifndef ENGINE_SPOT_LIGHT_H
#define ENGINE_SPOT_LIGHT_H

#include "attenuation.h"
#include "light.h"

class SpotLight : public Light {
private:
    glm::vec3 position;
    glm::vec3 direction;
    float cut_off;
    float outer_cut_off;

    Attenuation attenuation;

public:
    SpotLight(const glm::vec3& position, const glm::vec3& direction, float cut_off, float outer_cut_off, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const Attenuation& attenuation);

    Attenuation get_attenuation() const;
    glm::vec3 get_position() const;
    glm::vec3 get_direction() const;
    float get_cut_off() const;
    float get_outer_cut_off() const;
};


#endif //ENGINE_SPOT_LIGHT_H
