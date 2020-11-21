//
// Created by simon on 14/11/2020.
//

#include <iostream>

#include "learn_opengl_application.h"

LearnOpenGlApp::LearnOpenGlApp() : shader_program(ShaderProgram()) {
}

void LearnOpenGlApp::initialise() {
    Application::initialise();

    float vertices[] = {
             // positions        // colors
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
    };

    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
    };

    // Copy our vertices array in a buffer for OpenGL to use.
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Then set the vertex attributes pointers.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(VAO);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    this->shader_program.add_shader(Shader::vertex_shader("shaders/learnopengl_shaders/shader.vs.glsl"));
    this->shader_program.add_shader(Shader::fragment_shader("shaders/learnopengl_shaders/shader.fs.glsl"));
    this->shader_program.link();
}

void LearnOpenGlApp::render(const double& delta) {
    Application::render(delta);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    this->shader_program.use();
    this->shader_program.set_uniform("x_offset", -0.8f);
    glBindVertexArray(VAO);


    glDrawArrays(GL_TRIANGLES, 0, 3);
}
