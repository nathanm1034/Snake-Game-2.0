#pragma once

#include "gameContainer.h"
#include "state.h"
#include "assetManager.h"


class MainMenu : public State {
private:
	shared_ptr<GameContainer> gameContainer;

public:
	MainMenu(shared_ptr<GameContainer>& gameContainer);
	~MainMenu();

	void init() override;
	void handleInput() override;
	void update() override;
	void render() override;
};

