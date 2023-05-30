#include "../include/assetManager.h"

AssetManager::AssetManager() {

}

AssetManager::~AssetManager() {

}

void AssetManager::loadFont(string key) {
	auto pair = assets.find(key);
	unique_ptr<sf::Font> font = make_unique<sf::Font>();

	if (font->loadFromFile(pair->second)) {
		fonts[key] = move(font);
	}
}

sf::Font& AssetManager::getFont(string key) {
	return *(fonts.at(key).get());
}
