#include "../include/mainMenu.h"

MainMenu::MainMenu(shared_ptr<GameContainer>& gameContainer) 
	: gameContainer(gameContainer) {
}

MainMenu::~MainMenu() {

}

void MainMenu::init() {
	gameContainer->assetManager->loadFont("MAIN-FONT");

	const float referenceWidth = 1920.f;
	const float referenceHeight = 1080.f;
	float scaleFactor = min(gameContainer->window->getSize().x / referenceWidth, gameContainer->window->getSize().y / referenceHeight);

	gameTitle.setFont(gameContainer->assetManager->getFont("MAIN-FONT"));
	gameTitle.setString("Snake Game");
	gameTitle.setCharacterSize(100.f * scaleFactor);
	gameTitle.setFillColor(sf::Color::White);
	gameTitle.setStyle(sf::Text::Bold);
	gameTitle.setOrigin(gameTitle.getLocalBounds().width / 2, gameTitle.getLocalBounds().height / 2);
	gameTitle.setPosition(gameContainer->window->getSize().x / 2.f, gameContainer->window->getSize().y / 16.f);

	float spacing = gameContainer->window->getSize().y / 12.f;

	play.setFont(gameContainer->assetManager->getFont("MAIN-FONT"));
	play.setString("Play");
	play.setCharacterSize(60.f * scaleFactor);
	play.setFillColor(sf::Color::White);
	play.setOrigin(play.getLocalBounds().width / 2, play.getLocalBounds().height / 2);
	play.setPosition(gameContainer->window->getSize().x / 2.f, gameContainer->window->getSize().y / 2.f - spacing);

	highScore.setFont(gameContainer->assetManager->getFont("MAIN-FONT"));
	highScore.setString("High Score");
	highScore.setCharacterSize(60.f * scaleFactor);
	highScore.setFillColor(sf::Color::White);
	highScore.setOrigin(highScore.getLocalBounds().width / 2, highScore.getLocalBounds().height / 2);
	highScore.setPosition(gameContainer->window->getSize().x / 2.f, gameContainer->window->getSize().y / 2.f);

	exit.setFont(gameContainer->assetManager->getFont("MAIN-FONT"));
	exit.setString("Exit");
	exit.setCharacterSize(60.f * scaleFactor);
	exit.setFillColor(sf::Color::White);
	exit.setOrigin(exit.getLocalBounds().width / 2, exit.getLocalBounds().height / 2);
	exit.setPosition(gameContainer->window->getSize().x / 2.f, gameContainer->window->getSize().y / 2.f + spacing);
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
	gameContainer->window->draw(gameTitle);
	gameContainer->window->draw(play);
	gameContainer->window->draw(highScore);
	gameContainer->window->draw(exit);
	gameContainer->window->display();
}
