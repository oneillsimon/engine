//
// Created by simon on 20/02/2021.
//

#ifndef ENGINE_TRIANGLE_MESH_H
#define ENGINE_TRIANGLE_MESH_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "mesh.h"

class TriangleMesh : Mesh {
protected:
    GLuint number_of_vertices;
    GLuint vao;

    std::vector<GLuint> buffers;

    virtual void init_buffers(
            std::vector<GLuint>* indices,
            std::vector<GLfloat>* points,
            std::vector<GLfloat>* normals,
            std::vector<GLfloat>* tex_coords = nullptr,
            std::vector<GLfloat>* tangents = nullptr
            );

    virtual void delete_buffers();

public:
    virtual ~TriangleMesh();
    void render() const override;
    GLuint get_vao() const;
};


#endif //ENGINE_TRIANGLE_MESH_H
