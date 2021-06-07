//
// Created by simon on 10/05/2021.
//

#ifndef ENGINE_LUA_APPLICATION_H
#define ENGINE_LUA_APPLICATION_H

#include <functional>
#include <utility>

#include <scripting/lua.h>

#include "application.h"
#include "rendering/window.h"

class LuaApplication : public Application {
public:
    using InitialiseCallback = std::function<void(InputProcessor&)>;
    using UpdateCallback = std::function<void(const double&, InputProcessor&)>;
    using RenderCallback = std::function<void(const double&)>;
    using StopCallback = std::function<void()>;

    LuaApplication(Entity entity, std::tuple<LuaApplication::InitialiseCallback, LuaApplication::UpdateCallback, LuaApplication::RenderCallback>& application);

    InitialiseCallback initialise_callback;
    UpdateCallback update_callback;
    RenderCallback render_callback;
    StopCallback stop_callback;

    void on_initialise(const InitialiseCallback& callback);
    void on_update(const UpdateCallback& callback);
    void on_render(const RenderCallback& callback);
    void on_stop(const StopCallback& callback);

    void initialise(InputProcessor& input) override;
    void update(const double& delta, InputProcessor& input) override;
    void render(const double& delta) override;
    void stop() override;
};

#endif //ENGINE_LUA_APPLICATION_H
