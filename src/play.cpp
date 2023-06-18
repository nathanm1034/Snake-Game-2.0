#include "../include/play.h"

Play::Play(shared_ptr<GameContainer>& gameContainer) 
	:gameContainer(gameContainer), gridWidth(32), gridHeight(18), paused(false) {
	scaleFactor.x = gameContainer->window->getSize().x / 960.f;
	scaleFactor.y = gameContainer->window->getSize().y / 540.f;
}

Play::~Play() {

}

void Play::init() {
	loadTextures();

	wall.setTexture(gameContainer->assetManager->getTexture("WALL-ENVIRONMENT"));
	grass.setTexture(gameContainer->assetManager->getTexture("GRASS-ENVIRONMENT"));
	food.setTexture(gameContainer->assetManager->getTexture("FOOD-OBJECT"));
	grid.resize(gridHeight, vector<sf::Sprite>(gridWidth, wall));

	scaleSprite(wall, 30.f);
	scaleSprite(grass, 30.f);
	scaleSprite(food, 30.f);

	for (int y = 0; y < gridHeight; y++) {
		for (int x = 0; x < gridWidth; x++) {
			sf::Sprite& sprite = grid[y][x];

			if (x == 0 || y == 0 || x == gridWidth - 1 || y == gridHeight - 1) {
				sprite = wall;
			}
			else {
				sprite = grass;
				foodLocations.push_back(sf::Vector2i(x, y));
				if ((x + y) % 2 == 0) {
					sprite.setColor(sf::Color::White);
				}
				else {
					sprite.setColor(sf::Color(180, 180, 180));
				}
			}
			sprite.setPosition(x * 30 * scaleFactor.x, y * 30 * scaleFactor.y);
		}
	}

	snake = make_unique<Snake>(gridWidth / 2 - 1, gridHeight / 2 - 1, 5, gameContainer->assetManager, scaleFactor);
	for (const auto& segment : snake->getBody()) {
		sf::Vector2i position(segment.getPosition());
		removeFoodLocation(position);
	}

	placeFood();
}

