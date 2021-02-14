//
// Created by simon on 31/01/2021.
//

#include <iostream>

#include "ModelLoadingApp.h"

#include "components/camera_component.h"

bool capture_input = false;

ModelLoadingApp::ModelLoadingApp() : Application() {
    this->root->add_component("camera",new CameraComponent());
}


void ModelLoadingApp::initialise(const InputProcessor &input) {
    Application::initialise(input);

    stbi_set_flip_vertically_on_load(true);

    this->shader_program.add_shader(Shader::vertex_shader("shaders/model_loading/model_loading.vs.glsl"));
    this->shader_program.add_shader(Shader::fragment_shader("shaders/model_loading/model_loading.fs.glsl"));
    this->shader_program.link();

    this->our_model = Model("/home/simon/projects/engine/src/resources/models/guitar_backpack/backpack.obj");

    glEnable(GL_DEPTH_TEST);
}

void ModelLoadingApp::update(const double &delta, const InputProcessor &input) {
    Application::update(delta, input);

    if (capture_input) {
        input.set_input_mode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        input.set_input_mode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (input.get_key(GLFW_KEY_I, GLFW_PRESS)) {
        capture_input = true;
    }

    if (input.get_key(GLFW_KEY_ESCAPE, GLFW_PRESS)) {
        capture_input = false;
    }

    if (input.get_key(GLFW_KEY_Q, GLFW_PRESS)) {
        this->stop();
    }
}

void ModelLoadingApp::render(const double &delta) {
    Application::render(delta);

    glClearColor(0.5f, 0.4f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->shader_program.use();

    auto* camera = this->root->get_component<CameraComponent>("camera");

    // View/Projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera->get_zoom()), 800.0f/600.0f, 0.1f, 100.0f);
    glm::mat4 view = camera->get_view_matrix();

    this->shader_program.set_uniform("projection", projection);
    this->shader_program.set_uniform("view", view);

    // World transformation.
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
    this->shader_program.set_uniform("model", model);

    this->our_model.draw(this->shader_program);
}
