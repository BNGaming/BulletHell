#pragma once

#include "GameTime.h"

namespace game_time {
namespace framerate {
namespace sampler {

uint32_t DEFAULT_NUM_SAMPLES = 64;

class FrameRateSampler {
    virtual void tick(const GameTime& time) = 0;
    virtual double const average_frame_rate() = 0;
    virtual bool const is_saturated() = 0;
    virtual uint32_t const max_samples() = 0;
};
} // namespace sampler
} // namespace framerate
} // namespace game_time