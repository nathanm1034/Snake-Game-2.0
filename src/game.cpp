#include "../include/game.h"

Game::Game() 
    : gameContainer(make_shared<GameContainer>()) {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width / 2;
    unsigned int windowHeight = desktopMode.height / 2;

    gameContainer->window->create(sf::VideoMode(windowWidth, windowHeight), "Snake", (sf::Style::Close));
    gameContainer->stateManager->pushState(make_unique<MainMenu>(gameContainer));
}

Game::~Game() {

}

void Game::open() {
    sf::Clock clock;
    const sf::Time timePerFrame = sf::milliseconds(135);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    gameContainer->window->setFramerateLimit(60);

    while (gameContainer->window->isOpen()) {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        
        gameContainer->stateManager->changeState();
        gameContainer->stateManager->getCurrentState()->handleInput();
        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            gameContainer->stateManager->getCurrentState()->update();
        }
        gameContainer->stateManager->getCurrentState()->render();
    }
}
