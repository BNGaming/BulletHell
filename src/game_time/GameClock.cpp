#pragma once

#include <chrono>
#include <functional>

#include "FrameCounter.h"
#include "GameTime.h"
#include "TimeStep.h"

#include "GameClock.h"

namespace game_time {

GameTime GameClock::tick_with_wall_time(const time_steps::TimeStep& time_step,
        std::chrono::time_point<std::chrono::high_resolution_clock>
                frame_start) {
    this->m_current_frame += 1;
    std::chrono::duration<double> elapsed_wall_time =
            frame_start - this->frame_start_time();
    std::chrono::duration<double> elapsed_game_time =
            time_step.time_step(elapsed_wall_time) * this->m_clock_multiplier;
    std::chrono::duration<double> total_game_time =
            this->m_total_game_time + elapsed_game_time;

    this->m_total_game_time = total_game_time;

    GameTime time = GameTime(frame_start,
            frame_start - this->m_start_wall_time,
            total_game_time,
            elapsed_game_time,
            elapsed_wall_time,
            this->current_frame_number());

    this->m_last_frame_time = time;
    return time;
}


void GameClock::sleep_remaining_via(const framerate::FrameCount& counter,
        const std::function<void(const std::chrono::duration<double>&)>& f) {
    std::chrono::duration<double> remaining_time =
            counter.target_time_per_frame() -
            this->last_frame_time().elapsed_time_since_start_of_frame();

    if(remaining_time > std::chrono::duration<double>{0.0}) {
        f(remaining_time);
    }
}
} // namespace game_time
