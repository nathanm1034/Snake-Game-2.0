#pragma once

#include "assetManager.h"

#include <deque>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

class SnakeSegment {
private:
	sf::Sprite segmentSprite;
	sf::Vector2i segmentPosition;
	sf::Vector2f scaleFactor;

public:
	SnakeSegment(int x, int y, sf::Texture& texture, sf::Vector2f scaleFactor);
	~SnakeSegment();

	void setTexture(sf::Texture& texture);
	void setPosition(int x, int y);
	const sf::Sprite& getSprite() const;
};

class Snake {
private:
	deque<SnakeSegment> body;
	shared_ptr<AssetManager> assetManager;
	sf::Vector2f scaleFactor;

public:
	Snake(int startX, int startY, int initialLength, shared_ptr<AssetManager>& assetManager, sf::Vector2f scaleFactor);
	~Snake();

	void init();
	const deque<SnakeSegment>& getBody() const;
};
