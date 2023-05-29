#pragma once

#include "state.h"

class MainMenu : public State {
private:

public:
	MainMenu();
	~MainMenu();

	void handleInput() override;
	void update() override;
	void render() override;
};

