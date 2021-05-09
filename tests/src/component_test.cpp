//
// Created by simon on 08/04/2021.
//

#include <gtest/gtest.h>

#include <component.h>
#include <rendering/window.h>

class TestComponent : Component {
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

    void render(double delta) const override {
        Component::render(delta);
        this->is_rendered = true;
    }
};

TEST(component_test, initialises) {
    auto window = new Window("", 0, 0);
    auto component = TestComponent();

    ASSERT_FALSE(component.is_initialised);
    component.initialise(*window->get_input_processor());
    ASSERT_TRUE(component.is_initialised);
}

TEST(component_test, updates) {
    auto window = new Window("", 0, 0);
    auto component = TestComponent();

    ASSERT_FALSE(component.is_updated);
    component.update(0, *window->get_input_processor());
    ASSERT_TRUE(component.is_updated);
}

TEST(component_test, renders) {
    auto window = new Window("", 0, 0);
    auto component = TestComponent();

    ASSERT_FALSE(component.is_rendered);
    component.render(0);
    ASSERT_TRUE(component.is_rendered);
}
