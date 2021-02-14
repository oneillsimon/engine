//
// Created by simon on 13/12/2020.
//

#include "mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices,
           const std::vector<Texture>& textures) : vertices(vertices), indices(indices), textures(textures) {
    this->set_up_mesh();
}

void Mesh::set_up_mesh() {
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VAO);

    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &this->indices[0], GL_STATIC_DRAW);

    // Vertex positions.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Vertex normals.
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // Vertex texture coordinates.
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture_coordinates));

    glBindVertexArray(0);
}

void Mesh::draw(const ShaderProgram& shader) {
    unsigned int diffuse_number = 0;
    unsigned int specular_number = 0;

    for (unsigned int i = 0; i < this->textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string number;
        std::string name = this->textures[i].type;

        if (name == "texture_diffuse") {
            number = std::to_string(diffuse_number++);
        } else if (name == "texture_specular") {
            number = std::to_string(specular_number++);
        }

        name = "material." + name.append(number);

        shader.set_uniform(name, (float)i);
        glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    // Draw mesh.
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
