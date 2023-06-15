#include "../include/play.h"

Play::Play(shared_ptr<GameContainer>& gameContainer) 
	:gameContainer(gameContainer), paused(false) {
}

Play::~Play() {

}

void Play::init() {
	
}

void Play::handleInput() {
	if (paused) return;

	sf::Event event;

	while (gameContainer->window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			gameContainer->window->close();
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			gameContainer->stateManager->popState();
			gameContainer->stateManager->pushState(make_unique<MainMenu>(gameContainer));
		}
	}
}

void Play::update() {

}

void Play::render() {
	gameContainer->window->clear();
	gameContainer->window->display();
}

void Play::pause() {
	paused = true;
}

void Play::resume() {
	paused = false;
}
