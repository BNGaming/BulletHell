#include <iostream>
#include <memory>

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
    auto x = std::make_unique<int>(5);
    sf::Window window(sf::VideoMode(1600, 1000), "Test window");
    window.setFramerateLimit(60);

    while(window.isOpen()) {
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
    }

    return 0;
}
