//
// Created by simon on 20/02/2021.
//

#ifndef ENGINE_DISCARDSHADINGAPP_H
#define ENGINE_DISCARDSHADINGAPP_H

#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "application.h"
#include "rendering/glsl_program.h"
#include "rendering/material/material.h"
#include "rendering/mesh/examples/teapot.h"

class DiscardShadingApp : public Application {
private:
    GLSLProgram program;
    Teapot teapot;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

public:
    std::map<std::string, Material> materials;
    std::map<std::string, Material>::iterator current_material;

    DiscardShadingApp();
    void initialise(const InputProcessor& input) override;
    void update(const double& delta, const InputProcessor& input) override;
    void render(const double& delta) override;
    void stop() override;
};


#endif //ENGINE_DISCARDSHADINGAPP_H
