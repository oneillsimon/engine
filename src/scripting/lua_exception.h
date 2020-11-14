//
// Created by simon on 13/11/2020.
//

#ifndef ENGINE_LUA_EXCEPTION_H
#define ENGINE_LUA_EXCEPTION_H

#include <exception>
#include <string>

#include "lua.h"

class lua_exception : public std::exception {
private:
    std::string message;
public:
    explicit lua_exception(lua_State* L);
    const char* what() const noexcept override;
};

#endif //ENGINE_LUA_EXCEPTION_H
