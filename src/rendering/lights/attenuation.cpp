//
// Created by simon on 13/12/2020.
//

#include "attenuation.h"

Attenuation::Attenuation(float k, float l, float q) : constant(k), linear(l), quadratic(q) {

}

float Attenuation::get_constant() const {
    return this->constant;
}

float Attenuation::get_linear() const {
    return this->linear;
}

float Attenuation::get_quadratic() const {
    return this->quadratic;
}