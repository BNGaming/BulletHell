#pragma once

#include "FrameCount.h"

namespace game_time {
namespace framerate {
class FrameCounter : public FrameCount {
    double m_target_frame_rate;
    double m_slow_threshold;


public:
    virtual double const target_frame_rate() = 0;

    virtual std::chrono::duration<double> const target_time_per_frame() = 0;

    virtual std::chrono::duration<double> const remaining_frame_time() = 0;

    virtual void tick(const GameTime& time) = 0;

    virtual double const average_frame_rate() = 0;

    virtual bool const is_running_slow(const GameTime& time) = 0;
};

} // namespace framerate
} // namespace game_time