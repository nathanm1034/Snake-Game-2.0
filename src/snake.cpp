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

void Snake::init() {
	
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
	//case Direction::UP:
	//	break;
	case Direction::DOWN:
		if (direction != previousDirection) {
			body.front().setTexture(assetManager->getTexture("HEAD-D-OBJECT"));
			body.front().setTextureDirection(SnakeSegment::TextureDirection::DOWN);
		}
		headPos.y++;
		break;
	}

	if (direction == Direction::NONE) return;

	if (previousDirection == Direction::NONE) {
		cout << "none" << endl;
	}

	for (int i = static_cast<int>(body.size()) - 1; i > 0; i--) {
		if (i == 1) {
			if (body[i].getTextureDirection() == SnakeSegment::TextureDirection::HORIZONTAL && direction != Direction::RIGHT && direction != Direction::LEFT) {
				if (direction == Direction::DOWN && (previousDirection == Direction::RIGHT || previousDirection == Direction::NONE)) {
					body[i].setTexture(assetManager->getTexture("BODY-LD-OBJECT"));
					body[i].setTextureDirection(SnakeSegment::TextureDirection::LEFTDOWN);
				}
			}
			else if (body[i].getTextureDirection() == SnakeSegment::TextureDirection::VERTICAL && direction != Direction::UP && direction != Direction::DOWN) {
				if (direction == Direction::RIGHT && previousDirection == Direction::DOWN) {
					body[i].setTexture(assetManager->getTexture("BODY-RU-OBJECT"));
					body[i].setTextureDirection(SnakeSegment::TextureDirection::RIGHTUP);
				}
			}
			else if (body[i].getTextureDirection() == SnakeSegment::TextureDirection::LEFTDOWN && previousDirection == Direction::DOWN) {
				if (direction == Direction::RIGHT) {
					body[i].setTexture(assetManager->getTexture("BODY-RU-OBJECT"));
					body[i].setTextureDirection(SnakeSegment::TextureDirection::RIGHTUP);
				}
				else {
					body[i].setTexture(assetManager->getTexture("BODY-V-OBJECT"));
					body[i].setTextureDirection(SnakeSegment::TextureDirection::VERTICAL);
				}
			}
			else if (body[i].getTextureDirection() == SnakeSegment::TextureDirection::RIGHTUP && previousDirection == Direction::RIGHT) {
				if (direction == Direction::DOWN) {
					body[i].setTexture(assetManager->getTexture("BODY-LD-OBJECT"));
					body[i].setTextureDirection(SnakeSegment::TextureDirection::LEFTDOWN);
				}
				else {
					body[i].setTexture(assetManager->getTexture("BODY-H-OBJECT"));
					body[i].setTextureDirection(SnakeSegment::TextureDirection::HORIZONTAL);
				}
			}
		}
		else if (i == static_cast<int>(body.size()) - 1) {
			if (body[i].getTextureDirection() == SnakeSegment::TextureDirection::RIGHT) {
				if (body[i - 1].getTextureDirection() == SnakeSegment::TextureDirection::LEFTDOWN) {
					body[i].setTexture(assetManager->getTexture("TAIL-D-OBJECT"));
					body[i].setTextureDirection(SnakeSegment::TextureDirection::DOWN);
				}
			}
			if (body[i].getTextureDirection() == SnakeSegment::TextureDirection::DOWN) {
				if (body[i - 1].getTextureDirection() == SnakeSegment::TextureDirection::RIGHTUP) {
					body[i].setTexture(assetManager->getTexture("TAIL-R-OBJECT"));
					body[i].setTextureDirection(SnakeSegment::TextureDirection::RIGHT);
				}
			}
		}
		else {
			if (body[i - 1].getTextureDirection() == SnakeSegment::TextureDirection::HORIZONTAL) {
				body[i].setTexture(assetManager->getTexture("BODY-H-OBJECT"));
				body[i].setTextureDirection(SnakeSegment::TextureDirection::HORIZONTAL);
			}
			else if (body[i - 1].getTextureDirection() == SnakeSegment::TextureDirection::VERTICAL) {
				body[i].setTexture(assetManager->getTexture("BODY-V-OBJECT"));
				body[i].setTextureDirection(SnakeSegment::TextureDirection::VERTICAL);
			}
			else if (body[i - 1].getTextureDirection() == SnakeSegment::TextureDirection::RIGHTUP) {
				body[i].setTexture(assetManager->getTexture("BODY-RU-OBJECT"));
				body[i].setTextureDirection(SnakeSegment::TextureDirection::RIGHTUP);
			}
			else if (body[i - 1].getTextureDirection() == SnakeSegment::TextureDirection::LEFTDOWN) {
				body[i].setTexture(assetManager->getTexture("BODY-LD-OBJECT"));
				body[i].setTextureDirection(SnakeSegment::TextureDirection::LEFTDOWN);
			}
		}
		body[i].setPosition(body[i - 1].getPosition().x, body[i - 1].getPosition().y);
	}
	body.front().setPosition(headPos.x, headPos.y);

	/*for (auto& segment : body) {
		if (segment.getTextureDirection() == SnakeSegment::TextureDirection::RIGHT) {
			cout << "right" << endl;
		}
		else if (segment.getTextureDirection() == SnakeSegment::TextureDirection::HORIZONTAL) {
			cout << "horizontal" << endl;
		}
		else if (segment.getTextureDirection() == SnakeSegment::TextureDirection::DOWN) {
			cout << "down" << endl;
		}
	}*/

	previousDirection = direction;
}

void Snake::setDirection(Direction dir) {
	direction = dir;
}

const deque<SnakeSegment>& Snake::getBody() const {
	return body;
}
