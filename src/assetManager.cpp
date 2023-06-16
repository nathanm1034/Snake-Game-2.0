#include "../include/assetManager.h"

AssetManager::AssetManager() {

}

AssetManager::~AssetManager() {

}

bool AssetManager::loadFont(string key) {
	auto pair = assets.find(key);
	unique_ptr<sf::Font> font = make_unique<sf::Font>();

	if (!font->loadFromFile(pair->second)) {
		return false;
	}

	fonts[key] = move(font);
	return true;
}

bool AssetManager::loadTexture(string key) {
	auto pair = assets.find(key);
	unique_ptr<sf::Texture> texture = make_unique<sf::Texture>();

	if (!texture->loadFromFile(pair->second)) {
		return false;
	}

	textures[key] = move(texture);
	return true;
}

sf::Font& AssetManager::getFont(string key) {
	return *(fonts.at(key).get());
}

sf::Texture& AssetManager::getTexture(string key) {
	return *(textures.at(key).get());
}
