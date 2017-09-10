#pragma once

#include <chrono>

namespace game_time {
class TimeStep {
public:
    virtual std::chrono::duration<double> const time_step(
            const std::chrono::duration<double>& wall_time) = 0;
};
} // namespace game_time