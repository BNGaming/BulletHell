#pragma once

#include "TimeStep.h"

namespace game_time {
namespace time_step {
class VariableStep : public TimeStep {

public:
    VariableStep() {}

    std::chrono::duration<double> time_step(
            const std::chrono::duration<double>& wall_time) const {
        return wall_time;
    }
};

} // namespace time_step
} // namespace game_time