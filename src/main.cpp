#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "game_time/ConstantStep.h"
#include "game_time/FixedStep.h"
#include "game_time/FrameCount.h"
#include "game_time/FrameCounter.h"
#include "game_time/FrameRateSampler.h"
#include "game_time/GameClock.h"
#include "game_time/GameClockBuilder.h"
#include "game_time/GameTime.h"
#include "game_time/LinearAverageSampler.h"
#include "game_time/RunningAverageSampler.h"
#include "game_time/TimeStep.h"
#include "game_time/VariableStep.h"

//#include "game_time/GameTime.h"
//#include "game_time/GameTime.h"

int main(int argc, char** argv) {
    game_time::GameClock game_clock{};
    game_time::framerate::samplers::LinearAverageSampler frame_rate_sampler{
            60 * 5};
    game_time::framerate::FrameCounter frame_counter{60,
            std::unique_ptr<game_time::framerate::samplers::FrameRateSampler>(
                    std::move(&frame_rate_sampler))};
	//game_time::time_steps::ConstantStep time_step{ std::chrono::duration<double>{ 1.0 / 60.0 } };
	
	game_time::time_steps::FixedStep time_step{
            std::unique_ptr<game_time::framerate::FrameCount>(&frame_counter)};

    sf::RenderWindow window(sf::VideoMode(1600, 1000), "Test window");
    window.setFramerateLimit(60);

    sf::Font font;
    if(!font.loadFromFile("fonts/OpenSans/OpenSans-Regular.ttf")) {
        return 1;
    }
    sf::Text text;
    text.setFont(font);

    auto last_frame_time = game_clock.last_frame_time();

    while(window.isOpen()) {
        last_frame_time = game_clock.tick(time_step);
        frame_counter.tick(last_frame_time);

        double fps = frame_counter.average_frame_rate();
        text.setString("FPS: " + std::to_string(fps) + "\nFrame Number: " +
                std::to_string(last_frame_time.frame_number()) +
                "\nTotal Wall Time: " +
                std::to_string(last_frame_time.total_wall_time().count()) +
                "\nTotal Game Time: " +
                std::to_string(last_frame_time.total_game_time().count()) +
			"\nInstant-FPS: " + std::to_string(last_frame_time.instantaneous_frame_rate()));
        window.clear(sf::Color::Black);
        window.draw(text);

        sf::Event e;
        while(window.pollEvent(e)) {
            switch(e.type) {
            case sf::Event::Closed: {
                window.close();
                break;
            }
            default:
                break;
            }
        }

        window.display();
		//game_clock.sleep_remaining(frame_counter);
		//game_clock.sleep_remaining(frame_counter);
		//game_clock.sleep_remaining(frame_counter);
    }

    return 0;
}
