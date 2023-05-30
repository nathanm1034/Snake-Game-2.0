#pragma once

#include "assets.h"

#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class AssetManager {
private:
	unordered_map<int, unique_ptr<sf::Font>> fonts;

public:
	AssetManager();
	~AssetManager();

	void loadFont(string key);
	//sf::Font& getFont();
};

