//
// Created by simon on 13/11/2020.
//

#include "lua_exception.h"

lua_exception::lua_exception(lua_State* L) :
    message(lua_tostring(L, -1)) {
}

const char* lua_exception::what() const noexcept {
    return message.c_str();
}
