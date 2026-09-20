//
// Created by simon on 21/11/2020.
//

#include <chrono>
#include <thread>

#include <gtest/gtest.h>

#include <engine.h>
#include <input_processor.h>

class EngineTestTestApplication : public Application {
public:
    int counter = 0;

    EngineTestTestApplication() : Application() {}

    void update(const double& delta, InputProcessor& input) override {
        this->counter++;
    }

    void render(const double& delta) override {}
};

class TestInputProcessor : public InputProcessor {
public:
    explicit TestInputProcessor() : InputProcessor(nullptr) {}

    void capture_input() const override {}
    void release_input() const override {}
    void set_input_mode(int mode, int value) const override {}
    int get_input_mode(int mode) const override { return 0; }
    void begin_frame() override {}
    bool is_key_down(int key) override { return false; }
    bool is_key_pressed(int key) override { return false; }
    bool is_key_released(int key) override { return false; }
    bool is_key_repeating(int key) override { return false; }
    bool is_scrolling(const ScrollDirection& direction) override { return false; }
};

class TestWindow : public Window {
private:
    TestInputProcessor test_input_processor;
public:
    TestWindow(std::string title, const unsigned int& width, const unsigned int& height)
        : Window(std::move(title), width, height), test_input_processor() {
        this->input_processor = &this->test_input_processor;
    }

    void update() override {};
    void swap_buffers() override {};

    void request_close() {
        this->close_requested = true;
    }
};

void run_engine(Engine* engine) {
    engine->start();
}

TEST(engine_test, frame_rate) {
    auto application = new EngineTestTestApplication();
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
    auto application = new EngineTestTestApplication();
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