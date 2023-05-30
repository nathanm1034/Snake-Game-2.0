#include "../include/assetManager.h"

AssetManager::AssetManager() {

}

AssetManager::~AssetManager() {

}

void AssetManager::loadFont(string key) {
	auto pair = assets.find(key);
	unique_ptr<sf::Font> font = make_unique<sf::Font>();

	if (font->loadFromFile(pair->second)) {
		cout << "success" << endl;
	}
	else {
		cout << "fail" << endl;
	}
}

//sf::Font& AssetManager::getFont() {
//
//}
