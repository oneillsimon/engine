//
// Created by simon on 21/11/2020.
//

#ifndef ENGINE_SHADER_PROGRAM_H
#define ENGINE_SHADER_PROGRAM_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <glad/glad.h>

#include "shader.h"

class ShaderProgram {
private:
    std::vector<Shader> shaders{};
public:
    // The program ID.
    unsigned int ID{};

    ShaderProgram() = default;
    explicit ShaderProgram(std::vector<Shader> shaders);
    void add_shader(const Shader& shader);
    void link();
    void use() const;

    // Uniform utility methods;
    void set_uniform(const std::string& name, const bool& value) const;
    void set_uniform(const std::string& name, const float& value) const;
    void set_uniform(const std::string& name, const int& value) const;

    int get_uniform_location(const std::string& name) const;
};

#endif //ENGINE_SHADER_PROGRAM_H
