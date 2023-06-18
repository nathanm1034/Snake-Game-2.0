#include "../include/snake.h"

SnakeSegment::SnakeSegment(int x, int y, sf::Texture& texture, sf::Vector2f scaleFactor, TextureDirection textureDirection) 
	: scaleFactor(scaleFactor), texture(textureDirection) {
	setTexture(texture);
	setPosition(x, y);
}

SnakeSegment::~SnakeSegment() {

}

void SnakeSegment::setTexture(sf::Texture& texture) {
	segmentSprite.setTexture(texture);
	float scaleFactorX = 30.f * scaleFactor.x / segmentSprite.getTexture()->getSize().x;
	float scaleFactorY = 30.f * scaleFactor.y / segmentSprite.getTexture()->getSize().y;
	segmentSprite.setScale(scaleFactorX, scaleFactorY);
}

void SnakeSegment::setTextureDirection(TextureDirection texture) {
	this->texture = texture;
}

void SnakeSegment::setPosition(int x, int y) {
	segmentPosition.x = x;
	segmentPosition.y = y;
	segmentSprite.setPosition(x * 30 * scaleFactor.x, y * 30 * scaleFactor.y);
}

const sf::Vector2i SnakeSegment::getPosition() const {
	return segmentPosition;
}

const sf::Sprite& SnakeSegment::getSprite() const {
	return segmentSprite;
}

Snake::Snake(int startX, int startY, int initialLength, shared_ptr<AssetManager>& assetManager, sf::Vector2f scaleFactor) 
	: direction(Direction::NONE), previousDirection(Direction::NONE), assetManager(assetManager), scaleFactor(scaleFactor) {
	body.push_back(SnakeSegment(startX, startY, assetManager->getTexture("HEAD-R-OBJECT"), scaleFactor, SnakeSegment::TextureDirection::RIGHT));
	for (int i = 1; i < initialLength - 1; i++) {
		body.push_back(SnakeSegment(startX - i, startY, assetManager->getTexture("BODY-H-OBJECT"), scaleFactor, SnakeSegment::TextureDirection::HORIZONTAL));
	}
	body.push_back(SnakeSegment(startX - (initialLength - 1), startY, assetManager->getTexture("TAIL-R-OBJECT"), scaleFactor, SnakeSegment::TextureDirection::RIGHT));
}

Snake::~Snake() {

}

