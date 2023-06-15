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

void AssetManager::loadTexture(string key) {
	auto pair = assets.find(key);
	unique_ptr<sf::Texture> texture = make_unique<sf::Texture>();

	if (texture->loadFromFile(pair->second)) {
		textures[key] = move(texture);
	}
}

sf::Font& AssetManager::getFont(string key) {
	return *(fonts.at(key).get());
}

sf::Texture& AssetManager::getTexture(string key) {
	return *(textures.at(key).get());
}
