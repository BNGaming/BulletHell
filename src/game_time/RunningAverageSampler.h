#pragma once

#include <chrono>

#include "FrameRateSampler.h"
#include "GameTime.h"

namespace game_time {
namespace framerate {
namespace sampler {
class RunningAverageSampler : public FrameRateSampler {
    uint32_t max_samples;
    uint32_t current_samples;
    double current_average;

public:
    RunningAverageSampler(uint32_t max_samples,
            uint32_t current_samples,
            double current_average) {
        this->max_samples = max_samples;
        this->current_samples = current_samples;
        this->current_average = current_average;
    }

    RunningAverageSampler(uint32_t max_samples)
        : RunningAverageSampler(max_samples, 0, 0.0){};
    RunningAverageSampler()
        : RunningAverageSampler(DEFAULT_NUM_SAMPLES, 0, 0.0){};

    void tick(const GameTime& time) {
        if(!this->is_saturated()) {
            this->current_samples += 1;
        }
        auto num_sampled = this->current_samples;
        auto effective_fps = 1.0 /
                std::chrono::duration_cast<std::chrono::seconds>(
                        time.elapsed_wall_time())
                        .count();
    }
    double const average_frame_rate() { return 1; }
    bool const is_saturated() { return false; }
    uint32_t const max_samples() { return 1; }
};
} // namespace sampler
} // namespace framerate
} // namespace game_time
