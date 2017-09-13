#pragma once

#include <chrono>

namespace game_time {
namespace time_steps {
class TimeStep {
public:
    virtual std::chrono::duration<double> time_step(
            const std::chrono::duration<double>& wall_time) const = 0;
};
} // namespace time_step
} // namespace game_time