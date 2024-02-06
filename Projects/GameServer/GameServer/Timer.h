#pragma once
#include <iostream>
#include <chrono>

#define TIMER() Timer::getInstance()

class Timer {
public:
    static Timer& getInstance() {
        static Timer instance;
        return instance;
    }

    void start() {
        if (!isRunning) {
            isRunning = true;
            previousTime = std::chrono::high_resolution_clock::now();
        }
    }

    void update() {
        if (isRunning) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> frameDuration = currentTime - previousTime;
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

    float getDeltaTime() const {
        return deltaTime;
    }

    float getAccumulatedTime() const {
        return accumulatedTime;
    }

    float getCurrentTime() {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime.time_since_epoch());
        return duration.count();
    }

private:
    bool isRunning = false;
    float accumulatedTime = 0.0;
    float deltaTime;
    std::chrono::high_resolution_clock::time_point previousTime;

    // �����ڿ� �Ҹ��ڴ� private���� �����Ͽ� �ܺο��� ��ü�� ���� �� �Ҹ��� ����
    Timer() = default;
    ~Timer() = default;

    // ���� �����ڿ� ���� �����ڵ� private���� �����Ͽ� ���縦 ����
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
};