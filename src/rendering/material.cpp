//
// Created by simon on 13/12/2020.
//

#include "material.h"

Material::Material(float diffuse, float specular, float shininess) : diffuse(diffuse), specular(specular), shininess(shininess) {

}

float Material::get_diffuse() const {
    return this->diffuse;
}

float Material::get_specular() const {
    return this->specular;
}

float Material::get_shininess() const {
    return this->shininess;
}
