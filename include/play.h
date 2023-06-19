#pragma once

#include "gameContainer.h"
#include "state.h"
#include "mainMenu.h"
#include "snake.h"

#include<vector>
#include<queue>
#include<deque>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

using namespace std;

class Play : public State {
private:
	shared_ptr<GameContainer> gameContainer;
	sf::Vector2f scaleFactor;
	sf::Sprite wall;
	sf::Sprite grass;
	sf::Sprite food;
	unique_ptr<Snake> snake;

	vector<vector<sf::Sprite>> grid;
	vector<sf::Vector2i> foodLocations;
	queue<Snake::Direction> directionQueue;
	int gridWidth, gridHeight;
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
};