//
// Created by simon on 21/02/2021.
//

#include "teapot.h"

void
Teapot::generate_patches(std::vector<GLfloat> &points, std::vector<GLfloat> &normals, std::vector<GLfloat> &tex_coords,
                         std::vector<GLuint> &elements, int grid) {
    std::vector<GLfloat> b(4 * (grid + 1)); // Pre-computed Bernstein basis functions.
    std::vector<GLfloat> db(4 * (grid + 1)); // Pre-computed derivatives of basis functions.

    int index = 0;
    int element_index = 0;
    int tex_coord_index = 0;

    // Pre-compute the basis function (Bernstein polynomials) and their derivatives.
    compute_basis_functions(b, db, grid);

    // Build each patch.
    // The rim.
    build_patch_reflect(
            0, b, db, points, normals, tex_coords, elements, index, element_index,
            tex_coord_index, grid, true, true
    );

    // The body.
    build_patch_reflect(
            1, b, db, points, normals, tex_coords, elements, index, element_index,
            tex_coord_index, grid, true, true
    );
    build_patch_reflect(
            2, b, db, points, normals, tex_coords, elements, index, element_index,
            tex_coord_index, grid, true, true
    );

    // The lid.
    build_patch_reflect(
            3, b, db, points, normals, tex_coords, elements, index, element_index,
            tex_coord_index, grid, true, true
    );
    build_patch_reflect(
            4, b, db, points, normals, tex_coords, elements, index, element_index,
            tex_coord_index, grid, true, true
    );

    // The bottom.
    build_patch_reflect(
            5, b, db, points, normals, tex_coords, elements, index, element_index,
            tex_coord_index, grid, true, true
    );

    // The handle.
    build_patch_reflect(
            6, b, db, points, normals, tex_coords, elements, index, element_index,
            tex_coord_index, grid, false, true
    );
    build_patch_reflect(
            7, b, db, points, normals, tex_coords, elements, index, element_index,
            tex_coord_index, grid, false, true
    );

    // The spout.
    build_patch_reflect(
            8, b, db, points, normals, tex_coords, elements, index, element_index,
            tex_coord_index, grid, false, true
    );
    build_patch_reflect(
            9, b, db, points, normals, tex_coords, elements, index, element_index,
            tex_coord_index, grid, false, true
    );

}

void Teapot::build_patch_reflect(int patch_number, std::vector<GLfloat> &b, std::vector<GLfloat> &db,
                                 std::vector<GLfloat> &v, std::vector<GLfloat> &n, std::vector<GLfloat> &tc,
                                 std::vector<GLuint> &el, int &index, int &element_index, int &tex_coord_index,
                                 int grid, bool reflect_x, bool reflect_y) {
    glm::vec3 patch[4][4];
    glm::vec3 patch_reverse[4][4];

    get_patch(patch_number, patch, false);
    get_patch(patch_number, patch_reverse, true);

    // Patch without modification.
    build_patch(
            patch, b, db, v, n, tc, el, index, element_index, tex_coord_index, grid,
            glm::mat3(1.0F), true
            );

    // Patch reflected in x.
    if (reflect_x) {
        build_patch(
                patch_reverse, b, db, v, n, tc, el, index, element_index, tex_coord_index,
                grid, glm::mat3(
                        glm::vec3(-1.0F, 0.0F, 0.0F),
                        glm::vec3(0.0F, 1.0F, 0.0F),
                        glm::vec3(0.0F, 0.0F, 1.0F)
                        ), false
                );
    }

    // Patch reflected in y.
    if (reflect_y) {
        build_patch(
                patch_reverse, b, db, v, n, tc, el, index, element_index, tex_coord_index,
                grid, glm::mat3(
                        glm::vec3(1.0F, 0.0F, 0.0F),
                        glm::vec3(0.0F, -1.0F, 0.0F),
                        glm::vec3(0.0F, 0.0F, 1.0F)
                ), false
        );
    }

    // Patch reflected in x and y.
    if (reflect_x && reflect_y) {
        build_patch(
                patch_reverse, b, db, v, n, tc, el, index, element_index, tex_coord_index,
                grid, glm::mat3(
                        glm::vec3(-1.0F, 0.0F, 0.0F),
                        glm::vec3(0.0F, -1.0F, 0.0F),
                        glm::vec3(0.0F, 0.0F, 1.0F)
                ), true
        );
    }
}

void Teapot::build_patch(glm::vec3 (*patch)[4], std::vector<GLfloat> &b, std::vector<GLfloat> &db,
                                 std::vector<GLfloat> &v, std::vector<GLfloat> &n, std::vector<GLfloat> &tc,
                                 std::vector<GLuint> &el, int &index, int &element_index, int &tex_coord_index,
                                 int grid, glm::mat3 reflect, bool invert_normal) {
    int start_index = index / 3;
    float tc_factor = 1.0F / (float)grid;

    for (auto i = 0; i <= grid; i++) {
        for (auto j = 0; j <= grid; j++) {
            auto point = reflect * evaluate(i, j, b, patch);
            auto normal = reflect * evaluate_normal(i, j, b, db, patch);

            if (invert_normal) {
                normal = -normal;
            }

            v[index] = point.x;
            v[index + 1] = point.y;
            v[index + 2] = point.z;

            n[index] = normal.x;
            n[index + 1] = normal.y;
            n[index + 2] = normal.z;

            tc[tex_coord_index] = i * tc_factor;
            tc[tex_coord_index + 1] = j * tc_factor;

            index += 3;
            tex_coord_index += 2;
        }
    }

    for (auto i = 0; i < grid; i++) {
        int i_start = i * (grid + 1) + start_index;
        int next_i_start = (i + 1) * (grid + 1) + start_index;

        for (auto j = 0; j < grid; j++) {
            el[element_index] = i_start + j;
            el[element_index + 1] = next_i_start + j + 1;
            el[element_index + 2] = next_i_start + j;

            el[element_index + 3] = i_start + j;
            el[element_index + 4] = i_start + j + 1;
            el[element_index + 5] = next_i_start + j + 1;

            element_index += 6;
        }
    }
}

