#include <iostream>
#include <chrono>
#include <thread>

class Timer {
public:
    void start() {
        if (!isRunning) {
            isRunning = true;
            previousTime = std::chrono::high_resolution_clock::now();
        }
    }

    void update() {
        if (isRunning) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> frameDuration = currentTime - previousTime;
            deltaTime = frameDuration.count();
            accumulatedTime += deltaTime;
            previousTime = currentTime;
        }
    }

    void stop() {
        if (isRunning) {
            isRunning = false;
            update(); // Update one last time before stopping
        }
    }

    double getDeltaTime() const {
        return deltaTime;
    }

    double getAccumulatedTime() const {
        return accumulatedTime;
    }

private:
    bool isRunning = false;
    double accumulatedTime = 0.0f;
    double deltaTime;
    std::chrono::high_resolution_clock::time_point previousTime;
};