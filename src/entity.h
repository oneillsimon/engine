//
// Created by simon on 06/12/2020.
//

#ifndef ENGINE_ENTITY_H
#define ENGINE_ENTITY_H

#include <vector>

#include "component.h"

class Entity {
private:
    std::vector<Entity*> children;
    std::vector<Component*> components;

public:
    Entity();
    ~Entity();

    virtual void initialise();
    virtual void update(float delta);
    virtual void render(float delta);

    void add_child(Entity* entity);
    void add_component(Component* component);
};


#endif //ENGINE_ENTITY_H
