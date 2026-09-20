%module engine
%{
#include <engine.h>
%}

%include "lua_application.i"

%include "../src/engine.h"

%inline %{
    class LuaEngine : public Engine {
        public:
            LuaEngine(LuaApplication application, Window* window, double frame_rate) :
                Engine(new LuaApplication(application), window, frame_rate) {
            }
    };
%};

%luacode {
    Engine = {};

    function Engine:new(application, window, frame_rate)
        a = engine.LuaApplication(application.root, application)
        application.root = a.root
        return engine.LuaEngine(a, window, frame_rate)
    end
};
