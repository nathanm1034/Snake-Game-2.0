#pragma once

#include "gameContainer.h"
#include "state.h"
#include "mainMenu.h"

using namespace std;

class Play : public State {
private:
	shared_ptr<GameContainer> gameContainer;

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

