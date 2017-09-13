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
    auto num_samples = this->m_current_samples;
	auto effective_fps = std::chrono::duration<double>{ 1.0 } / time.elapsed_wall_time();

	auto new_average = ((this->m_current_average * (num_samples - 1)) + effective_fps) / num_samples;
	this->m_current_average = new_average;
}

} // namespace samplers
} // namespace framerate
} // namespace game_time
