//
// Created by simon on 12/12/2020.
//

#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

class Texture {
private:
    int width{};
    int height{};
    GLenum format{};
    std::string path;
    unsigned int id{};
    unsigned char* data{};

public:
    Texture();
    explicit Texture(const std::string& path);

    unsigned int ID() const;
};


#endif //ENGINE_TEXTURE_H
