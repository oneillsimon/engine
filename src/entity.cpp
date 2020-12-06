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

void Entity::update(float delta) {
    for (auto* component : this->components) {
        component->update(delta);
    }
}

void Entity::render(float delta) {
    for (auto* component : this->components) {
        component->render(delta);
    }
}

void Entity::add_child(Entity* entity) {
    this->children.push_back(entity);
}

void Entity::add_component(Component* component) {
    this->components.push_back(component);
}
