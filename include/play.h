#pragma once

#include "gameContainer.h"
#include "state.h"
#include "mainMenu.h"

#include<vector>

using namespace std;

class Play : public State {
private:
	shared_ptr<GameContainer> gameContainer;
	sf::Vector2f scaleFactor;
	sf::Sprite wall;
	sf::Sprite grass;
	sf::Sprite food;

	vector<vector<sf::Sprite>> grid;
	vector<sf::Vector2i> foodLocations;
	int gridWidth, gridHeight;
	bool paused;

	void placeFood();

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