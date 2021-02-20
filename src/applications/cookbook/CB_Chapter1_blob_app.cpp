//
// Created by simon on 14/02/2021.
//

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstring>

#include "rendering/glsl_program.h"

#include "CB_Chapter1_blob_app.h"

void CB_Chapter1_blob_app::initialise(const InputProcessor& input) {
    Application::initialise(input);

    auto shader_program = GLSLProgram();
    shader_program.compile_shader("shaders/cookbook/blob.vert.glsl", GLSLShaderType::VERTEX);
    shader_program.compile_shader("shaders/cookbook/blob.frag.glsl", GLSLShaderType::FRAGMENT);
    shader_program.link();
    shader_program.use();


    // Get index of block.
    GLuint block_index = glGetUniformBlockIndex(shader_program.get_handle(), "BlobSettings");

    // Allocate space for the buffer to contain the data for the uniform block.
    GLint block_size;
    glGetActiveUniformBlockiv(shader_program.get_handle(), block_index, GL_UNIFORM_BLOCK_DATA_SIZE, &block_size);

    GLubyte* block_buffer;
    block_buffer = (GLubyte*)malloc(block_size);

    // Query the offset of each variable withing the block.
    const GLchar* names[] = { "InnerColor", "OuterColor", "RadiusInner", "RadiusOuter" };
    GLuint indices[4];
    glGetUniformIndices(shader_program.get_handle(), 4, names, indices);

    GLint offset[4];
    glGetActiveUniformsiv(shader_program.get_handle(), 4, indices, GL_UNIFORM_OFFSET, offset);

    // Place data into the buffer at the approriate offset.
    GLfloat outer_color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat inner_color[] = { 1.0f, 1.0f, 0.75f, 1.0f };
    GLfloat inner_radius = 0.25f;
    GLfloat outer_radius = 0.45f;

    memcpy(block_buffer + offset[0], inner_color, 4 * sizeof(GLfloat));
    memcpy(block_buffer + offset[1], outer_color, 4 * sizeof(GLfloat));
    memcpy(block_buffer + offset[2], &inner_radius, sizeof(GLfloat));
    memcpy(block_buffer + offset[3], &outer_radius, sizeof(GLfloat));

    // Create the buffer object and copy the data into it.
    GLuint ubo_handle;
    glGenBuffers(1, &ubo_handle);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_handle);
    glBufferData(GL_UNIFORM_BUFFER, block_size, block_buffer, GL_DYNAMIC_DRAW);

    // Bind the buffer object to the uniform buffer binding point specified in the frag shader.
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo_handle);

    float position_data[] = {
            -0.8f, -0.8f, 0.0f,
            0.8f, -0.8f, 0.0f,
            0.8f, 0.8f, 0.0f,

            -0.8f, -0.8f, 0.0f,
            0.8f, 0.8f, 0.0f,
            -0.8f, 0.8f, 0.0f
    };

    float tex_data[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,

            0.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
    };

    GLuint vbo_handles[2];
    glGenBuffers(2, vbo_handles);
    GLuint position_buffer_handle = vbo_handles[0];
    GLuint tex_coords_buffer_handle = vbo_handles[1];

    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_handle);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), position_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, tex_coords_buffer_handle);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), tex_data, GL_STATIC_DRAW);

    // Create and setup VAO.
    glGenVertexArrays(1, &vao_handle);
    glBindVertexArray(vao_handle);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_handle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, tex_coords_buffer_handle);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
}

void CB_Chapter1_blob_app::update(const double& delta, const InputProcessor& input) {
    Application::update(delta, input);
}

void CB_Chapter1_blob_app::render(const double& delta) {
    Application::render(delta);

    auto rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

//    GLuint location = glGetUniformLocation(this->program_handle, "RotationMatrix");
//
//    if (location >= 0) {
//        glUniformMatrix4fv(location, 1, GL_FALSE, &rotation_matrix[0][0]);
//    }

    glBindVertexArray(this->vao_handle);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
