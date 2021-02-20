//
// Created by simon on 17/02/2021.
//

#include <sys/stat.h>

#include "glsl_program.h"

void GLSLProgram::set_uniform_locations() {
    uniform_locations.clear();

    GLint num_uniforms = 0;
    glGetProgramInterfaceiv(handle, GL_UNIFORM, GL_ACTIVE_RESOURCES, &num_uniforms);

    GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX };

    for (GLint i = 0; i < num_uniforms; i++) {
        GLint results[4];
        glGetProgramResourceiv(handle, GL_UNIFORM, i, 4, properties, 4, nullptr, results);

        if (results[3] != -1) {
            continue; // Skip uniforms in blocks.
        }

        GLint name_buffer_size = results[0] + 1;
        char* name = new char[name_buffer_size];
        glGetProgramResourceName(handle, GL_UNIFORM, i, name_buffer_size, nullptr, name);
        uniform_locations[name] = results[2];
        delete[] name;
    }
}

int GLSLProgram::get_uniform_location(const std::string &name) {
    auto position = uniform_locations.find(name);

    if (position == uniform_locations.end()) {
        uniform_locations[name] = glGetUniformLocation(handle, name.c_str());
    }
    return uniform_locations[name];
}

bool GLSLProgram::file_exists(const std::string &filename) const {
    struct stat info;
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

    // Get the names of the shadres.
    GLuint* shader_names = new GLuint[num_shaders];
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
    auto shader_source = shader_str.c_str();
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
    } else {
        // Compilation succeeded so we can attach the shader.
        glAttachShader(handle, shader_handle);
    }
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
    } else {
        set_uniform_locations();
        linked = true;
    }
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

void GLSLProgram::bind_attribute_location(GLuint location, const std::string &name) {
    glBindAttribLocation(handle, location, name.c_str());
}

void GLSLProgram::bind_fragment_data_location(GLuint location, const std::string &name) {
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
    glUniform1i(get_uniform_location(name), b);
}

void GLSLProgram::set_uniform(const std::string& name, GLuint value) {
    glUniform1ui(get_uniform_location(name), value);
}

void GLSLProgram::print_active_uniforms() const {
    GLint num_uniforms = 0;
    glGetProgramInterfaceiv(handle, GL_UNIFORM, GL_ACTIVE_RESOURCES, &num_uniforms);
    GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX };

    std::cout << "Active uniforms:" << std::endl;
    for (int i = 0; i < num_uniforms; i++) {
        GLint results[4];
        glGetProgramResourceiv(handle, GL_UNIFORM, i, 4, properties, 4, nullptr, results);

        if (results[3] != -1) {
            continue; // Skip uniforms in blocks.
        }
        GLint name_buffer_size = results[0] + 1;
        char* name = new char[name_buffer_size];
        glGetProgramResourceName(handle, GL_UNIFORM, i, name_buffer_size, nullptr, name);

        std::cout << results[2] << name << get_type_string(results[1]) << std::endl;

        delete[] name;
    }
}

void GLSLProgram::print_active_uniform_blocks() const {
    GLint num_blocks = 0;
    glGetProgramInterfaceiv(handle, GL_UNIFORM_BLOCK, GL_ACTIVE_RESOURCES, &num_blocks);
    GLenum block_properties[] = { GL_NUM_ACTIVE_VARIABLES, GL_NAME_LENGTH };
    GLenum block_index[] = { GL_ACTIVE_VARIABLES };
    GLenum properties[] = {  GL_NAME_LENGTH, GL_TYPE, GL_BLOCK_INDEX };

    for (int block = 0; block < num_blocks; block++) {
        GLint block_info[2];
        glGetProgramResourceiv(handle, GL_UNIFORM_BLOCK, block, 2, block_properties, 2, nullptr, block_info);
        GLint num_uniforms = block_info[0];

        char* block_name = new char[block_info[1] + 1];
        glGetProgramResourceName(handle, GL_UNIFORM_BLOCK, block, block_info[1] + 1, nullptr, block_name);

        std::cout << "Uniform block " << block_name << ":" << std::endl;
        delete[] block_name;

        auto uniform_indices = new GLint[num_uniforms];
        glGetProgramResourceiv(handle, GL_UNIFORM_BLOCK, block, 1, block_index, num_uniforms, nullptr, uniform_indices);

        for (auto uniform = 0; uniform < num_uniforms; uniform++) {
            GLint uniform_index = uniform_indices[uniform];
            GLint results[3];
            glGetProgramResourceiv(handle, GL_UNIFORM, uniform_index, 3, properties, 3, nullptr, results);

            GLint name_buffer_size = results[0] + 1;
            auto name = new char[name_buffer_size];
            glGetProgramResourceName(handle, GL_UNIFORM, uniform_index, name_buffer_size, nullptr, name);

            std::cout << name << " " << get_type_string(results[1]) << std::endl;
            delete[] name;
        }

        delete[] uniform_indices;
    }
}

void GLSLProgram::print_active_attributes() const {
    GLint num_attributes;
    glGetProgramInterfaceiv(handle, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &num_attributes);

    GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION };

    std::cout << "Active attributes:" << std::endl;
    for (auto i = 0; i < num_attributes; i++) {
        GLint results[3];
        glGetProgramResourceiv(handle, GL_PROGRAM_INPUT, i, 3, properties, 3, nullptr, results);

        GLint name_buffer_size = results[0] + 1;
        auto name = new char[name_buffer_size];
        glGetProgramResourceName(handle, GL_PROGRAM_INPUT, i, name_buffer_size, nullptr, name);
        std::cout << results[2] << " " << name << " " << get_type_string(results[1]) << std::endl;
        delete[] name;
    }
}

std::string GLSLProgram::get_type_string(GLenum type) const {
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
