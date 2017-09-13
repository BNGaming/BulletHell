#pragma once

#include <chrono>

#include "FrameRateSampler.h"
#include "GameTime.h"

namespace game_time {
namespace framerate {
namespace samplers {
class RunningAverageSampler : public FrameRateSampler {
    uint32_t m_max_samples;
    uint32_t m_current_samples;
    double m_current_average;

public:
    RunningAverageSampler(uint32_t max_samples,
            uint32_t current_samples,
            double current_average)
        : m_max_samples(max_samples), m_current_samples(current_samples),
          m_current_average(current_average) {}

    RunningAverageSampler(uint32_t max_samples)
        : RunningAverageSampler(max_samples, 0, 0.0){};
    RunningAverageSampler()
        : RunningAverageSampler(DEFAULT_NUM_SAMPLES, 0, 0.0){};

	void tick(const GameTime& time);

    double average_frame_rate() const { return this->m_current_average; }
    bool is_saturated() const {
        return this->m_current_samples == this->max_samples();
    }
    uint32_t max_samples() const { return this->m_max_samples; }
};
} // namespace samplers
} // namespace framerate
} // namespace game_time
