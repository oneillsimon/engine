//
// Created by simon on 13/12/2020.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H

#include <glm/glm.hpp>

class Light {
protected:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    Light(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);

public:
    glm::vec3 get_ambient() const;
    glm::vec3 get_diffuse() const;
    glm::vec3 get_specular() const;
};


#endif //ENGINE_LIGHT_H
