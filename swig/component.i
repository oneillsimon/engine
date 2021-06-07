%module engine
%{
#include <component.h>
#include <scripting/lua.h>

#include "utils.h"
%};

%include "../src/component.h"

%luacode {
    Component = {}

    function Component:new(o)
        o = o or {}
        setmetatable(o, self)
        self.__index = self
        return o
    end

    function Component:initialise(input)
    end

    function Component:update(delta, input)
    end

    function Component:render(delta)
    end
};