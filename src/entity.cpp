//
// Created by simon on 06/12/2020.
//

#include "entity.h"

Entity::Entity() = default;

Entity::~Entity() = default;

void Entity::initialise() {
    for (auto* component : this->components) {
        component->initialise();
    }
}

void Entity::update(double delta, const InputProcessor& input) {
    for (auto* component : this->components) {
        component->update(delta, input);
    }
}

void Entity::render(double delta) {
    for (auto* component : this->components) {
        component->render(delta);
    }
}

void Entity::add_child(Entity* entity) {
    if (!entity) {
        return;
    }

    this->children.push_back(entity);
    int b = 0;
}

void Entity::add_component(Component* component) {
    if (!component) {
        return;
    }

    this->components.push_back(component);
    int b = 0;
}
