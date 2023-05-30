#pragma once

#include "gameContainer.h"
#include "state.h"
#include "assetManager.h"

using namespace std;

class MainMenu : public State {
private:
	shared_ptr<GameContainer> gameContainer;
	sf::Text gameTitle;
	sf::Text play;
	sf::Text highScore;
	sf::Text exit;

public:
	MainMenu(shared_ptr<GameContainer>& gameContainer);
	~MainMenu();

	void init() override;
	void handleInput() override;
	void update() override;
	void render() override;
};

