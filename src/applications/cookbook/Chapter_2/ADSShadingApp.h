//
// Created by simon on 20/02/2021.
//

#ifndef ENGINE_ADSSHADINGAPP_H
#define ENGINE_ADSSHADINGAPP_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "application.h"
#include "rendering/glsl_program.h"
#include "rendering/mesh/examples/torus.h"

class ADSShadingApp : public Application {
private:
    GLSLProgram program;
    Torus torus;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
public:
    ADSShadingApp();
    void initialise(const InputProcessor& input) override;
    void update(const double& delta, const InputProcessor& input) override;
    void render(const double& delta) override;
    void stop() override;
};


#endif //ENGINE_ADSSHADINGAPP_H
