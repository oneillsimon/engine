//
// Created by simon on 20/02/2021.
//

#include <iostream>
#include "triangle_mesh.h"

void TriangleMesh::init_buffers(std::vector<GLuint> *indices, std::vector<GLfloat> *points,
                                std::vector<GLfloat> *normals, std::vector<GLfloat> *tex_coords,
                                std::vector<GLfloat> *tangents) {
    // Must contain data for indices, points and normals.
    if (indices == nullptr || points == nullptr || normals == nullptr) {
        //TODO: Throw an exception here?
        return;
    }

    number_of_vertices = static_cast<GLuint>(indices->size());

    GLuint index_buffer = 0;
    GLuint position_buffer = 0;
    GLuint normal_buffer = 0;
    GLuint tex_coords_buffer = 0;
    GLuint tangent_buffer = 0;

    glGenBuffers(1, &index_buffer);
    buffers.push_back(index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(GLuint), indices->data(), GL_STATIC_DRAW);

    glGenBuffers(1, &position_buffer);
    buffers.push_back(position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glBufferData(GL_ARRAY_BUFFER, points->size() * sizeof(GLfloat), points->data(), GL_STATIC_DRAW);

    glGenBuffers(1, &normal_buffer);
    buffers.push_back(normal_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glBufferData(GL_ARRAY_BUFFER, normals->size() * sizeof(GLfloat), normals->data(), GL_STATIC_DRAW);

    if (tex_coords != nullptr) {
        glGenBuffers(1, & tex_coords_buffer);
        buffers.push_back(tex_coords_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, tex_coords_buffer);
        glBufferData(GL_ARRAY_BUFFER, tex_coords->size() * sizeof(GLfloat), tex_coords->data(), GL_STATIC_DRAW);
    }

    if (tangents != nullptr) {
        glGenBuffers(1, &tangent_buffer);
        buffers.push_back(tangent_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, tangent_buffer);
        glBufferData(GL_ARRAY_BUFFER, tangents->size() * sizeof(GLfloat), tangents->data(), GL_STATIC_DRAW);
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Indices.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

    // Position.
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0); // Vertex position.

    // Normal.
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1); // Normal.

    // Tex coords.
    if (tex_coords != nullptr) {
        glBindBuffer(GL_ARRAY_BUFFER, tex_coords_buffer);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(2); // Tex coord.
    }

    // Tangents.
    if (tangents != nullptr) {
        glBindBuffer(GL_ARRAY_BUFFER, tangent_buffer);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(3); // Tangents.
    }

    glBindVertexArray(0);
}

void TriangleMesh::delete_buffers() {
    if (!buffers.empty()) {
        glDeleteBuffers(static_cast<GLsizei>(buffers.size()), buffers.data());
        buffers.clear();
    }

    if (vao != 0) {
        glDeleteVertexArrays(1, &vao);
        vao = 0;
    }
}

TriangleMesh::~TriangleMesh() {
    delete_buffers();
}

void TriangleMesh::render() const {
    if (vao == 0) {
        //TODO: Raise exception here?
        return;
    }

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, number_of_vertices, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

GLuint TriangleMesh::get_vao() const {
    return vao;
}
