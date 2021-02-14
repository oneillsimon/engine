//
// Created by simon on 24/01/2021.
//

#include <stb_image.h>

#include "model.h"

Model::Model(const std::string& path) {
    this->load(path);
}

void Model::draw(const ShaderProgram& shader_program) {
    for (auto mesh : this->meshes) {
        mesh.draw(shader_program);
    }
}

void Model::load(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Error loading file: " << importer.GetErrorString() << std::endl;
        return;
    }

    this->directory = path.substr(0, path.find_last_of('/'));
    this->process_node(scene->mRootNode, scene);
}

unsigned int texture_from_file(const std::string& path, const std::string& directory) {
    auto filename = directory + '/' + path;

    unsigned int texture_id;
    glGenTextures(1, &texture_id);

    int width, height, number_of_components;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &number_of_components, 0);

    if (data) {
        GLenum format;
        if (number_of_components == 1) {
            format = GL_RED;
        } else if (number_of_components == 3) {
            format = GL_RGB;
        } else if (number_of_components == 4) {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cerr << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
    return texture_id;
}

std::vector<Texture> Model::load_material_textures(aiMaterial* material, aiTextureType type, const std::string& type_name) {
    std::vector<Texture> textures;

    for (auto i = 0; i < material->GetTextureCount(type); i++) {
        aiString ai_string;
        material->GetTexture(type, i, &ai_string);

        bool skip_load = false;

        for (auto &t : textures_loaded) {
            if (std::strcmp(t.path.data(), ai_string.C_Str()) == 0) {
                textures.push_back(t);
                skip_load = true;
                break;
            }
        }

        if (!skip_load) {
            Texture texture;
            std::string path = std::string(ai_string.C_Str());
            texture.id = texture_from_file(path, this->directory);
            texture.type = type_name;
            texture.path = path;
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }
    return textures;
}

void Model::process_node(aiNode* node, const aiScene* scene) {
    // Process all the node's meshes (if any).
    for (auto i = 0; i < node->mNumMeshes; i++) {
        auto* mesh = scene->mMeshes[node->mMeshes[i]];
        this->meshes.push_back(this->process_mesh(mesh, scene));
    }

    // The do the same for each of the node's children.
    for (auto i = 0; i < node->mNumChildren; i++) {
        this->process_node(node->mChildren[i], scene);
    }
}

Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (auto i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        // Process vertex positions, normals and texture coordinates.
        glm::vec3 vertex_position;
        glm::vec3 vertex_normals;

        vertex_position.x = mesh->mVertices[i].x;
        vertex_position.y = mesh->mVertices[i].y;
        vertex_position.z = mesh->mVertices[i].z;
        vertex.position = vertex_position;

        vertex_normals.x = mesh->mNormals[i].x;
        vertex_normals.y = mesh->mNormals[i].y;
        vertex_normals.z = mesh->mNormals[i].z;
        vertex.normal = vertex_normals;

        if (mesh->mTextureCoords[0]) {
            glm::vec2 vertex_texture_coordinates;
            vertex_texture_coordinates.x = mesh->mTextureCoords[0][i].x;
            vertex_texture_coordinates.y = mesh->mTextureCoords[0][i].y;
            vertex.texture_coordinates = vertex_texture_coordinates;
        } else {
            vertex.texture_coordinates = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    // Process indices.
    for (auto i = 0; i < mesh->mNumFaces; i++) {
        auto face = mesh->mFaces[i];
        for (auto j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Process material.
    if (mesh->mMaterialIndex >= 0) {
        auto* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuse_maps = load_material_textures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());

        std::vector<Texture> specular_maps = load_material_textures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());
    }

    return Mesh(vertices, indices, textures);
}
