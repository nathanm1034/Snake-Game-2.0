#pragma once

#include "state.h"

#include <memory>
#include <SFML/Graphics.hpp>

using namespace std;

struct GameContainer {
	unique_ptr<sf::RenderWindow> window;
	unique_ptr<StateManager> stateManager;

	GameContainer() {
		window = make_unique<sf::RenderWindow>();
		stateManager = make_unique<StateManager>();
	}
};
