#include "GameClockBuilder.h"

#include <chrono>

#include "GameClock.h"
#include "GameTime.h"

namespace game_time {

GameClock GameClockBuilder::build() const
{
	auto now = std::chrono::high_resolution_clock::now();
	GameTime game_time = GameTime(this->m_start_wall_time,
		std::chrono::duration<double>{0.0},
		this->m_start_game_time,
		std::chrono::duration<double>{0.0},
		std::chrono::duration<double>{0.0},
		this->m_start_frame);

	return GameClock(game_time,
		this->m_start_wall_time,
		this->m_start_game_time,
		this->m_start_frame,
		this->m_clock_multiplier);
}

} // namespace game_time
