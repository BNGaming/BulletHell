#pragma once

#include <memory>

#include "FrameCount.h"
#include "TimeStep.h"

namespace game_time {
namespace time_step {
class FixedStep : public TimeStep {
    std::unique_ptr<framerate::FrameCount> m_count;

public:
    FixedStep(std::unique_ptr<framerate::FrameCount> count) : m_count(std::move(count)) {}

    std::chrono::duration<double> time_step(
            const std::chrono::duration<double>& wall_time) const {
        return this->m_count->target_time_per_frame();
    }
};

} // namespace time_step
} // namespace game_time