//
// Created by simon on 21/11/2020.
//

#include <chrono>
#include <thread>

#include <gtest/gtest.h>

#include <engine.h>

class TestApplication : public Application {
public:
    int counter = 0;

    TestApplication() : Application() {}

    void update(const double& delta, InputProcessor& input) override {
        this->counter++;
    }

    void render(const double& delta) override {}
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

void run_engine(Engine* engine) {
    engine->start();
}

TEST(engine_test, frame_rate) {
    auto application = new TestApplication();
    auto window = new TestWindow(std::string(), 0, 0);

    float frame_rate = 120.0f;
    auto e = Engine(application, window, frame_rate);

    // Start the engine in a new thread to avoid blocking this one.
    std::thread engine_runner(run_engine, &e);

    // Wait for 1 second.
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Stop the engine and join the runner thread.
    e.stop();
    engine_runner.join();

    // App updates frame_rate per second, so after 1 second of running we expect counter
    // to be the same.
    EXPECT_EQ(frame_rate, application->counter);
}

TEST(engine_test, window_close_stops_engine) {
    auto application = new TestApplication();
    auto window = new TestWindow(std::string(), 0, 0);
    auto e = Engine(application, window, 60.0f);

    // Start the engine in a new thread to avoid blocking this one.
    std::thread engine_runner(run_engine, &e);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    EXPECT_EQ(e.is_running(), true);

    // Close the window and check that the engine stops.
    window->request_close();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    engine_runner.join();
    EXPECT_EQ(e.is_running(), false);
}