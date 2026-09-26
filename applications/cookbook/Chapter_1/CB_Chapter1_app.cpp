// NOLINT
//
// Created by simon on 14/02/2021.
//

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "CB_Chapter1_app.h"

std::string load_shader_from_file(const std::string& path) {
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

    std::cout << path << std::endl << code.c_str() << std::endl;
//    const char* code_c_str = code.c_str();
    return code;
}

void CB_Chapter1_app::initialise(InputProcessor& input) {
    Application::initialise(input);

    // Compile vertex and fragment shaders.
    // Step 1. Create the shader object.
    GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
    if (vert_shader == 0) {
        std::cerr << "Error creating vertex shader." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Step 2. Copy the source into the shader object.
    auto vert_src = load_shader_from_file("shaders/cookbook/diffuse.vert.glsl");
//    std::cout << vert_src << std::endl;
    const GLchar* code_array[] = { vert_src.c_str() };
    glShaderSource(vert_shader, 1, code_array, NULL);

    // Step 3. Compile the shader.
    glCompileShader(vert_shader);


    // Step 4. Verify the compilation status.
    GLint result;
    glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        std::cerr << "Vertex shader compilation failed." << std::endl;

        GLint log_length;
        glGetShaderiv(vert_shader, GL_INFO_LOG_LENGTH, &log_length);

        if (log_length > 0) {
            char* log = new char[log_length];
            GLsizei written;
            glGetShaderInfoLog(vert_shader, log_length, &written, log);
            std::cerr << "Shader log: " << log << std::endl;
            delete []log;
        }
    }

    // Same for the fragment shader.
    // Step 1. Create the shader object.
    GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    if (frag_shader == 0) {
        std::cerr << "Error creating vertex shader." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Step 2. Copy the source into the shader object.
    auto frag_src = load_shader_from_file("shaders/cookbook/diffuse.frag.glsl");
    const GLchar* frag_code_array[] = { frag_src.c_str() };
    glShaderSource(frag_shader, 1, frag_code_array, NULL);

    // Step 3. Compile the shader.
    glCompileShader(frag_shader);


    // Step 4. Verify the compilation status.;
    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        std::cerr << "Fragment shader compilation failed." << std::endl;

        GLint log_length;
        glGetShaderiv(frag_shader, GL_INFO_LOG_LENGTH, &log_length);

        if (log_length > 0) {
            char* log = new char[log_length];
            GLsizei written;
            glGetShaderInfoLog(frag_shader, log_length, &written, log);
            std::cerr << "Shader log: " << log << std::endl;
            delete []log;
        }
    }

    // Create the program, attach shaders and link them.
    // Step 1. Create the shader program.
    this->program_handle = glCreateProgram();
    if (program_handle == 0) {
        std::cerr << "Error creating program object." << std::endl;
        exit(1);
    }

    // Step 2. Attach the shaders.
    glAttachShader(program_handle, vert_shader);
    glAttachShader(program_handle, frag_shader);

    // Step3. Link and verify link status.
    glLinkProgram(program_handle);

    GLint status;
    glGetProgramiv(program_handle, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        std::cerr << "Failed to link shader program." << std::endl;
        GLint log_length;
        glGetProgramiv(program_handle, GL_INFO_LOG_LENGTH, &log_length);

        if (log_length > 0) {
            char* log = new char[log_length];
            GLsizei written;
            glGetProgramInfoLog(program_handle, log_length, &written, log);
            std::cerr << "Program log: " << log << std::endl;
            delete []log;
        }
    } else {
        glUseProgram(program_handle);
    }

    float position_data[] = {
            -0.8F, -0.8F, 0.0F,
            0.8F, -0.8F, 0.0F,
            0.0F, 0.8F, 0.0F
    };

    float color_data[] = {
            1.0F, 0.0F, 0.0F,
            0.0F, 1.0F, 0.0F,
            0.0F, 0.0F, 1.0F
    };

    // Create and populate 2 buffer objects. (VBOs).
    GLuint vbo_handles[2];
    glGenBuffers(2, vbo_handles);
    GLuint position_buffer_handle = vbo_handles[0];
    GLuint color_buffer_handle = vbo_handles[1];


    // Populate the position buffer.
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_handle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), position_data, GL_STATIC_DRAW);

    // Populate the color buffer.
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer_handle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof (float), color_data, GL_STATIC_DRAW);

    // Create and setup the VAO (Vertex Attribute Object).
    glGenVertexArrays(1, &this->vao_handle);
    glBindVertexArray(this->vao_handle);

    // Enable the vertex attribute arrays.
    glEnableVertexAttribArray(0); // Vertex position.
    glEnableVertexAttribArray(1); // Vertex color.

    // Map index 0 to the position buffer.
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_handle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Map index 1 to the color buffer.
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer_handle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void CB_Chapter1_app::update(const double& delta, InputProcessor& input) {
    Application::update(delta, input);
}

void CB_Chapter1_app::render(const double& delta) {
    Application::render(delta);

    auto rotation_matrix = glm::rotate(glm::mat4(1.0F), glm::radians(90.0F), glm::vec3(0.0F, 0.0F, 1.0F));

    GLuint location = glGetUniformLocation(this->program_handle, "RotationMatrix");

    if (location >= 0) {
        glUniformMatrix4fv(location, 1, GL_FALSE, &rotation_matrix[0][0]);
    }

    glBindVertexArray(this->vao_handle);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
