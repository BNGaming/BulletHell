#pragma once

#include <chrono>
#include <deque>
#include <numeric>

#include "FrameRateSampler.h"
#include "GameTime.h"

#include "LinearAverageSampler.h"

namespace game_time {
namespace framerate {
namespace samplers {

void LinearAverageSampler::tick(const GameTime& time) {
	auto effective_fps = std::chrono::duration<double>{ 1.0 } / time.elapsed_wall_time();
    if(this->is_saturated()) {
        this->m_past_data.pop_front();
    }
    this->m_past_data.push_back(effective_fps);
}


} // namespace samplers
} // namespace framerate
} // namespace game_time
