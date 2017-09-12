#pragma once

#include <chrono>
#include <functional>
#include <thread>

#include "FrameCounter.h"
#include "GameTime.h"
#include "TimeStep.h"

namespace game_time {

class GameClock {
    GameTime m_last_frame_time;
    std::chrono::time_point<std::chrono::high_resolution_clock>
            m_start_wall_time;
    std::chrono::duration<double> m_total_game_time;
    uint64_t m_current_frame;
    double m_clock_multiplier;

public:
    GameClock()
        : m_last_frame_time(std::chrono::high_resolution_clock::now(),
                  std::chrono::duration<double>::zero(),
                  std::chrono::duration<double>::zero(),
                  std::chrono::duration<double>::zero(),
                  std::chrono::duration<double>::zero(),
                  0),
          m_start_wall_time(std::chrono::high_resolution_clock::now()),
          m_total_game_time(std::chrono::duration<double>::zero()),
          m_current_frame(0), m_clock_multiplier(1.0) {}

    GameClock(GameTime last_frame_time,
            std::chrono::time_point<std::chrono::high_resolution_clock>
                    start_wall_time,
            std::chrono::duration<double> total_game_time,
            uint64_t current_frame,
            double clock_multiplier)
        : m_last_frame_time(last_frame_time),
          m_start_wall_time(start_wall_time),
          m_total_game_time(total_game_time), m_current_frame(current_frame),
          m_clock_multiplier(clock_multiplier) {}

    const GameTime& last_frame_time() const { return this->m_last_frame_time; }

    uint64_t current_frame_number() const { return this->m_current_frame; }

    std::chrono::time_point<std::chrono::high_resolution_clock>
    start_wall_time() const {
        return this->m_start_wall_time;
    }

    std::chrono::time_point<std::chrono::high_resolution_clock>
    frame_start_time() const {
        return this->last_frame_time().frame_start_time();
    }

    std::chrono::duration<double> total_wall_time() const {
        return this->last_frame_time().total_wall_time();
    }

    std::chrono::duration<double> frame_elapsed_time() const {
        return std::chrono::high_resolution_clock::now() -
                this->last_frame_time().frame_start_time();
    }

    double clock_multiplier() const { return this->m_clock_multiplier; }

    GameClock set_clock_multiplier(double clock_multiplier) {
        this->m_clock_multiplier = clock_multiplier;
        return *this;
    }

    GameTime tick_with_wall_time(const TimeStep& time_step,
            std::chrono::time_point<std::chrono::high_resolution_clock>
                    frame_start);

    GameTime tick(const TimeStep& time_step) {
        auto frame_start = std::chrono::high_resolution_clock::now();
        return this->tick_with_wall_time(time_step, frame_start);
    }

    void sleep_remaining_via(const framerate::FrameCount& counter,
            std::function<void(const std::chrono::duration<double>&)> f);

    void sleep_remaining(const framerate::FrameCount& counter) {
        this->sleep_remaining_via(
                counter, [](auto& c) { std::this_thread::sleep_for(c); });
    }
};
} // namespace game_time
