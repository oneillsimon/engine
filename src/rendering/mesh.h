//
// Created by simon on 13/12/2020.
//

#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H

#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader_program.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture_coordinates;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    void set_up_mesh();

public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);

    void draw(const ShaderProgram& shader);
};


#endif //ENGINE_MESH_H
