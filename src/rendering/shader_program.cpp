//
// Created by simon on 21/11/2020.
//

#include "shader_program.h"

#include <utility>

ShaderProgram::ShaderProgram(std::vector<Shader>  shaders) : shaders(std::move(shaders)) {

}

void ShaderProgram::add_shader(const Shader& shader) {
    this->shaders.push_back(shader);
}

void ShaderProgram::link() {
    this->ID = glCreateProgram();

    for (auto shader : this->shaders) {
        glAttachShader(this->ID, shader.shader);
    }
    glLinkProgram(this->ID);

    int success;
    glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
    if (!success) {
        int info_log_size = 512;
        char info_log[info_log_size];
        glGetProgramInfoLog(this->ID, 512, nullptr, info_log);
        std::cerr << "Failed to link program: " << info_log << std::endl;
    }

    // Delete the shaders now that they're linked to the program.
    for (auto shader : this->shaders) {
        glDeleteShader(shader.shader);
    }
}

void ShaderProgram::use() const {
    glUseProgram(this->ID);
}

void ShaderProgram::set_uniform(const std::string& name, const bool& value) const {
    glUniform1i(this->get_uniform_location(name), static_cast<int>(value));
}

void ShaderProgram::set_uniform(const std::string& name, const float& value) const {
    glUniform1f(this->get_uniform_location(name), value);
}

void ShaderProgram::set_uniform(const std::string& name, const int& value) const {
    glUniform1i(this->get_uniform_location(name), value);
}

int ShaderProgram::get_uniform_location(const std::string& name) const {
    return glGetUniformLocation(this->ID, name.c_str());
}

void ShaderProgram::set_uniform(const std::string& name, const glm::vec2& value) const {
    return glUniform2fv(this->get_uniform_location(name), 1, &value[0]);
}

void ShaderProgram::set_uniform(const std::string& name, const glm::vec3& value) const {
    return glUniform3fv(this->get_uniform_location(name), 1, &value[0]);
}

void ShaderProgram::set_uniform(const std::string& name, const glm::vec4& value) const {
    return glUniform4fv(this->get_uniform_location(name), 1, &value[0]);
}

void ShaderProgram::set_uniform(const std::string& name, const glm::mat2& value) const {
    return glUniformMatrix2fv(this->get_uniform_location(name), 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::set_uniform(const std::string& name, const glm::mat3& value) const {
    return glUniformMatrix3fv(this->get_uniform_location(name), 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::set_uniform(const std::string& name, const glm::mat4& value) const {
    return glUniformMatrix4fv(this->get_uniform_location(name), 1, GL_FALSE, &value[0][0]);
}

