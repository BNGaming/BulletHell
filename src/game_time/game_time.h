#pragma once

#include <chrono>

namespace game_time {


struct GameTime {
    std::chrono::time_point<std::chrono::high_resolution_clock>
            frame_start_time;
    std::chrono::duration<double> total_wall_time;
    std::chrono::duration<double> total_game_time;
    std::chrono::duration<double> elapsed_wall_time;
    std::chrono::duration<double> elapsed_game_time;
    uint64_t frame_number;
};

struct GameClock {
    GameTime last_frame_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_wall_time;
    std::chrono::duration<double> total_game_time;
    uint64_t current_frame;
    double clock_multiplier;
};

struct GameClockBuilder {
    std::chrono::duration<double> start_game_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_wall_time;
    uint64_t start_frame;
    double clock_multiplier;
};

} // namespace game_time
