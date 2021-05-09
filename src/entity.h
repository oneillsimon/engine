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

    virtual void initialise(InputProcessor& input);
    virtual void update(double delta, InputProcessor& input);
    virtual void render(double delta);

    void add_child(const std::string& name, Entity* entity);
    void add_component(const std::string& name, Component* component);

    Entity* get_child(const std::string& name);

    template<class ComponentClass>
    ComponentClass* get_component(const std::string& name) {
        if (this->components.find(name) == this->components.end()) {
            return nullptr;
        }
        return static_cast<ComponentClass*>(this->components[name]);
    }

    std::map<const std::string, Entity*> all_children() const;
    std::map<const std::string, Component*> all_components() const;
};


#endif //ENGINE_ENTITY_H
