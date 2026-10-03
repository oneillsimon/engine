//
// Created by simon on 21/11/2020.
//

#include <gtest/gtest.h>

#include <engine.h>

class EngineTestTestApplication : public Application {
public:
    int update_counter = 0;
    int stop_counter = 0;
    double last_update_delta = 0;

    EngineTestTestApplication() : Application() {}

    void update(const double& delta, InputProcessor& input) override {
        Application::update(delta, input);
        this->last_update_delta = delta;
        this->update_counter++;
    }

    void render(const double& delta) override {
        Application::render(delta);
    }

    void stop() override {
        Application::stop();
        this->stop_counter++;
    }
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

class TestWindowClosesAfterNFrames: public TestWindow {
public:
    int close_after_frames;
    int counter;
    TestWindowClosesAfterNFrames(int closes_after_n_frames) : TestWindow(std::string(), 0, 0) {
        this->close_after_frames = closes_after_n_frames;
        this->counter = 0;
    }

    void update() override {
        this->counter++;
        if (this->counter >= this->close_after_frames) {
            this->request_close();
        }
    }
};

TEST(engine_test, frame_rate) {
    auto application = new EngineTestTestApplication();
    float frame_rate = 120.0f;
    auto window = std::unique_ptr<TestWindow>(new TestWindowClosesAfterNFrames(1));

    auto e = Engine(application, std::move(window), frame_rate);
    e.start();

    EXPECT_EQ(application->last_update_delta, 1.0 / frame_rate);
    EXPECT_GT(application->update_counter, 0);
    ASSERT_FALSE(e.is_running());
}

TEST(engine_test, window_close_stops_engine) {
    auto close_after_n_window_updates = 2;
    auto application = new EngineTestTestApplication();
    auto window = std::make_unique<TestWindowClosesAfterNFrames>(close_after_n_window_updates);
    auto window_raw_ptr = window.get();
    auto e = Engine(application, std::move(window), 60.0f);

    e.start();

    EXPECT_FALSE(e.is_running());
    EXPECT_EQ(window_raw_ptr->counter, close_after_n_window_updates);
    EXPECT_GE(application->update_counter, close_after_n_window_updates);
    EXPECT_EQ(application->stop_counter, 1);
}
