//
// Created by simon on 12/12/2020.
//

#include "texture.h"

Texture::Texture() = default;

Texture::Texture(const std::string& path) {
    glGenTextures(1, &this->id);

    int components_per_pixel;
    this->data = stbi_load(path.c_str(), &this->width, &this->height, &components_per_pixel, 0);

    if (this->data) {
        if (components_per_pixel == 1) {
            this->format = GL_RED;
        } else if (components_per_pixel == 3) {
            this->format = GL_RGB;
        } else if (components_per_pixel == 4) {
            this->format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, this->id);
        glTexImage2D(GL_TEXTURE_2D, 0, this->format, this->width, this->height, 0, this->format, GL_UNSIGNED_BYTE, this->data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(this->data);
    } else {
        std::cerr << "Texture failed to load from path: " << path << std::endl;
        stbi_image_free(this->data);
    }
}

unsigned int Texture::ID() const {
    return this->id;
}