void Teapot::get_patch(int patch_number, glm::vec3 (*patch)[4], bool reverse_v) {
    for (auto u = 0; u < 4; u++) {
        for (auto v = 0; v < 4; v++) {
            if (reverse_v) {
                patch[u][v] = glm::vec3(
                        TeapotData::cpdata[TeapotData::patchdata[patch_number][u * 4 + (3 - v)]][0],
                        TeapotData::cpdata[TeapotData::patchdata[patch_number][u * 4 + (3 - v)]][1],
                        TeapotData::cpdata[TeapotData::patchdata[patch_number][u * 4 + (3 - v)]][2]
                        );
            } else {
                patch[u][v] = glm::vec3(
                        TeapotData::cpdata[TeapotData::patchdata[patch_number][u * 4 + v]][0],
                        TeapotData::cpdata[TeapotData::patchdata[patch_number][u * 4 + v]][1],
                        TeapotData::cpdata[TeapotData::patchdata[patch_number][u * 4 + v]][2]
                );
            }
        }
    }
}

void Teapot::compute_basis_functions(std::vector<GLfloat> &b, std::vector<GLfloat> &db, int grid) {
    float inc = 1.0F / (float)grid;

    for (auto i = 0; i <= grid; i++) {
        float t = i * inc;
        float t_sqr = t * t;
        float one_minus_t = 1.0F - t;
        float one_minus_t_sqr = one_minus_t * one_minus_t;

        b[i * 4 + 0] = one_minus_t * one_minus_t_sqr;
        b[i * 4 + 1] = 3.0F * one_minus_t_sqr * t;
        b[i * 4 + 2] = 3.0F * one_minus_t * t_sqr;
        b[i * 4 + 3] = t * t_sqr;

        db[i * 4 + 0] = -3.0F * one_minus_t_sqr;
        db[i * 4 + 1] = -6.0F * t * one_minus_t + 3.0F * one_minus_t_sqr;
        db[i * 4 + 2] = -3.0F * t_sqr + 6.0F * t * one_minus_t;
        db[i * 4 + 3] = 3.0F * t_sqr;
    }
}

glm::vec3 Teapot::evaluate(int grid_u, int grid_v, std::vector<GLfloat> &b, glm::vec3 (*patch)[4]) {
    glm::vec3 p(0.0F, 0.0F, 0.0F);
    for (auto i = 0; i< 4; i++) {
        for (auto j = 0; j < 4; j++) {
            p += patch[i][j] * b[grid_u * 4 + i] * b[grid_v * 4 + j];
        }
    }
    return p;
}

glm::vec3 Teapot::evaluate_normal(int grid_u, int grid_v, std::vector<GLfloat> &b, std::vector<GLfloat> &db,
                                  glm::vec3 (*patch)[4]) {
    glm::vec3 du(0.0F, 0.0F, 0.0F);
    glm::vec3 dv(0.0F, 0.0F, 0.0F);

    for (auto i = 0; i < 4; i++) {
        for (auto j = 0; j < 4; j++) {
            du += patch[i][j] * db[grid_u * 4 + i] * b[grid_v * 4 + j];
            dv += patch[i][j] * b[grid_u * 4 + i] * db[grid_v * 4 + j];
        }
    }

    auto normal = glm::cross(du, dv);
    if (glm::length(normal) != 0.0F) {
        normal = glm::normalize(normal);
    }

    return normal;
}

void Teapot::move_lid(int grid, std::vector<GLfloat> &p, const glm::mat4 &lid_transform) {
    int start = 3 * 12 * (grid + 1) * (grid + 1);
    int end = 3 * 20 * (grid + 1) * (grid + 1);

    for (auto i = start; i < end; i += 3) {
        auto vertex = glm::vec4(p[i], p[i + 1], p[i + 2], 1.0F);
        vertex = lid_transform * vertex;

        p[i] = vertex.x;
        p[i + 1] = vertex.y;
        p[i + 2] = vertex.z;
    }
}

Teapot::Teapot(int grid, const glm::mat4 &lid_transform) {
    int vertices = 32 * (grid + 1) * (grid + 1);
    int faces = grid * grid * 32;

    std::vector<GLfloat> points(vertices * 3);
    std::vector<GLfloat> normals(vertices * 3);
    std::vector<GLfloat> tex_coords(vertices * 2);
    std::vector<GLuint> elements(faces * 6);

    generate_patches(points, normals, tex_coords, elements, grid);
    move_lid(grid, points, lid_transform);

    init_buffers(&elements, &points, &normals, &tex_coords);
}
