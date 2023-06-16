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

	snake = make_unique<Snake>(gridWidth / 2 - 1, gridHeight / 2 - 1, 3, gameContainer->assetManager, scaleFactor);

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

	if (!gameContainer->assetManager->loadTexture("HEADR-OBJECT")) {
		cerr << "Failed to load texture: HEADR-OBJECT" << endl;
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
	foodLocations.erase(foodLocations.begin() + index);
	food.setPosition(pos.x * 30 * scaleFactor.x, pos.y * 30 * scaleFactor.y);
}

void Play::handleInput() {
	if (paused) return;

	sf::Event event;

	while (gameContainer->window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			gameContainer->window->close();
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			gameContainer->stateManager->popState();
			gameContainer->stateManager->pushState(make_unique<MainMenu>(gameContainer));
		}
	}
}

void Play::update() {

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
