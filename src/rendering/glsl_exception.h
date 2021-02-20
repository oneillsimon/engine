//
// Created by simon on 17/02/2021.
//

#ifndef ENGINE_GLSL_EXCEPTION_H
#define ENGINE_GLSL_EXCEPTION_H

#include <stdexcept>

class GLSLException : public std::runtime_error {
public:
    explicit GLSLException(const std::string& message);
};


#endif //ENGINE_GLSL_EXCEPTION_H
