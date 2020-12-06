//
// Created by simon on 06/12/2020.
//

#ifndef ENGINE_GLFW_INPUT_PROCESSOR_H
#define ENGINE_GLFW_INPUT_PROCESSOR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "input_processor.h"

class GlfwInputProcessor : public InputProcessor {
public:
    GlfwInputProcessor(void* window);
    virtual bool get_key(int key, int state) const override;
};


#endif //ENGINE_GLFW_INPUT_PROCESSOR_H
