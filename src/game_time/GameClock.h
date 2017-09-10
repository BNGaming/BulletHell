#pragma once

#include <chrono>
#include <functional>
#include <thread>

#include "FrameCounter.h"
#include "GameTime.h"
#include "TimeStep.h"

namespace game_time {

class GameClock {
    GameTime last_frame_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_wall_time;
    std::chrono::duration<double> total_game_time;
    uint64_t current_frame;
    double clock_multiplier;

public:
    GameClock() {
        auto now = std::chrono::high_resolution_clock::now();
        this->last_frame_time = GameTime(now,
                std::chrono::duration<double>::zero(),
                std::chrono::duration<double>::zero(),
                std::chrono::duration<double>::zero(),
                std::chrono::duration<double>::zero(),
                0);
        this->start_wall_time = now;
        this->total_game_time = std::chrono::duration<double>::zero();
        this->current_frame = 0;
        this->clock_multiplier = 1.0;
    }

    GameClock(GameTime last_frame_time,
            std::chrono::time_point<std::chrono::high_resolution_clock>
                    start_wall_time,
            std::chrono::duration<double> total_game_time,
            uint64_t current_frame,
            double clock_multiplier) {
        this->last_frame_time = last_frame_time;
        this->start_wall_time = start_wall_time;
        this->total_game_time = total_game_time;
        this->current_frame = current_frame;
        this->clock_multiplier = clock_multiplier;
    }

    const GameTime& last_frame_time() const { return this->last_frame_time; }

    uint64_t current_frame_number() const { return this->current_frame; }

    std::chrono::time_point<std::chrono::high_resolution_clock>
    start_wall_time() const {
        return this->start_wall_time;
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

    const GameTime& last_frame_time() const { return this->last_frame_time; }

    double clock_multiplier() const { return this->clock_multiplier; }

    GameClock set_clock_multiplier(double clock_multiplier) {
        this->clock_multiplier = clock_multiplier;
        return *this;
    }

    /// TODO Tick Functions
    GameTime tick_with_wall_time(const TimeStep& time_step,
            std::chrono::time_point<std::chrono::high_resolution_clock>
                    frame_start) {
        this->current_frame += 1;
        std::chrono::duration<double> elapsed_wall_time =
                frame_start - this->frame_start_time();
        std::chrono::duration<double> elapsed_game_time =
                time_step.time_step(&elapsed_wall_time) *
                this->clock_multiplier;
        std::chrono::duration<double> total_game_time =
                this->total_game_time + elapsed_game_time;

        this->total_game_time = total_game_time;

        GameTime time = GameTime(frame_start,
                frame_start - this->start_wall_time,
                total_game_time,
                elapsed_game_time,
                elapsed_wall_time,
                this->current_frame);

        this->last_frame_time = time;
        return time;
    }

    GameTime tick(const TimeStep& time_step) {
        auto frame_start = std::chrono::high_resolution_clock::now();
        return this->tick_with_wall_time(time_step, frame_start);
    }

    template <class T>
    void sleep_remaining_via(const FrameCount& counter,
            std::function<void(const std::chrono::duration<T>&)> f) {
        std::chrono::duration<double> remaining_time =
                counter.target_time_per_frame() -
                this->last_frame_time().elapsed_time_since_start_of_frame();
        if(remaining_time > 0.0) {
            f(remaining_time);
        }
    }

    void sleep_remaining(const FrameCount& counter) {
        this->sleep_remaining_via(counter, std::this_thread::sleep_for);
    }
};
} // namespace game_time