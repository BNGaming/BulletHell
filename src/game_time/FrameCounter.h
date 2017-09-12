#pragma once

#include <chrono>
#include <memory>

#include "FrameCount.h"
#include "FrameRateSampler.h"
#include "GameTime.h"

namespace game_time {
namespace framerate {

class FrameCounter : public FrameCount {
    double m_target_frame_rate;
    double m_slow_threshold;
    std::unique_ptr<samplers::FrameRateSampler> m_sampler;

public:
    FrameCounter(double target_frame_rate,
            double slow_threshold,
            std::unique_ptr<samplers::FrameRateSampler> sampler)
        : m_target_frame_rate(target_frame_rate),
          m_slow_threshold(slow_threshold), m_sampler(std::move(sampler)) {}

    FrameCounter(double target_frame_rate,
            std::unique_ptr<samplers::FrameRateSampler> sampler)
        : FrameCounter(target_frame_rate,
                  DEFAULT_SLOW_THRESHOLD,
                  std::move(sampler)) {}

    FrameCounter& set_slow_threshold(double slow_threshold) {
        this->m_slow_threshold = slow_threshold;
        return *this;
    }

    double slow_threshold() const { return this->m_slow_threshold; }

    FrameCounter& set_target_frame_rate(double target_frame_rate) {
        this->m_target_frame_rate = target_frame_rate;
        return *this;
    }

    double target_frame_rate() const { return this->m_target_frame_rate; }

    bool is_saturated() const { return this->m_sampler->is_saturated(); }

    const samplers::FrameRateSampler& sampler() const {
        return *this->m_sampler;
    }


    double average_frame_rate() const {
        return this->m_sampler->average_frame_rate();
    }

    std::chrono::duration<double> target_time_per_frame() const {
        return std::chrono::duration<double>{1.0} / this->target_frame_rate();
    }


    std::chrono::duration<double> remaining_frame_time(
            const GameTime& time) const {
        return this->target_time_per_frame() -
                time.elapsed_time_since_start_of_frame();
    }


    bool is_running_slow(const GameTime& time) const {
        double ratio = this->target_time_per_frame() / time.elapsed_wall_time();
        return ratio <= this->slow_threshold();
    }

    void tick(const GameTime& time) { this->m_sampler->tick(time); }
};

} // namespace framerate
} // namespace game_time