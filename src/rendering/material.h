//
// Created by simon on 13/12/2020.
//

#ifndef ENGINE_MATERIAL_H
#define ENGINE_MATERIAL_H

class Material {
private:
    float diffuse;
    float specular;
    float shininess;

public:
    Material(float diffuse, float specular, float shininess);

    float get_diffuse() const;
    float get_specular() const;
    float get_shininess() const;
};


#endif //ENGINE_MATERIAL_H
