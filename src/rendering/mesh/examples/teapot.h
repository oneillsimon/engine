//
// Created by simon on 21/02/2021.
//

#ifndef ENGINE_TEAPOT_H
#define ENGINE_TEAPOT_H

#include <glm/glm.hpp>

#include "teapotdata.h"
#include "rendering/mesh/triangle_mesh.h"

class Teapot : public TriangleMesh {
private:
    void generate_patches(
            std::vector<GLfloat>& points,
            std::vector<GLfloat>& normals,
            std::vector<GLfloat>& tex_coords,
            std::vector<GLuint>& elements,
            int grid
            );
    void build_patch_reflect(
            int patch_number,
            std::vector<GLfloat>& b, std::vector<GLfloat>& db,
            std::vector<GLfloat>& v, std::vector<GLfloat>& n,
            std::vector<GLfloat>& tc, std::vector<GLuint>& el,
            int& index, int& element_index, int& tex_coord_index, int grid,
            bool reflect_x, bool reflect_y
    );
    void build_patch(
            glm::vec3 patch[][4],
            std::vector<GLfloat>& b, std::vector<GLfloat>& db,
            std::vector<GLfloat>& v, std::vector<GLfloat>& n,
            std::vector<GLfloat>& tc, std::vector<GLuint>& el,
            int& index, int& element_index, int& tex_coord_index, int grid,
            glm::mat3 reflect, bool invert_normal
    );
    void get_patch(int patch_number, glm::vec3 patch[][4], bool reverse_v);

    void compute_basis_functions(std::vector<GLfloat>& b, std::vector<GLfloat>& db, int grid);
    glm::vec3 evaluate(int grid_u, int grid_v, std::vector<GLfloat>& b, glm::vec3 patch[][4]);
    glm::vec3 evaluate_normal(int grid_u, int grid_v, std::vector<GLfloat>& b, std::vector<GLfloat>& db, glm::vec3 patch[][4]);
    void move_lid(int grid, std::vector<GLfloat>& p, const glm::mat4& lid_transform);

public:
    Teapot(int grid, const glm::mat4& lid_transform);
};


#endif //ENGINE_TEAPOT_H
