//
// Created by simon on 03/06/2021.
//

#ifndef ENGINE_LUA_COMPONENT_H
#define ENGINE_LUA_COMPONENT_H

#include "component.h"
#include "input_processor.h"

class LuaComponent : public Component {
public:
    using InitialiseCallback = std::function<void(InputProcessor&)>;
    using UpdateCallback = std::function<void(const double&, InputProcessor&)>;
    using RenderCallback = std::function<void(const double&)>;

    LuaComponent(std::tuple<LuaComponent::InitialiseCallback, LuaComponent::UpdateCallback, LuaComponent::RenderCallback>& c);

    InitialiseCallback initialise_callback;
    UpdateCallback update_callback;
    RenderCallback render_callback;

    void on_initialise(const InitialiseCallback& callback);
    void on_update(const UpdateCallback& callback);
    void on_render(const RenderCallback& callback);

    void initialise(InputProcessor& input) override;
    void update(double delta, InputProcessor& input) override;
    void render(double delta) override;
};


#endif //ENGINE_LUA_COMPONENT_H