void Play::loadTextures() {
	if (!gameContainer->assetManager->loadTexture("WALL-ENVIRONMENT")) {
		cerr << "Failed to load texture: WALL-ENVIRONMENT" << endl;
		exit(EXIT_FAILURE);
	}

	if (!gameContainer->assetManager->loadTexture("GRASS-ENVIRONMENT")) {
		cerr << "Failed to load texture: GRASS-ENVIRONMENT" << endl;
		exit(EXIT_FAILURE);
	}

	if (!gameContainer->assetManager->loadTexture("FOOD-OBJECT")) {
		cerr << "Failed to load texture: FOOD-OBJECT" << endl;
		exit(EXIT_FAILURE);
	}

	if (!gameContainer->assetManager->loadTexture("HEAD-R-OBJECT")) {
		cerr << "Failed to load texture: HEAD-R-OBJECT" << endl;
		exit(EXIT_FAILURE);
	}

	if (!gameContainer->assetManager->loadTexture("HEAD-L-OBJECT")) {
		cerr << "Failed to load texture: HEAD-L-OBJECT" << endl;
		exit(EXIT_FAILURE);
	}

	if (!gameContainer->assetManager->loadTexture("HEAD-U-OBJECT")) {
		cerr << "Failed to load texture: HEAD-U-OBJECT" << endl;
		exit(EXIT_FAILURE);
	}

	if (!gameContainer->assetManager->loadTexture("HEAD-D-OBJECT")) {
		cerr << "Failed to load texture: HEAD-D-OBJECT" << endl;
		exit(EXIT_FAILURE);
	}

	if (!gameContainer->assetManager->loadTexture("BODY-H-OBJECT")) {
		cerr << "Failed to load texture: BODY-H-OBJECT" << endl;
		exit(EXIT_FAILURE);
	}

	if (!gameContainer->assetManager->loadTexture("BODY-V-OBJECT")) {
		cerr << "Failed to load texture: BODY-V-OBJECT" << endl;
		exit(EXIT_FAILURE);
	}

	if (!gameContainer->assetManager->loadTexture("BODY-RU-OBJECT")) {
		cerr << "Failed to load texture: BODY-RU-OBJECT" << endl;
		exit(EXIT_FAILURE);
	}

	if (!gameContainer->assetManager->loadTexture("BODY-RD-OBJECT")) {
		cerr << "Failed to load texture: BODY-RD-OBJECT" << endl;
		exit(EXIT_FAILURE);
	}

	if (!gameContainer->assetManager->loadTexture("BODY-LU-OBJECT")) {
		cerr << "Failed to load texture: BODY-LU-OBJECT" << endl;
		exit(EXIT_FAILURE);
	}

	if (!gameContainer->assetManager->loadTexture("BODY-LD-OBJECT")) {
		cerr << "Failed to load texture: BODY-LD-OBJECT" << endl;
		exit(EXIT_FAILURE);
	}

	if (!gameContainer->assetManager->loadTexture("TAIL-R-OBJECT")) {
		cerr << "Failed to load texture: TAIL-R-OBJECT" << endl;
		exit(EXIT_FAILURE);
	}

	if (!gameContainer->assetManager->loadTexture("TAIL-L-OBJECT")) {
		cerr << "Failed to load texture: TAIL-L-OBJECT" << endl;
		exit(EXIT_FAILURE);
	}

	if (!gameContainer->assetManager->loadTexture("TAIL-U-OBJECT")) {
		cerr << "Failed to load texture: TAIL-U-OBJECT" << endl;
		exit(EXIT_FAILURE);
	}

	if (!gameContainer->assetManager->loadTexture("TAIL-D-OBJECT")) {
		cerr << "Failed to load texture: TAIL-D-OBJECT" << endl;
		exit(EXIT_FAILURE);
	}
}

void Play::scaleSprite(sf::Sprite& sprite, float targetSize) {
	float scaleFactorX = targetSize * scaleFactor.x / sprite.getTexture()->getSize().x;
	float scaleFactorY = targetSize * scaleFactor.y / sprite.getTexture()->getSize().y;
	sprite.setScale(scaleFactorX, scaleFactorY);
}

void Play::placeFood() {
	int index = rand() % foodLocations.size();
	sf::Vector2i pos = foodLocations[index];
	removeFoodLocation(pos);
	food.setPosition(pos.x * 30 * scaleFactor.x, pos.y * 30 * scaleFactor.y);
}

void Play::removeFoodLocation(sf::Vector2i position) {
	foodLocations.erase(remove(foodLocations.begin(), foodLocations.end(), position), foodLocations.end());
}

void Play::handleInput() {
	if (paused) return;

	sf::Event event;

	while (gameContainer->window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			gameContainer->window->close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				gameContainer->stateManager->popState();
				gameContainer->stateManager->pushState(make_unique<MainMenu>(gameContainer));
			}
			else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
				snake->setDirection(Snake::Direction::RIGHT);
			}
			else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
				snake->setDirection(Snake::Direction::LEFT);
			}
			else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
				snake->setDirection(Snake::Direction::UP);
			}
			else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
				snake->setDirection(Snake::Direction::DOWN);
			}
		}
	}
}

void Play::update() {
	snake->move();
}

void Play::render() {
	gameContainer->window->clear();
	for (int y = 0; y < gridHeight; y++) {
		for (int x = 0; x < gridWidth; x++) {
			gameContainer->window->draw(grid[y][x]);
		}
	}
	for (const auto& segment : snake->getBody()) {
		gameContainer->window->draw(segment.getSprite());
	}
	gameContainer->window->draw(food);
	gameContainer->window->display();
}

void Play::pause() {
	paused = true;
}

void Play::resume() {
	paused = false;
}
