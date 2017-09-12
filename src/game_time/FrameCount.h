#pragma once

#include <chrono>

#include "GameTime.h"

namespace game_time {
namespace framerate {

const double DEFAULT_SLOW_THRESHOLD = 0.95;

class FrameCount {
public:
    virtual double target_frame_rate() const = 0;
    virtual double average_frame_rate() const = 0;
    virtual std::chrono::duration<double> target_time_per_frame() const = 0;
    virtual std::chrono::duration<double> remaining_frame_time(
            const GameTime& time) const = 0;
    virtual bool is_running_slow(const GameTime& time) const = 0;

    virtual void tick(const GameTime& time) = 0;
};
} // namespace framerate
} // namespace game_time
