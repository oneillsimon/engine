%module engine
%{
#include <entity.h>

#include "utils.h"
%}

%include "component.i"
%include "lua_callbacks.i"

%typemap(out) Component* {
    if (!$1) {
        lua_pushnil(L);
    } else {
        SWIG_NewPointerObj(L, $1, SWIG_TypeQuery((type(*$1) + "*").c_str()), 0);
    }
    SWIG_arg++;
};

%include "../src/entity.h"

%extend Entity {
    void add_component(const std::string& name, LuaCallbacks& c) {
        $self->add_component(name, new LuaComponent(c));
    }

    Component* get_component(const std::string& name) {
        return $self->all_components()[name];
    }
};
