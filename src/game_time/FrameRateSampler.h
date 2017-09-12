#pragma once

#include "GameTime.h"

namespace game_time {
namespace framerate {
namespace samplers {

uint32_t DEFAULT_NUM_SAMPLES = 64;

class FrameRateSampler {
public:
    virtual void tick(const GameTime& time) = 0;
    virtual double average_frame_rate() const = 0;
    virtual bool is_saturated() const = 0;
    virtual uint32_t max_samples() const = 0;
};
} // namespace samplers
} // namespace framerate
} // namespace game_time