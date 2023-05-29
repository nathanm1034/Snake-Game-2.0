#pragma once

#include "state.h"
#include "gameContainer.h"


class MainMenu : public State {
private:
	shared_ptr<GameContainer> gameContainer;

public:
	MainMenu(shared_ptr<GameContainer>& gameContainer);
	~MainMenu();

	void handleInput() override;
	void update() override;
	void render() override;
};

