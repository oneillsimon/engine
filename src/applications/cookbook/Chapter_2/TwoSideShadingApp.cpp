//
// Created by simon on 20/02/2021.
//

#include "TwoSideShadingApp.h"
//
//void key_callback(void* window, int key, int scancode, int action, int mods) {
//    auto instance = static_cast<TwoSideShadingApp*>(glfwGetWindowUserPointer(static_cast<GLFWwindow*>(window)));
//    if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
//        if (std::distance(instance->current_material, instance->materials.end()) == 1) {
//            instance->current_material = instance->materials.begin();
//        } else {
//            instance->current_material++;
//        }
//        std::cout << "Using material: " << instance->current_material->first << std::endl;
//    }
//
//    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
//        if (instance->current_material == instance->materials.begin()) {
//            instance->current_material = instance->materials.end();
//            instance->current_material--;
//        } else {
//            instance->current_material--;
//        }
//        std::cout << "Using material: " << instance->current_material->first << std::endl;
//    }
//}

TwoSideShadingApp::TwoSideShadingApp() :
teapot(13, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.5f, 0.25f))) {

}


void TwoSideShadingApp::initialise(InputProcessor& input) {
    Application::initialise(input);

    program = GLSLProgram();
    program.compile_shader("shaders/cookbook/adstwosided.vert.glsl", GLSLShaderType::VERTEX);
    program.compile_shader("shaders/cookbook/adstwosided.frag.glsl", GLSLShaderType::FRAGMENT);
    program.link();
    program.use();

    glEnable(GL_DEPTH_TEST);

    view = glm::lookAt(glm::vec3(2.0f,4.0f,2.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
    projection = glm::perspective(glm::radians(70.0f), (float)800/600, 0.3f, 100.0f);

    auto world_light = glm::vec4(2.0f, 4.0f, 2.0f, 1.0f);
    model = glm::rotate(glm::mat4(), glm::radians(0.0f), glm::vec3(0.0f,1.0f,0.0f));
    program.set_uniform("Light.Position", view * model * world_light);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0,-1.0,0.0));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f,0.0f,0.0f));
    program.set_uniform("Light.Ld", 1.0f, 1.0f, 1.0f);
    program.set_uniform("Light.La", 0.4f, 0.4f, 0.4f);
    program.set_uniform("Light.Ls", 1.0f, 1.0f, 1.0f);

    materials = std::map<std::string, Material>{
            std::make_pair("A", Material(glm::vec3(0.9f, 0.5f, 0.3f), glm::vec3(0.9f, 0.5f, 0.3f), glm::vec3(0.8f, 0.8f, 0.8f), 100.0f)),
            std::make_pair("BLACK_PLASTIC", Materials::BLACK_PLASTIC),
            std::make_pair("BLACK_RUBBER", Materials::BLACK_RUBBER),
            std::make_pair("BRASS", Materials::BRASS),
            std::make_pair("BRONZE", Materials::BRONZE),
            std::make_pair("CHROME", Materials::CHROME),
            std::make_pair("COPPER", Materials::COPPER),
            std::make_pair("CYAN_PLASTIC", Materials::CYAN_PLASTIC),
            std::make_pair("CYAN_RUBBER", Materials::CYAN_RUBBER),
            std::make_pair("EMERALD", Materials::EMERALD),
            std::make_pair("GOLD", Materials::GOLD),
            std::make_pair("GREEN_PLASTIC", Materials::GREEN_PLASTIC),
            std::make_pair("GREEN_RUBBER", Materials::GREEN_RUBBER),
            std::make_pair("JADE", Materials::JADE),
            std::make_pair("OBSIDIAN", Materials::OBSIDIAN),
            std::make_pair("PEARL", Materials::PEARL),
            std::make_pair("RED_PLASTIC", Materials::RED_PLASTIC),
            std::make_pair("RED_RUBBER", Materials::RED_RUBBER),
            std::make_pair("RUBY", Materials::RUBY),
            std::make_pair("SILVER", Materials::SILVER),
            std::make_pair("TURQUOISE", Materials::TURQUOISE),
            std::make_pair("YELLOW_PLASTIC", Materials::YELLOW_PLASTIC),
            std::make_pair("YELLOW_RUBBER", Materials::YELLOW_RUBBER),
            std::make_pair("WHITE_PLASTIC", Materials::WHITE_PLASTIC),
            std::make_pair("WHITE_RUBBER", Materials::WHITE_RUBBER)
    };

    current_material = materials.begin();
}

void TwoSideShadingApp::update(const double &delta, InputProcessor& input) {
    Application::update(delta, input);

    if (input.is_key_down(GLFW_KEY_ESCAPE)) {
        this->stop();
    }
}

void TwoSideShadingApp::render(const double &delta) {
    Application::render(delta);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

    auto material = current_material->second;
    program.set_uniform("Material.Kd", material.k_d);
    program.set_uniform("Material.Ks", material.k_s);
    program.set_uniform("Material.Ka", material.k_a);
    program.set_uniform("Material.Shininess", material.shininess);

    auto mv = view * model;

    program.set_uniform("ModelViewMatrix", mv);
    program.set_uniform("NormalMatrix", glm::mat3(
            glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2])
    ));
    program.set_uniform("MVP", projection * mv);

    teapot.render();
}

void TwoSideShadingApp::stop() {
    Application::stop();
}