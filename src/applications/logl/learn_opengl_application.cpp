//
// Created by simon on 14/11/2020.
//

#include <algorithm>
#include <iostream>

#include <stb_image.h>

#include "learn_opengl_application.h"
#include "component.h"

class TestComponent : public Component {
public:
//    void update(double delta, InputProcessor* input) override {
//    }
};

LearnOpenGlApp::LearnOpenGlApp() : Application(), shader_program(ShaderProgram()) {
    auto tc = new TestComponent();
    root->add_component(tc);
}

// Camera
auto camera_pos = glm::vec3(0.0f, 0.0f, 3.0f);
auto camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
auto camera_up = glm::vec3(0.0f, 1.0f, 0.0f);

auto yaw = -90.0f;
auto pitch = 0.0f;
auto first_mouse = true;
auto last_x = 400;
auto last_y = 300;

auto fov = 45.0f;

void mouse_callback(void* window, double x, double y) {
    if (first_mouse) {
        last_x = x;
        last_y = y;
        first_mouse = false;
    }

    auto x_offset = x - last_x;
    auto y_offset = y - last_y;
    last_x = x;
    last_y = y;

    const float sensitivity = 0.1f;
    x_offset *= sensitivity;
    y_offset *= sensitivity;

    yaw += x_offset;
    pitch += y_offset;

    if (pitch > 89.0f) {
        pitch =  89.0f;
    }

    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    auto direction = glm::vec3(
            cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
            sin(glm::radians(pitch)),
            sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    );

    camera_front = glm::normalize(direction);
}

void scroll_callback(void* window, double x, double y) {
    fov -= (float)y;

    if (fov < 1.0f) {
        fov = 1.0f;
    }

    if (fov > 45.0f) {
        fov = 45.0f;
    }
}

void LearnOpenGlApp::initialise(const InputProcessor& input) {
    Application::initialise(input);

//    float vertices[] = {
//             // positions          // colors           // texture coords
//             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
//             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
//            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
//    };

    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };


    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
    };

    // Copy our vertices array in a buffer for OpenGL to use.
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Then set the vertex attributes pointers.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attributes
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);

    // Texture coord attribute.
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(VAO);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    this->shader_program.add_shader(Shader::vertex_shader("shaders/learnopengl_shaders/shader.vs.glsl"));
    this->shader_program.add_shader(Shader::fragment_shader("shaders/learnopengl_shaders/shader.fs.glsl"));
    this->shader_program.link();

    glGenTextures(1, &textures[0]);
    glBindTexture(GL_TEXTURE_2D, textures[0]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, number_channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("resources/textures/container.jpg", &width, &height, &number_channels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &textures[1]);
    glBindTexture(GL_TEXTURE_2D, textures[1]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width2, height2, number_channels2;
    unsigned char* data2 = stbi_load("resources/textures/awesomeface.png", &width2, &height2, &number_channels2, 0);
    if (data2) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data2);

    this->shader_program.use();
    this->shader_program.set_uniform("texture1", 0);
    this->shader_program.set_uniform("texture2", 1);

//    transform = glm::mat4(1.0f);
//    transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
//    transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5));

    auto model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    auto view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                       glm::vec3(0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 1.0f, 0.0f));

    auto projection = glm::perspective(glm::radians(fov), 800.0f/600.0f, 0.1f, 100.0f);

//    this->shader_program.set_uniform("transform", glm::value_ptr(transform));
    this->shader_program.set_uniform("model", model);
    this->shader_program.set_uniform("view", view);
    this->shader_program.set_uniform("projection", projection);

    glEnable(GL_DEPTH_TEST);

    // Camera stuff
    input.capture_input();
    input.set_cursor_position_callback(mouse_callback);
    input.set_scroll_callback(scroll_callback);
}

void LearnOpenGlApp::update(const double& delta, const InputProcessor& input) {
    Application::update(delta, input);

    if (input.get_key(GLFW_KEY_Q, GLFW_PRESS)) {
        this->stop();
    }

    float speed = 2.5f * delta;
    if (input.get_key(GLFW_KEY_W, GLFW_PRESS)) {
        camera_pos += speed * camera_front;
    }

    if (input.get_key(GLFW_KEY_S, GLFW_PRESS)) {
        camera_pos -= speed * camera_front;
    }

    if (input.get_key(GLFW_KEY_A, GLFW_PRESS)) {
        camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * speed;
    }

    if (input.get_key(GLFW_KEY_D, GLFW_PRESS)) {
        camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * speed;
    }

    auto projection = glm::perspective(glm::radians(fov), 800.0f/600.0f, 0.1f, 100.0f);
    this->shader_program.set_uniform("projection", projection);
}

void LearnOpenGlApp::render(const double& delta) {
    Application::render(delta);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->shader_program.use();
//    this->shader_program.set_uniform("x_offset", -0.8f);

    auto model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.6f, 1.0f, 0.2f));
    this->shader_program.set_uniform("model", model);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[1]);

    glBindVertexArray(VAO);

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

//    float radius = 10.0f;
//    float cam_x = sin(glfwGetTime()) * radius;
//    float cam_z = cos(glfwGetTime()) * radius;
//    auto view = glm::mat4(1.0f);
//    view = glm::lookAt(glm::vec3(cam_x, 0.0f, cam_z), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    auto view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
    this->shader_program.set_uniform("view", view);

    int i = 0;
    for (auto position : positions) {
        auto model = glm::translate(glm::mat4(1.0f), position);
        float angle = 20.0f * i;
        i = i + 1;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        this->shader_program.set_uniform("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
