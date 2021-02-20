//
// Created by simon on 14/02/2021.
//

#ifndef ENGINE_CB_CHAPTER1_APP_H
#define ENGINE_CB_CHAPTER1_APP_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "application.h"
#include "input_processor.h"

class CB_Chapter1_app : public Application {
private:
    GLuint program_handle;
    GLuint vao_handle;
public:
    void initialise(const InputProcessor& input) override;
    void update(const double& delta, const InputProcessor& input) override;
    void render(const double& delta) override;
};


#endif //ENGINE_CB_CHAPTER1_APP_H
