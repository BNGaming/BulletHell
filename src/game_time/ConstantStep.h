#pragma once

#include <chrono>

#include "TimeStep.h"

namespace game_time {
namespace time_step {
class ConstantStep : public TimeStep {
    std::chrono::duration<double> step;

public:
    ConstantStep(std::chrono::duration<double> step) { this->step = step; }
    // ConstantStep(double step) { this->step = std::chrono::duration<double>
    // {step}; }

    ConstantStep null_step() {
        return ConstantStep(std::chrono::duration<double>{0.0});
    }

    std::chrono::duration<double> const time_step(
            const std::chrono::duration<double>& wall_time) {
        return this->step;
    }
};

} // namespace time_step
} // namespace game_time