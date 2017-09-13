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

    void tick(const GameTime& time) {
        if(!this->is_saturated()) {
            this->m_current_samples += 1;
        }
        auto num_sampled = this->m_current_samples;
        auto effective_fps = 1.0 /
                std::chrono::duration_cast<std::chrono::seconds>(
                        time.elapsed_wall_time())
                        .count();
    }
    double const average_frame_rate() { return this->m_current_average; }
    bool const is_saturated() {
        return this->m_current_samples == this->max_samples();
    }
    uint32_t const max_samples() { return this->m_max_samples; }
};
} // namespace samplers
} // namespace framerate
} // namespace game_time
