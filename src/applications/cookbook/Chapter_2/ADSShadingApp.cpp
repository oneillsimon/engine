//
// Created by simon on 20/02/2021.
//

#include "ADSShadingApp.h"

ADSShadingApp::ADSShadingApp() : torus(0.7f, 0.3f, 30, 30) {

}


void ADSShadingApp::initialise(const InputProcessor &input) {
    Application::initialise(input);

    program = GLSLProgram();
    program.compile_shader("shaders/cookbook/ads.vert.glsl", GLSLShaderType::VERTEX);
    program.compile_shader("shaders/cookbook/ads.frag.glsl", GLSLShaderType::FRAGMENT);
    program.link();
    program.use();

    glEnable(GL_DEPTH_TEST);

    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-35.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(35.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    projection = glm::perspective(glm::radians(70.0f), (float)800/600, 0.3f, 100.0f);

    program.set_uniform("Kd", 0.9f, 0.5f, 0.3f);
    program.set_uniform("Ld", 1.0f, 1.0f, 1.0f);
    program.set_uniform("LightPosition", view * glm::vec4(0.5f, 0.5f, 2.0f, 1.0f));
}

void ADSShadingApp::update(const double &delta, const InputProcessor &input) {
    Application::update(delta, input);

    if (input.get_key(GLFW_KEY_ESCAPE, GLFW_PRESS)) {
        this->stop();
    }
}

void ADSShadingApp::render(const double &delta) {
    Application::render(delta);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

    auto mv = view * model;

    program.set_uniform("ModelViewMatrix", mv);
    program.set_uniform("NormalMatrix", glm::mat3(
            glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2])
    ));
    program.set_uniform("MVP", projection * mv);

    torus.render();
}

void ADSShadingApp::stop() {
    Application::stop();
}