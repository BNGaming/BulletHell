#pragma once

#include "FrameCount.h"

namespace game_time {
namespace framerate {
class FrameCounter : public FrameCount {
    double m_target_frame_rate;
    double m_slow_threshold;


public:
    virtual double target_frame_rate() const = 0;

    virtual std::chrono::duration<double> target_time_per_frame() const = 0;

    virtual std::chrono::duration<double> remaining_frame_time() const = 0;

    virtual void tick(const GameTime& time) = 0;

    virtual double average_frame_rate() const = 0;

    virtual bool is_running_slow(const GameTime& time) const = 0;
};

} // namespace framerate
} // namespace game_time