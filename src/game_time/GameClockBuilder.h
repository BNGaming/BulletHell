#pragma once

#include <chrono>

#include "GameClock.h"
#include "GameTime.h"

namespace game_time {

class GameClockBuilder {
    std::chrono::duration<double> m_start_game_time;
    std::chrono::time_point<std::chrono::high_resolution_clock>
            m_start_wall_time;
    uint64_t m_start_frame;
    double m_clock_multiplier;

public:
    GameClockBuilder() : m_start_game_time(std::chrono::duration<double>{0.0}),
            m_start_wall_time(std::chrono::high_resolution_clock::now()),
            m_start_frame(0), m_clock_multiplier(1.0) {}

    GameClockBuilder start_game_time(
            std::chrono::duration<double> start_game_time) {
        this->m_start_game_time = start_game_time;
        return *this;
    }

    GameClockBuilder start_wall_time(
            std::chrono::time_point<std::chrono::high_resolution_clock>
                    start_wall_time) {
        this->m_start_wall_time = start_wall_time;
        return *this;
    }

    GameClockBuilder start_frame(uint64_t start_frame) {
        this->m_start_frame = start_frame;
        return *this;
    }

    GameClockBuilder clock_multiplier(double clock_multiplier) {
        this->m_clock_multiplier = clock_multiplier;
        return *this;
    }

	GameClock build() const;
};

} // namespace game_time
