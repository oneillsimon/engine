//
// Created by simon on 08/04/2021.
//

#include <gtest/gtest.h>

#include <component.h>
#include <entity.h>
#include <rendering/window.h>

class TestComponent : public Component {
public:
    bool is_initialised = false;
    bool is_updated = false;
    mutable bool is_rendered = false;

    void initialise(InputProcessor& input) override {
        Component::initialise(input);
        this->is_initialised = true;
    }

    void update(double delta, InputProcessor& input) override {
        Component::update(delta, input);
        this->is_updated = true;
    }

    void render(double delta) override {
        Component::render(delta);
        this->is_rendered = true;
    }
};

TEST(entity_test, components_are_initialised) {
    auto* window = new Window("", 0, 0);
    auto entity = Entity();
    entity.add_component("test", new TestComponent());
    auto* component = entity.get_component<TestComponent>("test");

    ASSERT_FALSE(component->is_initialised);
    entity.initialise(*window->get_input_processor());
    ASSERT_TRUE(component->is_initialised);
}

TEST(entity_test, child_components_are_initialised) {
    auto* window = new Window("", 0, 0);
    auto* entity = new Entity();
    entity->add_component("test", new TestComponent());
    auto* component = entity->get_component<TestComponent>("test");

    auto* root = new Entity();
    root->add_child("child", entity);

    ASSERT_FALSE(component->is_initialised);
    root->initialise(*window->get_input_processor());
    ASSERT_TRUE(component->is_initialised);
}

TEST(entity_test, components_are_updated) {
    auto* window = new Window("", 0, 0);
    auto entity = Entity();
    entity.add_component("test", new TestComponent());
    auto* component = entity.get_component<TestComponent>("test");

    ASSERT_FALSE(component->is_updated);
    entity.update(0, *window->get_input_processor());
    ASSERT_TRUE(component->is_updated);
}

TEST(entity_test, child_components_are_updated) {
    auto* window = new Window("", 0, 0);
    auto* entity = new Entity();
    entity->add_component("test", new TestComponent());
    auto* component = entity->get_component<TestComponent>("test");

    auto* root = new Entity();
    root->add_child("child", entity);

    ASSERT_FALSE(component->is_updated);
    root->update(0, *window->get_input_processor());
    ASSERT_TRUE(component->is_updated);
}

TEST(entity_test, components_are_rendered) {
    auto* window = new Window("", 0, 0);
    auto entity = Entity();
    entity.add_component("test", new TestComponent());
    auto* component = entity.get_component<TestComponent>("test");

    ASSERT_FALSE(component->is_rendered);
    entity.render(0);
    ASSERT_TRUE(component->is_rendered);
}

TEST(entity_test, child_components_are_rendered) {
    auto* entity = new Entity();
    entity->add_component("test", new TestComponent());
    auto* component = entity->get_component<TestComponent>("test");

    auto* root = new Entity();
    root->add_child("child", entity);

    ASSERT_FALSE(component->is_rendered);
    root->render(0);
    ASSERT_TRUE(component->is_rendered);
}

TEST(entity_test, add_child) {
    auto entity = new Entity();
    auto a_child = new Entity();
    auto b_child = new Entity();
    auto c_child = new Entity();

    ASSERT_EQ(entity->get_child("a"), nullptr);
    ASSERT_EQ(entity->get_child("b"), nullptr);
    ASSERT_EQ(entity->get_child("c"), nullptr);

    ASSERT_EQ(entity->all_children().size(), 0);

    entity->add_child("a", a_child);
    entity->add_child("b", b_child);
    entity->add_child("c", c_child);

    ASSERT_EQ(entity->get_child("a"), a_child);
    ASSERT_EQ(entity->get_child("b"), b_child);
    ASSERT_EQ(entity->get_child("c"), c_child);

    ASSERT_EQ(entity->all_children().size(), 3);
}

TEST(entity_test, add_null_child) {
    auto entity = new Entity();

    ASSERT_EQ(entity->all_children().size(), 0);

    entity->add_child("child", nullptr);

    ASSERT_EQ(entity->get_child("child"), nullptr);
    ASSERT_EQ(entity->all_children().size(), 0);
}

TEST(entity_test, add_component) {
    auto entity = new Entity();
    auto a_component = new TestComponent();
    auto b_component = new TestComponent();
    auto c_component = new TestComponent();

    ASSERT_EQ(entity->get_component<TestComponent>("a"), nullptr);
    ASSERT_EQ(entity->get_component<TestComponent>("b"), nullptr);
    ASSERT_EQ(entity->get_component<TestComponent>("c"), nullptr);

    ASSERT_EQ(entity->all_components().size(), 0);

    entity->add_component("a", a_component);
    entity->add_component("b", b_component);
    entity->add_component("c", c_component);

    ASSERT_EQ(entity->get_component<TestComponent>("a"), a_component);
    ASSERT_EQ(entity->get_component<TestComponent>("b"), b_component);
    ASSERT_EQ(entity->get_component<TestComponent>("c"), c_component);

    ASSERT_EQ(entity->all_components().size(), 3);
}

TEST(entity_test, add_null_component) {
    auto entity = new Entity();
    TestComponent* component = nullptr;

    ASSERT_EQ(entity->all_components().size(), 0);

    entity->add_component("component", component);

    ASSERT_EQ(entity->get_component<TestComponent>("component"), nullptr);
    ASSERT_EQ(entity->all_components().size(), 0);
}