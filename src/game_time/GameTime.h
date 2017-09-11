#pragma once

#include <chrono>

namespace game_time {

class GameTime {
    std::chrono::time_point<std::chrono::high_resolution_clock>
            m_frame_start_time;
    std::chrono::duration<double> m_total_wall_time;
    std::chrono::duration<double> m_total_game_time;
    std::chrono::duration<double> m_elapsed_wall_time;
    std::chrono::duration<double> m_elapsed_game_time;
    uint64_t m_frame_number;

public:
    GameTime(std::chrono::time_point<std::chrono::high_resolution_clock>
                     frame_start_time,
            std::chrono::duration<double> total_wall_time,
            std::chrono::duration<double> total_game_time,
            std::chrono::duration<double> elapsed_wall_time,
            std::chrono::duration<double> elapsed_game_time,
            uint64_t frame_number)
        : m_frame_start_time(frame_start_time),
          m_total_wall_time(total_wall_time),
          m_total_game_time(total_game_time),
          m_elapsed_wall_time(elapsed_wall_time),
          m_elapsed_game_time(elapsed_game_time), m_frame_number(frame_number) {
    }

    std::chrono::time_point<std::chrono::high_resolution_clock>
    frame_start_time() const {
        return this->m_frame_start_time;
    }
    std::chrono::duration<double> total_wall_time() const {
        return this->m_total_wall_time;
    }
    std::chrono::duration<double> total_game_time() const {
        return this->m_total_game_time;
    }
    std::chrono::duration<double> elapsed_wall_time() const {
        return this->m_elapsed_wall_time;
    }
    std::chrono::duration<double> elapsed_game_time() const {
        return this->m_elapsed_game_time;
    }

    std::chrono::duration<double> elapsed_time_since_start_of_frame() const {
        auto now = std::chrono::high_resolution_clock::now();
        return this->m_frame_start_time - now;
    }

    uint64_t frame_number() const { return this->m_frame_number; }

    double instantaneous_frame_rate() const {
        return 1.0 /
                std::chrono::duration_cast<std::chrono::seconds>(
                        this->m_elapsed_game_time)
                        .count();
    }
};

} // namespace game_time
