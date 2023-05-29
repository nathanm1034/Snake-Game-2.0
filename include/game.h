#pragma once

#include "state.h"
#include "mainMenu.h"
#include "gameContainer.h"

#include <memory>
#include <SFML/Graphics.hpp>

using namespace std;

class Game {
private: 
	shared_ptr<GameContainer> gameContainer;

public:
	Game();
	~Game();

	void open();
};

