#include "../include/mainMenu.h"

MainMenu::MainMenu(shared_ptr<GameContainer>& gameContainer) 
	: gameContainer(gameContainer) {
}

MainMenu::~MainMenu() {

}

void MainMenu::handleInput() {
	sf::Event event;

	while (gameContainer->window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			gameContainer->window->close();
		}
	}
}

void MainMenu::update() {
	
}

void MainMenu::render() {
	gameContainer->window->clear();
	gameContainer->window->display();
}
