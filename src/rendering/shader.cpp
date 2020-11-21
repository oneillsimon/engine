//
// Created by simon on 21/11/2020.
//

#include "shader.h"

Shader::Shader(const ShaderType& shader_type, const std::string& path) {
    // First, retrieve the shader source code from the file path.
    std::string code;
    std::ifstream file;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // Open the file and read the data into stream.
        file.open(path);

        std::stringstream stream;
        stream << file.rdbuf();
        file.close();

        code = stream.str();
    } catch (const std::ifstream::failure& e) {
        std::cerr << "Failed to read shader file. " << e.what() << std::endl;
    }

    const char* code_c_str = code.c_str();

    // Next, compile the shader.
    int success;

    this->shader = Shader::create_shader(shader_type);
    glShaderSource(this->shader, 1, &code_c_str, nullptr);
    glCompileShader(this->shader);

    // Check for errors.
    glGetShaderiv(this->shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        const int info_log_size = 512;
        char info_log[info_log_size];
        glGetShaderInfoLog(this->shader, info_log_size, nullptr, info_log);
        std::cerr << "Shader compilation failed: " << info_log << std::endl;
    }
}

Shader Shader::vertex_shader(const std::string& path) {
    return { ShaderType::VERTEX, path };
}

Shader Shader::fragment_shader(const std::string& path) {
    return { ShaderType::FRAGMENT, path };
}

int Shader::create_shader(const ShaderType& shader_type) {
    int gl_shader_type;

    switch (shader_type) {
        case FRAGMENT:
            gl_shader_type = GL_FRAGMENT_SHADER;
            break;
        case VERTEX:
        default:
            gl_shader_type = GL_VERTEX_SHADER;
            break;
    }

    return glCreateShader(gl_shader_type);
}

