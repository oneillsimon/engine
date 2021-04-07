//
// Created by simon on 17/02/2021.
//

#ifndef ENGINE_GLSL_PROGRAM_H
#define ENGINE_GLSL_PROGRAM_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "glsl_exception.h"

enum GLSLShaderType {
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER,
    GEOMETRY = GL_GEOMETRY_SHADER,
    TESS_CONTROL = GL_TESS_CONTROL_SHADER,
    TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
    COMPUTE = GL_COMPUTE_SHADER
};

class GLSLProgram {
private:
    int handle;
    bool linked;
    std::map<std::string, int> uniform_locations;

    void set_uniform_locations();
    int get_uniform_location(const std::string& name);
    static bool file_exists(const std::string& filename) ;

public:
    GLSLProgram();
    ~GLSLProgram();

    void compile_shader(const std::string& filename, GLSLShaderType shader_type);

    void link();
    void use() const;
    void validate() const;

    [[nodiscard]] int get_handle() const;
    [[nodiscard]] bool is_linked() const;

    void bind_attribute_location(GLuint location, const std::string& name) const;
    void bind_fragment_data_location(GLuint location, const std::string& name) const;

    void set_uniform(const std::string& name, float x, float y, float z);
    void set_uniform(const std::string& name, const glm::vec2& v);
    void set_uniform(const std::string& name, const glm::vec3& v);
    void set_uniform(const std::string& name, const glm::vec4& v);
    void set_uniform(const std::string& name, const glm::mat3& m);
    void set_uniform(const std::string& name, const glm::mat4& m);
    void set_uniform(const std::string& name, float f);
    void set_uniform(const std::string& name, int i);
    void set_uniform(const std::string& name, bool b);
    void set_uniform(const std::string& name, GLuint value);

    //TODO: Make these functions return a list of strings to be printed instead.
    void print_active_uniforms() const;
    void print_active_uniform_blocks() const;
    void print_active_attributes() const;

    [[nodiscard]] static std::string get_type_string(GLenum type) ;
};


#endif //ENGINE_GLSL_PROGRAM_H
