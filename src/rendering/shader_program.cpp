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


void ShaderProgram::set_light_uniform(const std::string& name, const Light &light) const {
    set_uniform(name + ".ambient", light.get_ambient());
    set_uniform(name + ".diffuse", light.get_diffuse());
    set_uniform(name + ".specular", light.get_specular());
}


void ShaderProgram::set_attenuation_uniform(const std::string& name, const Attenuation& attenuation) const {
    set_uniform(name + ".constant", attenuation.get_constant());
    set_uniform(name + ".linear", attenuation.get_linear());
    set_uniform(name + ".quadratic", attenuation.get_quadratic());
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
    int b = glGetUniformLocation(this->ID, name.c_str());
    return  b;
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

void ShaderProgram::set_uniform(const std::string &name, const Material &material) const {
    set_uniform(name + ".diffuse", material.get_diffuse());
    set_uniform(name + ".specular", material.get_specular());
    set_uniform(name + ".shininess", material.get_shininess());
}

void ShaderProgram::set_uniform(const std::string &name, const DirectionalLight& directional_light) const {
    set_uniform(name + ".direction", directional_light.get_direction());
    set_light_uniform(name, directional_light);
}

void ShaderProgram::set_uniform(const std::string &name, const PointLight& point_light) const {
    set_uniform(name + ".position", point_light.get_position());
    set_light_uniform(name, point_light);
    set_attenuation_uniform(name, point_light.get_attenuation());
}

void ShaderProgram::set_uniform(const std::string &name, const SpotLight &spot_light) const {
    set_uniform(name + ".position", spot_light.get_position());
    set_uniform(name + ".direction", spot_light.get_direction());
    set_uniform(name + ".cut_off", spot_light.get_cut_off());
    set_uniform(name + ".outer_cut_off", spot_light.get_outer_cut_off());
    set_light_uniform(name, spot_light);
    set_attenuation_uniform(name, spot_light.get_attenuation());
}
