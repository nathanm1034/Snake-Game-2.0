#include "../include/game.h"

Game::Game() {
    stateManager = make_shared<StateManager>();
    stateManager->setState(make_unique<MainMenu>());
}

Game::~Game() {

}

void Game::open() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width / 2;
    unsigned int windowHeight = desktopMode.height / 2;

    window = make_unique<sf::RenderWindow>(sf::VideoMode(windowWidth, windowHeight), "Snake", (sf::Style::Close));
    window->setFramerateLimit(60);
	
    sf::Event event;
    while (window->isOpen()) {
        stateManager->getState()->handleInput();
        stateManager->getState()->update();
        stateManager->getState()->render();

        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }

        window->clear();
        window->display();
    }
}
