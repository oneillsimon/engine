//
// Created by simon on 17/02/2021.
//

#include <sys/stat.h>

#include "glsl_program.h"

int GLSLProgram::get_uniform_location(const std::string &name) {
    auto position = uniform_locations.find(name);

    if (position == uniform_locations.end()) {
        uniform_locations[name] = glGetUniformLocation(handle, name.c_str());
    }
    return uniform_locations[name];
}

bool GLSLProgram::file_exists(const std::string &filename) {
    struct stat info {};
    auto result = stat(filename.c_str(), &info);
    return result == 0;
}

GLSLProgram::GLSLProgram() : handle(0), linked(false) {

}

GLSLProgram::~GLSLProgram() {
    if (handle == 0) {
        return;
    }

    // Query the number of attached shaders.
    GLint num_shaders = 0;
    glGetProgramiv(handle, GL_ATTACHED_SHADERS, &num_shaders);

    // Get the names of the shaders.
    auto* shader_names = new GLuint[num_shaders];
    glGetAttachedShaders(handle, num_shaders, nullptr, shader_names);

    // Delete each shader.
    for (auto i = 0; i < num_shaders; i++) {
        glDeleteShader(shader_names[i]);
    }

    // Delete the program.
    glDeleteProgram(handle);

    delete[] shader_names;
}

void GLSLProgram::compile_shader(const std::string &filename, GLSLShaderType shader_type) {
    if (!file_exists(filename)) {
        throw GLSLException("Shader: " + filename + "not found.");
    }

    std::ifstream in_file(filename, std::ios::in);
    if (!in_file) {
        throw GLSLException("Unable to open: " + filename + ".");
    }

    // Get the contents of the file.
    std::stringstream code;
    code << in_file.rdbuf();
    in_file.close();

    if (handle <= 0) {
        handle = glCreateProgram();
        if (handle == 0) {
            throw GLSLException("Unable to create shader program.");
        }
    }

    GLuint shader_handle = glCreateShader(shader_type);

    auto shader_str = code.str();
    const auto* shader_source = shader_str.c_str();
    glShaderSource(shader_handle, 1, &shader_source, nullptr);

    glCompileShader(shader_handle);

    // Check for errors.
    int result;
    glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
        // Shader compilation failed. Let's get the log.
        int length = 0;
        std::string log;

        glGetShaderiv(shader_handle, GL_INFO_LOG_LENGTH, &length);
        if (length > 0) {
            char* c_log = new char[length];
            int written = 0;
            glGetShaderInfoLog(shader_handle, length, &written, c_log);
            log = c_log;
            delete []c_log;
        }

        std::string message = (filename.empty() ? "" : filename + ": ") + "Shader compilation failed.";
        message += " " + log;
        throw GLSLException(message);
    }

    // Compilation succeeded so we can attach the shader.
    glAttachShader(handle, shader_handle);
}

void GLSLProgram::link() {
    if (linked) {
        return;
    }

    if (handle <= 0) {
        throw GLSLException("Program has not been compiled");
    }

    glLinkProgram(handle);

    int status = 0;
    glGetProgramiv(handle, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        int length = 0;
        std::string log;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);

        if (length > 0) {
            char* c_log = new char[length];
            int written = 0;
            glGetProgramInfoLog(handle, length, &written, c_log);
            log = c_log;
            delete[] c_log;
        }

        throw GLSLException("Program link failed. " + log);
    }

    linked = true;
}

void GLSLProgram::use() const {
    if (!is_linked()) {
        throw GLSLException("Program has not been linked.");
    }
    glUseProgram(handle);
}

void GLSLProgram::validate() const {
    if (!is_linked()) {
        throw GLSLException("Program has not been linked.");
    }

    GLint status;
    glValidateProgram(handle);
    glGetProgramiv(handle, GL_VALIDATE_STATUS, &status);

    if (status == GL_FALSE) {
        int length = 0;
        std::string log;

        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);

        if (length > 0) {
            char* c_log = new char[length];
            int written = 0;
            glGetProgramInfoLog(handle, length, &written, c_log);
            log = c_log;
            delete[] c_log;
        }

        throw GLSLException("Program failed to validate. " + log);
    }
}

int GLSLProgram::get_handle() const {
    return handle;
}

bool GLSLProgram::is_linked() const {
    return linked;
}

void GLSLProgram::bind_attribute_location(GLuint location, const std::string &name) const {
    glBindAttribLocation(handle, location, name.c_str());
}

void GLSLProgram::bind_fragment_data_location(GLuint location, const std::string &name) const {
    glBindFragDataLocation(handle, location, name.c_str());
}

void GLSLProgram::set_uniform(const std::string& name, float x, float y, float z) {
    glUniform3f(get_uniform_location(name), x, y, z);
}

void GLSLProgram::set_uniform(const std::string& name, const glm::vec2 &v) {
    glUniform2f(get_uniform_location(name), v.x, v.y);
}

void GLSLProgram::set_uniform(const std::string& name, const glm::vec3 &v) {
    this->set_uniform(name, v.x, v.y, v.z);
}

void GLSLProgram::set_uniform(const std::string& name, const glm::vec4 &v) {
    glUniform4f(get_uniform_location(name), v.x, v.y, v.z, v.w);
}

void GLSLProgram::set_uniform(const std::string& name, const glm::mat3 &m) {
    glUniformMatrix3fv(get_uniform_location(name), 1, GL_FALSE, &m[0][0]);
}

void GLSLProgram::set_uniform(const std::string& name, const glm::mat4 &m) {
    glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &m[0][0]);
}

void GLSLProgram::set_uniform(const std::string& name, float f) {
    glUniform1f(get_uniform_location(name), f);
}

void GLSLProgram::set_uniform(const std::string& name, int i) {
    glUniform1i(get_uniform_location(name), i);
}

void GLSLProgram::set_uniform(const std::string& name, bool b) {
    glUniform1i(get_uniform_location(name), static_cast<GLint>(b));
}

void GLSLProgram::set_uniform(const std::string& name, GLuint value) {
    glUniform1ui(get_uniform_location(name), static_cast<GLint>(value));
}

std::string GLSLProgram::get_type_string(GLenum type) {
    //TODO: Is there a better way to do this? Should come up with a more comprehensive mapping.
    switch (type) {
        case GL_FLOAT:
            return "float";
        case GL_FLOAT_VEC2:
            return "vec2";
        case GL_FLOAT_VEC3:
            return "vec3";
        case GL_FLOAT_VEC4:
            return "vec4";
        case GL_DOUBLE:
            return "double";
        case GL_INT:
            return "int";
        case GL_UNSIGNED_INT:
            return "unsigned int";
        case GL_BOOL:
            return "bool";
        case GL_FLOAT_MAT2:
            return "mat2";
        case GL_FLOAT_MAT3:
            return "mat3";
        case GL_FLOAT_MAT4:
            return "mat4";
        default:
            return "?";
    }
}
