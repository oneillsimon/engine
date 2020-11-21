//
// Created by simon on 14/11/2020.
//

#ifndef ENGINE_LEARN_OPENGL_APPLICATION_H
#define ENGINE_LEARN_OPENGL_APPLICATION_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "application.h"
#include "rendering/shader.h"
#include "rendering/shader_program.h"

class LearnOpenGlApp : public Application {
public:
    unsigned int VBO;
    unsigned int VAO;
    ShaderProgram shader_program;

    LearnOpenGlApp();

    void initialise() override;
    void render(const double& delta) override;
};

#endif //ENGINE_LEARN_OPENGL_APPLICATION_H
