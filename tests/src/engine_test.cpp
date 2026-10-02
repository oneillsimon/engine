//
// Created by simon on 21/11/2020.
//

#include <chrono>
#include <thread>

#include <gtest/gtest.h>

#include <engine.h>

class EngineTestTestApplication : public Application {
public:
    int update_counter = 0;
    int stop_counter = 0;

    EngineTestTestApplication() : Application() {}

    void update(const double& delta, InputProcessor& input) override {
        Application::update(delta, input);
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
private:
    int close_after_frames;
    int counter;
public:
    TestWindowClosesAfterNFrames(int closes_after_n_frames) : TestWindow(std::string(), 0, 0) {
        this->close_after_frames = closes_after_n_frames;
        this->counter = 0;
    }

    void update() {
        this->counter++;
        if (this->counter >= this->close_after_frames) {
            this->request_close();
        }
    }
};

void run_engine(Engine* engine) {
    engine->start();
}

TEST(engine_test, frame_rate) {
    auto application = new EngineTestTestApplication();
    auto window = std::unique_ptr<TestWindow>(new TestWindow(std::string(), 0, 0));

    float frame_rate = 120.0f;
    auto e = Engine(application, std::move(window), frame_rate);

    // Start the engine in a new thread to avoid blocking this one.
    std::thread engine_runner(run_engine, &e);

    // Wait for 1 second.
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Stop the engine and join the runner thread.
    e.stop();
    engine_runner.join();

    // App updates frame_rate per second, so after 1 second of running we expect counter
    // to be the same.
    EXPECT_EQ(frame_rate, application->update_counter);
}

TEST(engine_test, window_close_stops_engine) {
    auto application = new EngineTestTestApplication();
    auto window = std::unique_ptr<TestWindowClosesAfterNFrames>(new TestWindowClosesAfterNFrames(60));
    auto e = Engine(application, std::move(window), 60.0f);

    // Start the engine in a new thread to avoid blocking this one.
    std::thread engine_runner(run_engine, &e);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    EXPECT_EQ(e.is_running(), true);

    // Close the window and check that the engine stops.
    std::this_thread::sleep_for(std::chrono::seconds(1));
    engine_runner.join();
    EXPECT_EQ(e.is_running(), false);
    EXPECT_EQ(application->stop_counter, 1);
}
