#pragma once

#include "assetManager.h"

#include <deque>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

class SnakeSegment {
public:
	enum class TextureDirection {
		UP,
		DOWN,
		LEFT, 
		RIGHT,
		HORIZONTAL,
		VERTICAL,
		RIGHTDOWN,
		LEFTDOWN,
		RIGHTUP,
		LEFTUP
	};

private:
	sf::Sprite segmentSprite;
	sf::Vector2i segmentPosition;
	sf::Vector2f scaleFactor;
	TextureDirection texture;

public:
	SnakeSegment(int x, int y, sf::Texture& texture, sf::Vector2f scaleFactor, TextureDirection textureDirection);
	~SnakeSegment();

	void setTexture(sf::Texture& texture);
	void setTextureDirection(TextureDirection texture);
	void setPosition(int x, int y);
	const sf::Vector2i getPosition() const;
	const sf::Sprite& getSprite() const;
	SnakeSegment::TextureDirection getTextureDirection() { return texture; }
};

class Snake {
public:
	enum class Direction {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE
	};

private:
	deque<SnakeSegment> body;
	Direction direction;
	Direction previousDirection;
	shared_ptr<AssetManager> assetManager;
	sf::Vector2f scaleFactor;

public:
	Snake(int startX, int startY, int initialLength, shared_ptr<AssetManager>& assetManager, sf::Vector2f scaleFactor);
	~Snake();

	void setSegmentTexture(int index);
	void move();
	void setDirection(Direction dir);
	const deque<SnakeSegment>& getBody() const;
};
