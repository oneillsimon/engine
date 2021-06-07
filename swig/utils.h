//
// Created by simon on 21/05/2021.
//

#ifndef ENGINE_SWIG_UTILS_H
#define ENGINE_SWIG_UTILS_H

#include <string>
#include <typeinfo>

#include "glfw_input_processor.h"

std::string demangle(const char* name);

template<class T>
std::string type(const T& t) {
    return demangle(typeid(t).name());
}


#endif //ENGINE_SWIG_UTILS_H
