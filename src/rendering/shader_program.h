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
    void set_uniform(const std::string& name, const glm::vec2& value) const;
    void set_uniform(const std::string& name, const glm::vec3& value) const;
    void set_uniform(const std::string& name, const glm::vec4& value) const;
    void set_uniform(const std::string& name, const glm::mat2& value) const;
    void set_uniform(const std::string& name, const glm::mat3& value) const;
    void set_uniform(const std::string& name, const glm::mat4& value) const;
    /*
     * void setVec2(const std::string &name, const glm::vec2 &value) const
    {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string &name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string &name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }*/

    int get_uniform_location(const std::string& name) const;
};

#endif //ENGINE_SHADER_PROGRAM_H
