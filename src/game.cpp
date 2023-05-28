#include "../include/game.h"

game::game() {

}

game::~game() {

}

void game::open() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width / 2;
    unsigned int windowHeight = desktopMode.height / 2;

    window = make_unique<sf::RenderWindow>(sf::VideoMode(windowWidth, windowHeight), "Snake", (sf::Style::Close));
    window->setFramerateLimit(60);
	
    while (window->isOpen()) {
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }

        window->clear();
        window->display();
    }
}
