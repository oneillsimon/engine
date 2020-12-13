//
// Created by simon on 13/12/2020.
//

#ifndef ENGINE_ATTENUATION_H
#define ENGINE_ATTENUATION_H


class Attenuation {
private:
    float constant;
    float linear;
    float quadratic;

public:
    Attenuation(float k, float l, float q);

    float get_constant() const;
    float get_linear() const;
    float get_quadratic() const;
};


#endif //ENGINE_ATTENUATION_H
