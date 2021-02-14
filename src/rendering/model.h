//
// Created by simon on 24/01/2021.
//

#ifndef ENGINE_MODEL_H
#define ENGINE_MODEL_H

#include <iostream>
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "shader_program.h"

class Model {
private:
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;

    void load(const std::string& path);
    std::vector<Texture> load_material_textures(aiMaterial* material, aiTextureType type, const std::string& type_name);
    void process_node(aiNode* node, const aiScene* scene);
    Mesh process_mesh(aiMesh* mesh, const aiScene* scene);

public:
    Model() = default;
    Model(const std::string& path);
    void draw(const ShaderProgram& shader_program);
};


#endif //ENGINE_MODEL_H
