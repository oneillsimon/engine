//
// Created by simon on 21/11/2020.
//

#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

enum ShaderType {
  VERTEX,
  FRAGMENT
};


class Shader {
private:
    static int create_shader(const ShaderType& shader_type);
public:
    int shader{};

    Shader(const ShaderType& shader_type, const std::string& path);

    static Shader vertex_shader(const std::string& path);
    static Shader fragment_shader(const std::string& path);
};

#endif //ENGINE_SHADER_H
