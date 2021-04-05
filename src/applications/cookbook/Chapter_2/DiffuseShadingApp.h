//
// Created by simon on 20/02/2021.
//

#ifndef ENGINE_DIFFUSESHADINGAPP_H
#define ENGINE_DIFFUSESHADINGAPP_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "application.h"
#include "rendering/glsl_program.h"
#include "rendering/mesh/examples/torus.h"

class DiffuseShadingApp : public Application {
private:
    GLSLProgram program;
    Torus torus;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    float reflectivity = 1.0f;
    float intensity = 1.0f;
public:
    DiffuseShadingApp();
    void initialise(InputProcessor& input) override;
    void update(const double& delta, InputProcessor& input) override;
    void render(const double& delta) override;
    void stop() override;
};


#endif //ENGINE_DIFFUSESHADINGAPP_H
