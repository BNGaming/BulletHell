#pragma once

#include <chrono>

#include "FrameRateSampler.h"
#include "GameTime.h"

#include "RunningAverageSampler.h"

namespace game_time {
namespace framerate {
namespace samplers {

void RunningAverageSampler::tick(const GameTime& time) {
    if(!this->is_saturated()) {
        this->m_current_samples += 1;
    }
    auto num_sampled = this->m_current_samples;
    auto effective_fps = 1.0 /
            std::chrono::duration_cast<std::chrono::seconds>(
                    time.elapsed_wall_time())
                    .count();
}

} // namespace samplers
} // namespace framerate
} // namespace game_time
