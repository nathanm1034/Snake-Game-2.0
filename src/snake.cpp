#include "../include/snake.h"

SnakeSegment::SnakeSegment(int x, int y, sf::Texture& texture, sf::Vector2f scaleFactor) 
	: scaleFactor(scaleFactor) {
	setTexture(texture);
	setPosition(x, y);
}

void SnakeSegment::setTexture(sf::Texture& texture) {
	segmentSprite.setTexture(texture);
	float scaleFactorX = 30.f * scaleFactor.x / segmentSprite.getTexture()->getSize().x;
	float scaleFactorY = 30.f * scaleFactor.y / segmentSprite.getTexture()->getSize().y;
	segmentSprite.setScale(scaleFactorX, scaleFactorY);
}

void SnakeSegment::setPosition(int x, int y) {
	segmentPosition.x = x;
	segmentPosition.y = y;
	segmentSprite.setPosition(x * 30 * scaleFactor.x, y * 30 * scaleFactor.y);
}

SnakeSegment::~SnakeSegment() {

}

const sf::Sprite& SnakeSegment::getSprite() const {
	return segmentSprite;
}

Snake::Snake(int startX, int startY, int initialLength, shared_ptr<AssetManager>& assetManager, sf::Vector2f scaleFactor) 
	: assetManager(assetManager), scaleFactor(scaleFactor) {
	body.push_back(SnakeSegment(startX, startY, assetManager->getTexture("HEADR-OBJECT"), scaleFactor));
}

Snake::~Snake() {

}

void Snake::init() {
	
}

const deque<SnakeSegment>& Snake::getBody() const {
	return body;
}
