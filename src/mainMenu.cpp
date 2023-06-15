#include "../include/mainMenu.h"

MainMenu::MainMenu(shared_ptr<GameContainer>& gameContainer) 
	: gameContainer(gameContainer), selectedMenuOption(-1), usingMouse(false), paused(false) {
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

void MainMenu::handleInput() {
	if (paused) return;

	sf::Event event;

	while (gameContainer->window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			gameContainer->window->close();
		}
		else if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed) {
			handleMouseEvent(event);
		} 
		else if (event.type = sf::Event::KeyPressed) {
			handleKeyEvent(event);
		}
	}
}

void MainMenu::handleMouseEvent(sf::Event& event) {
	sf::Vector2f mousePosition = gameContainer->window->mapPixelToCoords(sf::Mouse::getPosition(*gameContainer->window));
	bool hovering = false;

	for (int i = 0; i < menuOptions.size(); i++) {
		if (menuOptions[i]->getGlobalBounds().contains(mousePosition)) {
			selectedMenuOption = i;
			usingMouse = true;
			hovering = true;

			if (event.mouseButton.button == sf::Mouse::Left) {
				if (selectedMenuOption == 0) {
					gameContainer->stateManager->popState();
					gameContainer->stateManager->pushState(make_unique<Play>(gameContainer));
				}
				else if (selectedMenuOption == 1) {
					gameContainer->stateManager->pushState(make_unique<HighScore>(gameContainer));
				}
				else if (selectedMenuOption == menuOptions.size() - 1) {
					gameContainer->window->close();
				}
			}

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
	case sf::Keyboard::Enter:
		if (selectedMenuOption == 1) {
			gameContainer->stateManager->pushState(make_unique<HighScore>(gameContainer));
			keyClock.restart();
		}
		else if (selectedMenuOption == menuOptions.size() - 1) {
			gameContainer->window->close();
		}
		break;
	default:
		break;
	}
}

void MainMenu::update() {
	if (paused) return;

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

void MainMenu::pause() {
	paused = true;
}

void MainMenu::resume() {
	paused = false;
}



HighScore::HighScore(shared_ptr<GameContainer>& gameContainer) 
	:gameContainer(gameContainer), hovering(false) {
}

HighScore::~HighScore() {

}

void HighScore::init() {
	const sf::Vector2f windowSize(gameContainer->window->getSize());
	const sf::Vector2f baseResolution(1920.f, 1080.f);
	const sf::Vector2f scaleFactor(windowSize.x / baseResolution.x, windowSize.y / baseResolution.y);
	const float maxScaleFactor = max(scaleFactor.x, scaleFactor.y);
	const float borderThickness = 18.f * maxScaleFactor;

	const sf::Vector2f popupBodySize(windowSize / 2.f);
	popupBody = thor::Shapes::roundedRect(popupBodySize, 120.f * maxScaleFactor, sf::Color(105, 105, 105), borderThickness, sf::Color::White);
	popupBody.setOrigin(popupBodySize / 2.f);
	popupBody.setPosition(windowSize / 2.f);

	const float radius = 40.f * maxScaleFactor;
	const sf::Vector2f closePosition(popupBody.getPosition().x * 1.5f - radius / 2.f, popupBody.getPosition().y / 2.f + radius / 2.f);
	const float titlePosY = windowSize.y / 4.f + borderThickness * 3.5f;

	closeBody.setRadius(radius);
	closeBody.setFillColor(sf::Color(105, 105, 105));
	closeBody.setOutlineThickness(borderThickness);
	closeBody.setOutlineColor(sf::Color::White);
	closeBody.setOrigin(radius, radius);
	closeBody.setPosition(closePosition);

	closeText = *initText("x", closePosition.x, closePosition.y, static_cast<unsigned int>(50.f * scaleFactor.y));
	highScoreTitle = *initText("HighScore", windowSize.x / 2.f, titlePosY, static_cast<unsigned int>(80.f * scaleFactor.y));
	highScore = *initText("0", windowSize.x / 2.f, windowSize.y / 2.f, static_cast<unsigned int>(65.f * scaleFactor.y));
}

shared_ptr<sf::Text> HighScore::initText(const string& textString, float positionX, float positionY, unsigned int charSize) {
	auto text = make_shared<sf::Text>();
	text->setFont(gameContainer->assetManager->getFont("MAIN-FONT"));
	text->setString(textString);
	text->setCharacterSize(charSize);
	text->setFillColor(sf::Color::White);
	text->setOrigin(text->getLocalBounds().left + text->getLocalBounds().width / 2.f, text->getLocalBounds().top + text->getLocalBounds().height / 2.f);
	text->setPosition(positionX, positionY);
	return text;
}

void HighScore::handleInput() {
	sf::Event event;

	while (gameContainer->window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			gameContainer->window->close();
		}
		else if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2f mousePosition = gameContainer->window->mapPixelToCoords(sf::Mouse::getPosition(*gameContainer->window));
			if (closeBody.getGlobalBounds().contains(mousePosition)) {
				sf::Vector2f buttonCenter = closeBody.getPosition();
				float radius = closeBody.getRadius();
				float distance = sqrt((mousePosition.x - buttonCenter.x) * (mousePosition.x - buttonCenter.x) + (mousePosition.y - buttonCenter.y) * (mousePosition.y - buttonCenter.y));
				if (distance < radius) {
					hovering = true;
				}
				else {
					hovering = false;
				}

				if (hovering && event.mouseButton.button == sf::Mouse::Left) {
					gameContainer->stateManager->popState();
				}
			}
			else {
				hovering = false;
			}
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			gameContainer->stateManager->popState();
		}
	}
}

void HighScore::update() {
	if (hovering) {
		closeBody.setFillColor(sf::Color::Red);
	}
	else {
		closeBody.setFillColor(sf::Color(105, 105, 105));
	}
}

void HighScore::render() {
	gameContainer->window->draw(popupBody);
	gameContainer->window->draw(closeBody);
	gameContainer->window->draw(closeText);
	gameContainer->window->draw(highScoreTitle);
	gameContainer->window->draw(highScore);
	gameContainer->window->display();
}
