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

    for (auto const& child : this->children) {
        child.second->initialise(input);
    }
}

void Entity::update(double delta, InputProcessor& input) {
    for (auto const& component : this->components) {
        component.second->update(delta, input);
    }

    for (auto const& child : this->children) {
        child.second->update(delta, input);
    }
}

void Entity::render(double delta) {
    for (auto const& component : this->components) {
        component.second->render(delta);
    }

    for (auto const& child : this->children) {
        child.second->render(delta);
    }
}

void Entity::add_child(const std::string& name, Entity* entity) {
    if (entity == nullptr) {
        return;
    }

    this->children.insert(std::make_pair(name, entity));
}

void Entity::add_component(const std::string& name, Component* component) {
    if (component == nullptr) {
        return;
    }
    this->components[name] = component;
}

Entity* Entity::get_child(const std::string &name) {
    if (this->children.find(name) == this->children.end()) {
        return nullptr;
    }

    return this->children[name];
}

std::map<const std::string, Entity*> Entity::all_children() const {
    return this->children;
}

std::map<const std::string, Component*> Entity::all_components() const {
    return this->components;
}
