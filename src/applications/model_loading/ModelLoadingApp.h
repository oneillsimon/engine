//
// Created by simon on 31/01/2021.
//

#ifndef ENGINE_MODELLOADINGAPP_H
#define ENGINE_MODELLOADINGAPP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "application.h"

#include "rendering/model.h"
#include "rendering/shader.h"
#include "rendering/shader_program.h"

class ModelLoadingApp : public Application {
private:
    ShaderProgram shader_program;
    Model our_model;
public:
    ModelLoadingApp();

    void initialise(const InputProcessor& input) override;
    void update(const double& delta, const InputProcessor& input) override;
    void render(const double& delta) override;
};


#endif //ENGINE_MODELLOADINGAPP_H
