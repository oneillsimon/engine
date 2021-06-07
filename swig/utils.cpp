//
// Created by simon on 21/05/2021.
//

#include "utils.h"

#ifdef __GNUG__
#include <cstdlib>
#include <cxxabi.h>
#include <memory>

std::string demangle(const char* name) {
    int status;
    std::unique_ptr<char, void(*)(void*)> result {
        abi::__cxa_demangle(name, nullptr, nullptr, &status),
        std::free
    };
    return status == 0 ? result.get() : name;
}

#else

std::string demangle(const char* name) {
    return name;
}

#endif