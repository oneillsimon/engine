//
// Created by simon on 11/12/2020.
//

#ifndef ENGINE_LIGHTING_APP_H
#define ENGINE_LIGHTING_APP_H

#include "application.h"
#include "components/camera_component.h"
#include "rendering/shader_program.h"

class LightingApp : public Application {
public:
    unsigned int VBO;
    unsigned int lightVAO;
    unsigned int cubeVAO;
    ShaderProgram lightingShader;
    ShaderProgram lightCubeShader;

    LightingApp();

    void initialise(const InputProcessor& input) override;
    void update(const double& delta, const InputProcessor& input) override;
    void render(const double& delta) override;
};


#endif //ENGINE_LIGHTING_APP_H
