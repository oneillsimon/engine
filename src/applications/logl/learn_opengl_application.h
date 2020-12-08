//
// Created by simon on 14/11/2020.
//

#ifndef ENGINE_LEARN_OPENGL_APPLICATION_H
#define ENGINE_LEARN_OPENGL_APPLICATION_H

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#include "../../application.h"
#include "input_processor.h"
#include "../../rendering/shader.h"
#include "../../rendering/shader_program.h"

class LearnOpenGlApp : public Application {
public:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    unsigned int textures[2];
    ShaderProgram shader_program;
    glm::mat4 transform;

    explicit LearnOpenGlApp();

    void initialise(const InputProcessor& input) override;
    void update(const double& delta, const InputProcessor& input) override;
    void render(const double& delta) override;
};

#endif //ENGINE_LEARN_OPENGL_APPLICATION_H
