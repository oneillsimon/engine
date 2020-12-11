//
// Created by simon on 06/12/2020.
//

#ifndef ENGINE_ENTITY_H
#define ENGINE_ENTITY_H

#include <map>
#include <string>

#include "component.h"
#include "input_processor.h"

class Entity {
private:
    std::map<const std::string, Entity*> children;
    std::map<const std::string, Component*> components;

public:
    Entity();
    ~Entity();

    virtual void initialise(const InputProcessor& input);
    virtual void update(double delta, const InputProcessor& input);
    virtual void render(double delta);

    void add_child(const std::string& name, Entity* entity);
    void add_component(const std::string& name, Component* component);

    Entity* get_child(const std::string& name);

    template<class ComponentClass>
    ComponentClass* get_component(const std::string& name) {
        return static_cast<ComponentClass*>(this->components[name]);
    }
};


#endif //ENGINE_ENTITY_H
