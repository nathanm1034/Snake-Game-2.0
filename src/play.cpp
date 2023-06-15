#include "../include/play.h"

Play::Play(shared_ptr<GameContainer>& gameContainer) 
	:gameContainer(gameContainer), gridWidth(32), gridHeight(18), paused(false) {
	scaleFactor.x = gameContainer->window->getSize().x / 960.f;
	scaleFactor.y = gameContainer->window->getSize().y / 540.f;
}

Play::~Play() {

}

void Play::init() {
	gameContainer->assetManager->loadTexture("WALL-ENVIRONMENT");
	gameContainer->assetManager->loadTexture("GRASS-ENVIRONMENT");

	wall.setTexture(gameContainer->assetManager->getTexture("WALL-ENVIRONMENT"));
	grass.setTexture(gameContainer->assetManager->getTexture("GRASS-ENVIRONMENT"));
	grid.resize(gridHeight, vector<sf::Sprite>(gridWidth, wall));

	float scaleFactorXWall = 30.f * scaleFactor.x / wall.getTexture()->getSize().x;
	float scaleFactorYWall = 30.f * scaleFactor.y / wall.getTexture()->getSize().y;
	wall.setScale(scaleFactorXWall, scaleFactorYWall);

	float scaleFactorXGrass = 30.f * scaleFactor.x / grass.getTexture()->getSize().x;
	float scaleFactorYGrass = 30.f * scaleFactor.y / grass.getTexture()->getSize().y;
	grass.setScale(scaleFactorXGrass, scaleFactorYGrass);

	for (int y = 0; y < gridHeight; y++) {
		for (int x = 0; x < gridWidth; x++) {
			sf::Sprite& sprite = grid[y][x];

			if (x == 0 || y == 0 || x == gridWidth - 1 || y == gridHeight - 1) {
				sprite = wall;
			}
			else {
				sprite = grass;
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
	gameContainer->window->display();
}

void Play::pause() {
	paused = true;
}

void Play::resume() {
	paused = false;
}
