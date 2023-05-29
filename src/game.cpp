#include "../include/game.h"

Game::Game() 
    : gameContainer(make_shared<GameContainer>()) {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width / 2;
    unsigned int windowHeight = desktopMode.height / 2;

    gameContainer->window->create(sf::VideoMode(windowWidth, windowHeight), "Snake", (sf::Style::Close));
    gameContainer->stateManager->setState(make_unique<MainMenu>(gameContainer));
}

Game::~Game() {

}

void Game::open() {
    gameContainer->window->setFramerateLimit(60);

    while (gameContainer->window->isOpen()) {
        gameContainer->stateManager->getState()->handleInput();
        gameContainer->stateManager->getState()->update();
        gameContainer->stateManager->getState()->render();
    }
}
