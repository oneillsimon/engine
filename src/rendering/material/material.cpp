//
// Created by simon on 21/02/2021.
//

#include "material.h"

Material::Material(const glm::vec3 &k_a, const glm::vec3 &k_d, const glm::vec3 &k_s, float shininess) :
k_a(k_a), k_d(k_d), k_s(k_s), shininess(shininess) {

}
