#include <iostream>
#include <memory>

#include <SFML/Window.hpp>

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
