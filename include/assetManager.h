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
	unordered_map<string, unique_ptr<sf::Font>> fonts;
	unordered_map<string, unique_ptr<sf::Texture>> textures;

public:
	AssetManager();
	~AssetManager();

	void loadFont(string key);
	void loadTexture(string key);

	sf::Font& getFont(string key);
	sf::Texture& getTexture(string key);
};

