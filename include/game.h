#pragma once

#include "state.h"
#include "mainMenu.h"

#include <memory>
#include <SFML/Graphics.hpp>

using namespace std;

class Game {
private: 
    unique_ptr<sf::RenderWindow> window;
	shared_ptr<StateManager> stateManager;

public:
	Game();
	~Game();

	void open();
};

