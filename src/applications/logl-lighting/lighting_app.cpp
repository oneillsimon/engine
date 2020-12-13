//
// Created by simon on 11/12/2020.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "lighting_app.h"
#include "rendering/texture.h"
#include "rendering/lights/directional_light.h"

bool capture_input = false;

auto light_position = glm::vec3(1.2f, 1.0f, 2.0f);

Texture diffuse_texture;
Texture specular_texture;

glm::vec3 positions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
};

void key_callback(void* window, int key, int scan_code, int action, int mods) {
    if (key == GLFW_KEY_I && action == GLFW_PRESS) {
        capture_input = !capture_input;
    }
}

LightingApp::LightingApp() {
    this->root->add_component("camera", new CameraComponent());
}

void LightingApp::initialise(const InputProcessor &input) {
    Application::initialise(input);

//    input.set_key_callback(static_cast<GLFWwindow*>(input.get_window()), key_callback);

    this->lightingShader.add_shader(Shader::vertex_shader("shaders/learnopengl_lighting_shaders/colours.vs.glsl"));
    this->lightingShader.add_shader(Shader::fragment_shader("shaders/learnopengl_lighting_shaders/colours.fs.glsl"));
    this->lightingShader.link();

    this->lightCubeShader.add_shader(Shader::vertex_shader("shaders/learnopengl_lighting_shaders/light_cube.vs.glsl"));
    this->lightCubeShader.add_shader(Shader::fragment_shader("shaders/learnopengl_lighting_shaders/light_cube.fs.glsl"));
    this->lightCubeShader.link();

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    // First, configure the cube's VBO and VAO
    glGenVertexArrays(1, &this->cubeVAO);
    glGenBuffers(1, &this->VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glBindVertexArray(this->cubeVAO);

    // Position attribute.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Normal attribute.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3  * sizeof(float)));
    glEnableVertexAttribArray(1);
    // TexCoords attribute.
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Second, configure the light's VAO. (VBO stays te same since the vertices are the same for the light object which is also a 3D cube.
    glGenVertexArrays(1, &this->lightVAO);
    glBindVertexArray(this->lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);

    // Load textures.
    diffuse_texture = Texture("resources/textures/woodencontainer.png");
    specular_texture = Texture("resources/textures/woodencontainer_specular.png");
    this->lightingShader.use();
//    this->lightingShader.set_uniform("material.diffuse", 0);
//    this->lightingShader.set_uniform("material.specular", 1);
}

void LightingApp::update(const double &delta, const InputProcessor &input) {
    Application::update(delta, input);

//    light_position = glm::vec3(sin(glfwGetTime()) * 2.5f, light_position.y,  cos(glfwGetTime()) * 2.5f);

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

void LightingApp::render(const double &delta) {
    Application::render(delta);

    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto* camera = this->root->get_component<CameraComponent>("camera");

    // Activate the shader.
    this->lightingShader.use();
    this->lightingShader.set_uniform("object_colour", glm::vec3(1.0f, 0.5f, 0.31f));
    this->lightingShader.set_uniform("light_colour", glm::vec3(1.0f, 1.0f, 1.0f));
//    this->lightingShader.set_uniform("light_position", light_position);
    this->lightingShader.set_uniform("view_position", camera->get_position());

    auto material = Material(1, 0, 32.0f);
    this->lightingShader.set_uniform("material", material);

    glm::vec3 light_colour = glm::vec3(1.0f, 1.0f, 1.0f);
//    light_colour.x = sin(glfwGetTime() * 2.0f);
//    light_colour.y = sin(glfwGetTime() * 0.7f);
//    light_colour.z = sin(glfwGetTime() * 1.3f);

//    glm::vec3 diffuse_colour = light_colour * glm::vec3(0.5f);
//    glm::vec3 ambient_colour = diffuse_colour * glm::vec3(0.2f);
//    glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);

    glm::vec3 diffuse_colour = glm::vec3(0.8f, 0.8f, 0.8f);
    glm::vec3 ambient_colour = glm::vec3(0.1f, 0.1f, 0.1f);
    glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);

//    this->lightingShader.set_uniform("light.ambient", ambient_colour);
//    this->lightingShader.set_uniform("light.diffuse", diffuse_colour);
//    this->lightingShader.set_uniform("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
//    this->lightingShader.set_uniform("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));

    auto directional_light = DirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f), ambient_colour, diffuse_colour, glm::vec3(1.0f, 1.0f, 1.0f));
    this->lightingShader.set_uniform("directional_light", directional_light);

    auto attenuation = Attenuation(1.0f, 0.09f, 0.032f);

    glm::vec3 point_light_positions[] = {
            glm::vec3( 0.7f,  0.2f,  2.0f),
            glm::vec3( 2.3f, -3.3f, -4.0f),
            glm::vec3(-4.0f,  2.0f, -12.0f),
            glm::vec3( 0.0f,  0.0f, -3.0f)
    };

    for (int i = 0; i < 4; i++) {
        auto point_light = PointLight(point_light_positions[i], ambient_colour, diffuse_colour, specular, attenuation);
        this->lightingShader.set_uniform("point_lights[" + std::to_string(i) + "]", point_light);
    }
//    auto point_light = PointLight(light_position, ambient_colour, diffuse_colour, specular, attenuation);
//    this->lightingShader.set_uniform("light", point_light);

    auto spot_light = SpotLight(camera->get_position(), camera->get_front(), glm::radians(12.5f), glm::radians(17.5f), ambient_colour, diffuse_colour, specular, attenuation);
    this->lightingShader.set_uniform("spot_light", spot_light);

    // View/Projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera->get_zoom()), 800.0f/600.0f, 0.1f, 100.0f);
    glm::mat4 view = camera->get_view_matrix();

    this->lightingShader.set_uniform("projection", projection);
    this->lightingShader.set_uniform("view", view);

    // World transformation.
    glm::mat4 model = glm::mat4(1.0f);
    this->lightingShader.set_uniform("model", model);
//
//    // Render the cube
//    glBindVertexArray(this->cubeVAO);
//    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Bind diffuse map.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuse_texture.ID());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specular_texture.ID());

    glBindVertexArray(this->cubeVAO);
    auto i = 0;
    for (auto position : positions) {
        glm::mat4 cmodel = glm::mat4(1.0f);
        cmodel = glm::translate(cmodel, position);
        float angle = 20.0f * i;
        i++;
        cmodel = glm::rotate(cmodel, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        this->lightingShader.set_uniform("model", cmodel);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // Draw the lamp object.
    this->lightCubeShader.use();
    this->lightCubeShader.set_uniform("projection", projection);
    this->lightCubeShader.set_uniform("view", view);

    model = glm::mat4(1.0f);
    model = glm::translate(model, light_position);
    model = glm::scale(model, glm::vec3(0.2f));
    this->lightCubeShader.set_uniform("model", model);

    this->lightCubeShader.set_uniform("light_colour", light_colour);

    glBindVertexArray(this->lightVAO);
    for (auto i = 0 ; i < 4; i++) {
        glm::mat4 cmodel = glm::mat4(1.0f);
        cmodel = glm::translate(model, point_light_positions[i]);
        this->lightCubeShader.set_uniform("model", cmodel);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
//    glDrawArrays(GL_TRIANGLES, 0, 36);
}