void Snake::setSegmentTexture(int index) {
	if (index == 1) {
		switch (body[index].getTextureDirection()) {
		case SnakeSegment::TextureDirection::HORIZONTAL:
			switch (direction) {
			case Direction::UP:
				switch (previousDirection) {
				case Direction::NONE:
				case Direction::RIGHT:
					body[index].setTexture(assetManager->getTexture("BODY-LU-OBJECT"));
					body[index].setTextureDirection(SnakeSegment::TextureDirection::LEFTUP);
					break;
				}
				break;
			case Direction::DOWN:
				switch (previousDirection) {
				case Direction::NONE:
				case Direction::RIGHT:
					body[index].setTexture(assetManager->getTexture("BODY-LD-OBJECT"));
					body[index].setTextureDirection(SnakeSegment::TextureDirection::LEFTDOWN);
					break;
				}
				break;
			}
			break;
		case SnakeSegment::TextureDirection::VERTICAL:
			switch (direction) {
			case Direction::RIGHT:
				switch (previousDirection) {
				case Direction::UP:
					body[index].setTexture(assetManager->getTexture("BODY-RD-OBJECT"));
					body[index].setTextureDirection(SnakeSegment::TextureDirection::RIGHTDOWN);
					break;
				case Direction::DOWN:
					body[index].setTexture(assetManager->getTexture("BODY-RU-OBJECT"));
					body[index].setTextureDirection(SnakeSegment::TextureDirection::RIGHTUP);
					break;
				}
				break;
			}
			break;
		case SnakeSegment::TextureDirection::RIGHTUP:
			switch (previousDirection) {
			case Direction::RIGHT:
				switch (direction) {
				case Direction::RIGHT:
					body[index].setTexture(assetManager->getTexture("BODY-H-OBJECT"));
					body[index].setTextureDirection(SnakeSegment::TextureDirection::HORIZONTAL);
					break;
				case Direction::UP:
					body[index].setTexture(assetManager->getTexture("BODY-LU-OBJECT"));
					body[index].setTextureDirection(SnakeSegment::TextureDirection::LEFTUP);
					break;
				case Direction::DOWN:
					body[index].setTexture(assetManager->getTexture("BODY-LD-OBJECT"));
					body[index].setTextureDirection(SnakeSegment::TextureDirection::LEFTDOWN);
					break;
				}
				break;
			}
			break;
		case SnakeSegment::TextureDirection::LEFTUP:
			switch (previousDirection) {
			case Direction::UP:
				switch (direction) {
				case Direction::RIGHT:
					body[index].setTexture(assetManager->getTexture("BODY-RD-OBJECT"));
					body[index].setTextureDirection(SnakeSegment::TextureDirection::RIGHTDOWN);
					break;
				case Direction::UP:
					body[index].setTexture(assetManager->getTexture("BODY-V-OBJECT"));
					body[index].setTextureDirection(SnakeSegment::TextureDirection::VERTICAL);
					break;
				}
			}
			break;
		case SnakeSegment::TextureDirection::RIGHTDOWN:
			switch (previousDirection) {
			case Direction::RIGHT:
				switch (direction) {
				case Direction::RIGHT:
					body[index].setTexture(assetManager->getTexture("BODY-H-OBJECT"));
					body[index].setTextureDirection(SnakeSegment::TextureDirection::HORIZONTAL);
					break;
				case Direction::UP:
					body[index].setTexture(assetManager->getTexture("BODY-LU-OBJECT"));
					body[index].setTextureDirection(SnakeSegment::TextureDirection::LEFTUP);
					break;
				case Direction::DOWN:
					body[index].setTexture(assetManager->getTexture("BODY-LD-OBJECT"));
					body[index].setTextureDirection(SnakeSegment::TextureDirection::LEFTDOWN);
					break;
				}
				break;
			}
			break;
		case SnakeSegment::TextureDirection::LEFTDOWN:
			switch (previousDirection) {
			case Direction::DOWN:
				switch (direction) {
				case Direction::RIGHT:
					body[index].setTexture(assetManager->getTexture("BODY-RU-OBJECT"));
					body[index].setTextureDirection(SnakeSegment::TextureDirection::RIGHTUP);
					break;
				case Direction::DOWN:
					body[index].setTexture(assetManager->getTexture("BODY-V-OBJECT"));
					body[index].setTextureDirection(SnakeSegment::TextureDirection::VERTICAL);
					break;
				}
				break;
			}
			break;
		}
	}

	else if (index == static_cast<int>(body.size()) - 1) {
		switch (body[index].getTextureDirection()) {
		case SnakeSegment::TextureDirection::RIGHT:
			switch (body[index - 1].getTextureDirection()) {
			case SnakeSegment::TextureDirection::LEFTUP:
				body[index].setTexture(assetManager->getTexture("TAIL-U-OBJECT"));
				body[index].setTextureDirection(SnakeSegment::TextureDirection::UP);
				break;
			case SnakeSegment::TextureDirection::LEFTDOWN:
				body[index].setTexture(assetManager->getTexture("TAIL-D-OBJECT"));
				body[index].setTextureDirection(SnakeSegment::TextureDirection::DOWN);
				break;
			}
			break;
		case SnakeSegment::TextureDirection::LEFT:
			break;
		case SnakeSegment::TextureDirection::UP:
			switch (body[index - 1].getTextureDirection()) {
			case SnakeSegment::TextureDirection::RIGHTDOWN:
				body[index].setTexture(assetManager->getTexture("TAIL-R-OBJECT"));
				body[index].setTextureDirection(SnakeSegment::TextureDirection::RIGHT);
				break;
			}
			break;
		case SnakeSegment::TextureDirection::DOWN:
			switch (body[index - 1].getTextureDirection()) {
			case SnakeSegment::TextureDirection::RIGHTUP:
				body[index].setTexture(assetManager->getTexture("TAIL-R-OBJECT"));
				body[index].setTextureDirection(SnakeSegment::TextureDirection::RIGHT);
				break;
			}
			break;
		}
	}

	else { 
		switch (body[index - 1].getTextureDirection()) {
		case SnakeSegment::TextureDirection::HORIZONTAL:
			body[index].setTexture(assetManager->getTexture("BODY-H-OBJECT"));
			body[index].setTextureDirection(SnakeSegment::TextureDirection::HORIZONTAL);
			break;
		case SnakeSegment::TextureDirection::VERTICAL:
			body[index].setTexture(assetManager->getTexture("BODY-V-OBJECT"));
			body[index].setTextureDirection(SnakeSegment::TextureDirection::VERTICAL);
			break;
		case SnakeSegment::TextureDirection::RIGHTUP:
			body[index].setTexture(assetManager->getTexture("BODY-RU-OBJECT"));
			body[index].setTextureDirection(SnakeSegment::TextureDirection::RIGHTUP);
			break;
		case SnakeSegment::TextureDirection::LEFTUP:
			body[index].setTexture(assetManager->getTexture("BODY-LU-OBJECT"));
			body[index].setTextureDirection(SnakeSegment::TextureDirection::LEFTUP);
			break;
		case SnakeSegment::TextureDirection::RIGHTDOWN:
			body[index].setTexture(assetManager->getTexture("BODY-RD-OBJECT"));
			body[index].setTextureDirection(SnakeSegment::TextureDirection::RIGHTDOWN);
			break;
		case SnakeSegment::TextureDirection::LEFTDOWN:
			body[index].setTexture(assetManager->getTexture("BODY-LD-OBJECT"));
			body[index].setTextureDirection(SnakeSegment::TextureDirection::LEFTDOWN);
			break;
		}
	}
}

void Snake::move() {
	sf::Vector2i headPos = body.front().getPosition();

	switch (direction) {
	case Direction::RIGHT:
		if (direction != previousDirection) {
			body.front().setTexture(assetManager->getTexture("HEAD-R-OBJECT"));
			body.front().setTextureDirection(SnakeSegment::TextureDirection::RIGHT);
		}
		headPos.x++;
		break;
	//case Direction::LEFT:
	//	break;
	case Direction::UP:
		if (direction != previousDirection) {
			body.front().setTexture(assetManager->getTexture("HEAD-U-OBJECT"));
			body.front().setTextureDirection(SnakeSegment::TextureDirection::UP);
		}
		headPos.y--;
		break;
	case Direction::DOWN:
		if (direction != previousDirection) {
			body.front().setTexture(assetManager->getTexture("HEAD-D-OBJECT"));
			body.front().setTextureDirection(SnakeSegment::TextureDirection::DOWN);
		}
		headPos.y++;
		break;
	}

	if (direction == Direction::NONE) return;

	for (int i = static_cast<int>(body.size()) - 1; i > 0; i--) {
		setSegmentTexture(i);
		body[i].setPosition(body[i - 1].getPosition().x, body[i - 1].getPosition().y);
	}
	body.front().setPosition(headPos.x, headPos.y);

	previousDirection = direction;
}

void Snake::setDirection(Direction dir) {
	direction = dir;
}

const deque<SnakeSegment>& Snake::getBody() const {
	return body;
}
