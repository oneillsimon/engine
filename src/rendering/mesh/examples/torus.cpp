//
// Created by simon on 20/02/2021.
//

#include <iostream>
#include "torus.h"

Torus::Torus(float outer_radius, float inner_radius, unsigned int number_of_sides, unsigned int number_of_rings) {
    auto faces = number_of_sides * number_of_rings;

    // One extra ring to duplicate first one.
    auto number_of_vertices = number_of_sides * (number_of_rings + 1);

    std::vector<GLfloat> points(3 * number_of_vertices);
    std::vector<GLfloat> normals(3 * number_of_vertices);
    std::vector<GLfloat> tex_coords(2 * number_of_vertices);
    std::vector<GLuint> elements(6 * faces);

    // Generate the vertex data.
    auto ring_factor = glm::two_pi<float>() / number_of_rings;
    auto side_factor = glm::two_pi<float>() / number_of_sides;

    auto index = 0;
    auto tex_index = 0;

    for (auto ring = 0; ring <= number_of_rings; ring++) {
        auto u = ring * ring_factor;
        auto cos_u = cos(u);
        auto sin_u = sin(u);

        for (auto side = 0; side < number_of_sides; side++) {
            auto v = side * side_factor;
            auto cos_v = cos(v);
            auto sin_v = sin(v);

            auto r = (outer_radius + inner_radius * cos_v);

            points[index] = r * cos_u;
            points[index + 1] = r * sin_u;
            points[index + 2] = inner_radius * sin_v;

            normals[index] = cos_v * cos_u * r;
            normals[index + 1] = cos_v * sin_u * r;
            normals[index + 2] = sin_v * r;

            tex_coords[tex_index] = u / glm::two_pi<float>();
            tex_coords[tex_index + 1] = v / glm::two_pi<float>();
            tex_index += 2;

            // Normalize.
            auto length = sqrt(
                    normals[index] * normals[index] +
                    normals[index + 1] * normals[index + 1] +
                    normals[index + 2] * normals[index + 2]
                    );

            normals[index] /= length;
            normals[index + 1] /= length;
            normals[index + 2] /= length;
            index += 3;
        }
    }

    index = 0;
    for (auto ring = 0; ring < number_of_rings; ring++) {
        auto ring_start = ring * number_of_sides;
        auto next_ring_start = (ring + 1) * number_of_sides;
        for (auto side = 0; side < number_of_sides; side++) {
            auto next_side = (side + 1) % number_of_sides;

            // The quad.
            elements[index] = ring_start + side;
            elements[index + 1] = next_ring_start + side;
            elements[index + 2] = next_ring_start + next_side;
            elements[index + 3] = ring_start + side;
            elements[index + 4] = next_ring_start + next_side;
            elements[index + 5] = ring_start + next_side;
            index += 6;
        }
    }

    init_buffers(&elements, &points, & normals, &tex_coords);
}
