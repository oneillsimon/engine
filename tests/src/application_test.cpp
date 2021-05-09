//
// Created by simon on 08/04/2021.
//

#include <gtest/gtest.h>

#include <application.h>
#include <component.h>
#include <rendering/window.h>

class ApplicationTestTestApplication : public Application {
public:
    ApplicationTestTestApplication() : Application() {}
};

class TestWindow : public Window {
public:
    TestWindow(std::string title, const unsigned int& width, const unsigned int& height): Window(title, width, height) {}

    void update() {};
    void swap_buffers() {};

    void request_close() {
        this->close_requested = true;
    }
};

class TestComponent : public Component {
public:
    bool is_initialised = false;
    bool is_updated = false;
    mutable bool is_rendered = false;

    ~TestComponent() override = default;

    void initialise(InputProcessor& input) override {
        Component::initialise(input);
        this->is_initialised = true;
    }

    void update(double delta, InputProcessor& input) override {
        Component::update(0, input);
        this->is_updated = true;
    }

    void render(double delta) const override {
        Component::render(delta);
        this->is_rendered = true;
    }
};

TEST(application_test, initialises_components) {
    auto application = ApplicationTestTestApplication();
    application.root->add_component("test", new TestComponent());

    auto* test_component = application.root->get_component<TestComponent>("test");
    ASSERT_FALSE(test_component->is_initialised);

    auto window = TestWindow("", 0, 0);
    application.initialise(*window.get_input_processor());

    ASSERT_TRUE(test_component->is_initialised);
}

TEST(application_test, updates_components) {
    auto application = ApplicationTestTestApplication();
    application.root->add_component("test", new TestComponent());

    auto* test_component = application.root->get_component<TestComponent>("test");
    ASSERT_FALSE(test_component->is_updated);

    auto window = TestWindow("", 0, 0);
    application.initialise(*window.get_input_processor());
    application.update(0, *window.get_input_processor());

    ASSERT_TRUE(test_component->is_updated);
}

TEST(application_test, renders_components) {
    auto application = ApplicationTestTestApplication();
    application.root->add_component("test", new TestComponent());

    auto* test_component = application.root->get_component<TestComponent>("test");
    ASSERT_FALSE(test_component->is_rendered);

    auto window = TestWindow("", 0, 0);
    application.initialise(*window.get_input_processor());
    application.render(0);

    ASSERT_TRUE(test_component->is_rendered);
}