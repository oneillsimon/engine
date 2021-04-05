//
// Created by simon on 06/12/2020.
//

#include "entity.h"

Entity::Entity() = default;

Entity::~Entity() = default;

void Entity::initialise(InputProcessor& input) {
    for (auto const& component : this->components) {
        component.second->initialise(input);
    }
}

void Entity::update(double delta, InputProcessor& input) {
    for (auto const& component : this->components) {
        component.second->update(delta, input);
    }
}

void Entity::render(double delta) {
    for (auto const& component : this->components) {
        component.second->render(delta);
    }
}

void Entity::add_child(const std::string& name, Entity* entity) {
    if (!entity) {
        return;
    }

    this->children.insert(std::make_pair(name, entity));
    int b = 0;
}

void Entity::add_component(const std::string& name, Component* component) {
    if (!component) {
        return;
    }

    this->components.insert(std::make_pair(name, component));
    int b = 0;
}

Entity* Entity::get_child(const std::string &name) {
    return this->children[name];
}
