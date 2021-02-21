//
// Created by simon on 20/02/2021.
//

#ifndef ENGINE_TORUS_H
#define ENGINE_TORUS_H

#include <cmath>

#include <glm/gtc/constants.hpp>

#include "rendering/mesh/triangle_mesh.h"

class Torus : public TriangleMesh {
public:
    Torus(float outer_radius, float inner_radius, unsigned int number_of_sides, unsigned int number_of_rings);
};


#endif //ENGINE_TORUS_H
