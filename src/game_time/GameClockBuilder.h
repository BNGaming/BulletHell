#pragma once

#include <chrono>

#include "GameClock.h"
#include "GameTime.h"

namespace game_time {

class GameClockBuilder {
    std::chrono::duration<double> start_game_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_wall_time;
    uint64_t start_frame;
    double clock_multiplier;

public:
    GameClockBuilder() {
        this->start_game_time = std::chrono::duration<double>{0.0};
        this->start_wall_time = std::chrono::high_resolution_clock::now();
        this->start_frame = 0;
        this->clock_multiplier = 1.0;
    }

    GameClockBuilder start_game_time(
            std::chrono::duration<double> start_game_time) {
        this->start_game_time = start_game_time;
        return *this;
    }

    GameClockBuilder start_wall_time(
            std::chrono::time_point<std::chrono::high_resolution_clock>
                    start_wall_time) {
        this->start_wall_time = start_wall_time;
        return *this;
    }

    GameClockBuilder start_frame(uint64_t start_frame) {
        this->start_frame = start_frame;
        return *this;
    }

    GameClockBuilder clock_multiplier(double clock_multiplier) {
        this->clock_multiplier = clock_multiplier;
        return *this;
    }

    GameClock build() const {
        auto now = std::chrono::high_resolution_clock::now();
        GameTime game_time = GameTime(this->start_wall_time,
                std::chrono::duration<double>{0.0},
                this->start_game_time,
                std::chrono::duration<double>{0.0},
                std::chrono::duration<double>{0.0},
                this->start_frame);

        return GameClock(game_time,
                this->start_wall_time,
                this->start_game_time,
                this->start_frame,
                this->clock_multiplier);
    }
};

} // namespace game_time
