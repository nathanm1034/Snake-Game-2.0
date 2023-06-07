#include "../include/mainMenu.h"

MainMenu::MainMenu(shared_ptr<GameContainer>& gameContainer) 
	: gameContainer(gameContainer), selectedMenuOption(-1), usingMouse(false) {
}

MainMenu::~MainMenu() {

}

void MainMenu::init() {
	unsigned int baseResolution = 1080;
	unsigned int currentResolution = gameContainer->window->getSize().y;
	float scale = static_cast<float>(currentResolution) / baseResolution;
	float spacing = gameContainer->window->getSize().y / 12.f;

	gameContainer->assetManager->loadFont("MAIN-FONT");

	gameTitle = *initText("Snake Game", gameContainer->window->getSize().x / 2.f, gameContainer->window->getSize().y / 16.f, static_cast<unsigned int>(108 * scale));
	play = *initText("Play", gameContainer->window->getSize().x / 2.f, gameContainer->window->getSize().y / 2.f - spacing, static_cast<unsigned int>(55 * scale));
	highScore = *initText("High Score", gameContainer->window->getSize().x / 2.f, gameContainer->window->getSize().y / 2.f, static_cast<unsigned int>(55 * scale));
	exit = *initText("Exit", gameContainer->window->getSize().x / 2.f, gameContainer->window->getSize().y / 2.f + spacing, static_cast<unsigned int>(55 * scale));

	menuOptions.push_back(make_shared<sf::Text>(play));
	menuOptions.push_back(make_shared<sf::Text>(highScore));
	menuOptions.push_back(make_shared<sf::Text>(exit));
}

void MainMenu::handleInput() {
	sf::Event event;

	cout << selectedMenuOption << endl;

	while (gameContainer->window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			gameContainer->window->close();
		}
		else if (event.type == sf::Event::MouseMoved) {
			handleMouseEvent(event);
		} 
		else if (event.type = sf::Event::KeyPressed) {
			handleKeyEvent(event);
		}
	}
}

void MainMenu::update() {
	for (int i = 0; i < menuOptions.size(); i++) {
		if (i == selectedMenuOption) {
			menuOptions[i]->setFillColor(sf::Color::Red);
		}
		else {
			menuOptions[i]->setFillColor(sf::Color::White);
		}
	}
}

void MainMenu::render() {
	gameContainer->window->clear();
	gameContainer->window->draw(gameTitle);
	for (auto& text : menuOptions) {
		gameContainer->window->draw(*text);
	}
	gameContainer->window->display();
}

shared_ptr<sf::Text> MainMenu::initText(const string& textString, float positionX, float positionY, unsigned int charSize) {
	auto text = make_shared<sf::Text>();
	text->setFont(gameContainer->assetManager->getFont("MAIN-FONT"));
	text->setString(textString);
	text->setCharacterSize(charSize);
	text->setFillColor(sf::Color::White);
	text->setOrigin(text->getLocalBounds().width / 2, text->getLocalBounds().height / 2);
	text->setPosition(positionX, positionY);
	return text;
}

void MainMenu::handleMouseEvent(sf::Event& event) {
	sf::Vector2f mousePosition = gameContainer->window->mapPixelToCoords(sf::Mouse::getPosition(*gameContainer->window));
	bool hovering = false;

	for (int i = 0; i < menuOptions.size(); i++) {
		if (menuOptions[i]->getGlobalBounds().contains(mousePosition)) {
			selectedMenuOption = i;
			usingMouse = true;
			hovering = true;
			break;
		}
	}
	if (!hovering && usingMouse) {
		selectedMenuOption = -1;
	}
}

void MainMenu::handleKeyEvent(sf::Event& event) {
	if (keyClock.getElapsedTime().asMilliseconds() < 200) {
		return;
	}

	switch (event.key.code) {
	case sf::Keyboard::Up:
	case sf::Keyboard::W:
		usingMouse = false;
		if (selectedMenuOption > 0) {
			selectedMenuOption--;
		}
		else if (selectedMenuOption == -1 || selectedMenuOption == 0) {
			selectedMenuOption = static_cast<int>(menuOptions.size()) - 1;
		}
		keyClock.restart();
		break;
	case sf::Keyboard::Down:
	case sf::Keyboard::S:
		usingMouse = false;
		if (selectedMenuOption < menuOptions.size() - 1) {
			selectedMenuOption++;
		}
		else if (selectedMenuOption == -1 || selectedMenuOption == menuOptions.size() - 1) {
			selectedMenuOption = 0;
		}
		keyClock.restart();
		break;
	default:
		break;
	}
}
