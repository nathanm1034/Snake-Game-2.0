#pragma once

#include "state.h"
#include "assetManager.h"

#include <memory>
#include <SFML/Graphics.hpp>

using namespace std;

struct GameContainer {
	unique_ptr<sf::RenderWindow> window;
	unique_ptr<StateManager> stateManager;
	unique_ptr<AssetManager> assetManager;

	GameContainer() {
		window = make_unique<sf::RenderWindow>();
		stateManager = make_unique<StateManager>();
		assetManager = make_unique<AssetManager>();
	}
};
