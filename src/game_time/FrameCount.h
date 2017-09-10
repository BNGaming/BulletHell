#pragma once

#include <chrono>

#include "GameTime.h"

namespace game_time {
class FrameCount {
public:
    virtual double const target_frame_rate() = 0;

    template <class T>
    virtual std::chrono::duration<T> const target_time_per_frame() = 0;

    template <class T>
    virtual std::chrono::duration<T> const remaining_frame_time() = 0;

    virtual void tick(const GameTime& time) = 0;

    virtual double const average_frame_rate() = 0;

    virtual bool const is_running_slow(const GameTime& time) = 0;
};
} // namespace game_time
