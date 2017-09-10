#pragma once

#include "FrameCount.h"
#include "TimeStep.h"

namespace game_time {
namespace time_step {
class FixedStep : public TimeStep {
    framerate::FrameCount count;

public:
    FixedStep(framerate::FrameCount count) { this->count = count; }

    std::chrono::duration<double> const time_step(
            const std::chrono::duration<double>& wall_time) {
        return this->step;
    }
};

} // namespace time_step
} // namespace game_time