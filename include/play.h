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

	vector<vector<sf::Sprite>> grid;
	int gridWidth, gridHeight;
	bool paused;

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