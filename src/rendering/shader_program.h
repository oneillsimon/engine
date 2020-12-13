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
#include "material.h"
#include "lights/attenuation.h"
#include "lights/light.h"
#include "lights/directional_light.h"
#include "lights/point_light.h"
#include "lights/spot_light.h"

class ShaderProgram {
private:
    std::vector<Shader> shaders{};

    void set_light_uniform(const std::string& name, const Light& light) const;
    void set_attenuation_uniform(const std::string& name, const Attenuation& attenuation) const;
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
    void set_uniform(const std::string& name, const Material& material) const;
    void set_uniform(const std::string& name, const DirectionalLight& directional_light) const;
    void set_uniform(const std::string& name, const PointLight& point_light) const;
    void set_uniform(const std::string& name, const SpotLight& spot_light) const;

    int get_uniform_location(const std::string& name) const;
};

#endif //ENGINE_SHADER_PROGRAM_H
