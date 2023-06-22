#pragma once

#include "gameContainer.h"
#include "state.h"
#include "mainMenu.h"
#include "snake.h"

#include <vector>
#include <queue>
#include <deque>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Thor/Shapes.hpp>

using namespace std;

class Play : public State {
private:
	shared_ptr<GameContainer> gameContainer;
	sf::Sprite wall;
	sf::Sprite grass;
	sf::Sprite food;
	unique_ptr<Snake> snake;
	sf::Vector2f scaleFactor;

	vector<vector<sf::Sprite>> grid;
	int gridWidth, gridHeight;

	vector<sf::Vector2i> foodLocations;
	sf::Vector2i foodPosition;

	queue<Snake::Direction> directionQueue;
	bool gameOver;
	bool gameOverInitial;
	bool paused;

	void loadTextures();
	void scaleSprite(sf::Sprite& sprite, float targetSize);
	void placeFood();
	void addFoodLocation(sf::Vector2i position);
	void removeFoodLocation(sf::Vector2i position);

public:
	Play(shared_ptr<GameContainer>& gameContainer);
	~Play();

	void init() override;
	void handleInput() override;
	void update() override;
	void render() override;
	void pause() override;
	void resume() override;

	string getType() override { return "Play"; }
};

class Popup : public State {
protected:
	shared_ptr<GameContainer> gameContainer;
	sf::ConvexShape popupBody;
	sf::Text title;
	vector<shared_ptr<sf::Text>> options;
	bool usingMouse;
	int selectedOption;

	shared_ptr<sf::Text> initText(const string& textString, float positionX, float positionY, unsigned int charSize, sf::Color fillColor = sf::Color::White);
	void handleMouseEvent(sf::Event& event);
	void handleKeyEvent(sf::Event& event);

public:
	Popup(shared_ptr<GameContainer>& gameContainer);
	virtual ~Popup() {};

	void handleInput() override;
	void update() override;
	void render() override;
};

class Paused : public Popup {
private:
	sf::Text resume;
	sf::Text restart;
	sf::Text mainMenu;

public:
	Paused(shared_ptr<GameContainer>& gameContainer);

	void init() override;
};

class GameOver : public Popup {
private:
	sf::Text view;
	sf::Text restart;
	sf::Text mainMenu;

public:
	GameOver(shared_ptr<GameContainer>& gameContainer);

	void init() override;
};