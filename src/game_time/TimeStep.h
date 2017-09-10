#pragma once

#include <chrono>

namespace game_time {
class TimeStep {
public:
    template <class T>
    virtual std::chrono::duration<T> time_step(
            const std::chrono::duration<T>& wall_time) = 0;
};
} // namespace game_time