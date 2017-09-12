#pragma once

#include <chrono>
#include <deque>
#include <numeric>

#include "FrameRateSampler.h"
#include "GameTime.h"

namespace game_time {
namespace framerate {
namespace samplers {
class LinearAverageSampler : public FrameRateSampler {
    uint32_t m_max_samples;
    std::deque<double> m_past_data;

public:
    LinearAverageSampler(uint32_t max_samples, std::deque<double> past_data)
        : m_max_samples(max_samples), m_past_data(std::move(past_data)) {}

    LinearAverageSampler(uint32_t max_samples)
        : LinearAverageSampler(max_samples, std::deque<double>(max_samples)){};
    LinearAverageSampler() : LinearAverageSampler(DEFAULT_NUM_SAMPLES){};

	void tick(const GameTime& time);

    double const average_frame_rate() {
        double sum = std::accumulate(
                this->m_past_data.begin(), this->m_past_data.end(), 0.0);
        return sum / this->m_past_data.size();
    }

    bool const is_saturated() {
        return this->m_past_data.size() == this->max_samples();
    }
    uint32_t const max_samples() { return this->m_max_samples; }
};
} // namespace samplers
} // namespace framerate
} // namespace game_time
