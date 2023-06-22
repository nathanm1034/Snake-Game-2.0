#include "../include/play.h"

Play::Play(shared_ptr<GameContainer>& gameContainer) 
	:gameContainer(gameContainer), gridWidth(32), gridHeight(18), gameOver(false), gameOverInitial(false), paused(false) {
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
	foodPosition = foodLocations[index];
	removeFoodLocation(foodPosition);
	food.setPosition(foodPosition.x * 30 * scaleFactor.x, foodPosition.y * 30 * scaleFactor.y);
	food.setColor(sf::Color(255, 255, 255, 255));
}

void Play::addFoodLocation(sf::Vector2i position) {
	foodLocations.push_back(position);
}

void Play::removeFoodLocation(sf::Vector2i position) {
	foodLocations.erase(remove(foodLocations.begin(), foodLocations.end(), position), foodLocations.end());
}

void Play::handleInput() {
	if (gameOver && !gameOverInitial) {
		gameContainer->stateManager->pushState(make_unique<GameOver>(gameContainer));
		gameOverInitial = true;
		return;
	}

	if (paused) return;

	sf::Event event;

	while (gameContainer->window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			gameContainer->window->close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				if (gameOver) {
					gameContainer->stateManager->pushState(make_unique<GameOver>(gameContainer));
				}
				else {
					gameContainer->stateManager->pushState(make_unique<Paused>(gameContainer));
				}
			}
			else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
				directionQueue.push(Snake::Direction::RIGHT);
			}
			else if ((event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) && snake->getDirection() != Snake::Direction::NONE) {
				directionQueue.push(Snake::Direction::LEFT);
			}
			else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
				directionQueue.push(Snake::Direction::UP);
			}
			else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
				directionQueue.push(Snake::Direction::DOWN);
			}
		}
	}
}

void Play::update() {
	if (paused || gameOver) return;

	if (!directionQueue.empty()) {
		Snake::Direction newDirection = directionQueue.front();
		directionQueue.pop();

		if ((newDirection == Snake::Direction::LEFT && snake->getDirection() != Snake::Direction::RIGHT) ||
			(newDirection == Snake::Direction::RIGHT && snake->getDirection() != Snake::Direction::LEFT) ||
			(newDirection == Snake::Direction::UP && snake->getDirection() != Snake::Direction::DOWN) ||
			(newDirection == Snake::Direction::DOWN && snake->getDirection() != Snake::Direction::UP)) {
			snake->setDirection(newDirection);
		}
	}

	if (snake->getDirection() != Snake::Direction::NONE) {
		addFoodLocation(snake->getBody().back().getPosition());
		snake->move();
		removeFoodLocation(snake->getBody().front().getPosition());
	}

	sf::Vector2i head(snake->getBody().front().getPosition());

	if (head.x == 0 || head.y == 0 || head.x == gridWidth - 1 || head.y == gridHeight - 1) {
		gameOver = true;
		return;
	}

	if (head == foodPosition) {
		placeFood();
		//grow
	}
}

void Play::render() {
	gameContainer->window->clear();
	for (int y = 0; y < gridHeight; y++) {
		for (int x = 0; x < gridWidth; x++) {
			gameContainer->window->draw(grid[y][x]);
		}
	}
	gameContainer->window->draw(food);
	for (const auto& segment : snake->getBody()) {
		gameContainer->window->draw(segment.getSprite());
	}
	gameContainer->window->display();
}

void Play::pause() {
	paused = true;
}

void Play::resume() {
	paused = false;
}


Popup::Popup(shared_ptr<GameContainer>& gameContainer) 
	: gameContainer(gameContainer), selectedOption(-1), usingMouse(false) {}

shared_ptr<sf::Text> Popup::initText(const string& textString, float positionX, float positionY, unsigned int charSize, sf::Color fillColor) {
	auto text = make_shared<sf::Text>();
	text->setFont(gameContainer->assetManager->getFont("MAIN-FONT"));
	text->setString(textString);
	text->setCharacterSize(charSize);
	text->setFillColor(fillColor);
	text->setOrigin(text->getLocalBounds().left + text->getLocalBounds().width / 2.f, text->getLocalBounds().top + text->getLocalBounds().height / 2.f);
	text->setPosition(positionX, positionY);
	return text;
}

void Popup::handleInput() {
	sf::Event event;

	while (gameContainer->window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			gameContainer->window->close();
		}
		else if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed) {
			handleMouseEvent(event);
		}
		else if (event.type == sf::Event::KeyPressed) {
			handleKeyEvent(event);
		}
	}
}

void Popup::handleMouseEvent(sf::Event& event) {
	sf::Vector2f mousePosition = gameContainer->window->mapPixelToCoords(sf::Mouse::getPosition(*gameContainer->window));
	bool hovering = false;

	for (int i = 0; i < options.size(); i++) {
		if (options[i]->getGlobalBounds().contains(mousePosition)) {
			selectedOption = i;
			usingMouse = true;
			hovering = true;

			if (event.mouseButton.button == sf::Mouse::Left) {
				if (selectedOption == 0) {
					gameContainer->stateManager->popState();
				}
				else if (selectedOption == 1) {
					gameContainer->stateManager->pushState(make_unique<Play>(gameContainer), true);
				}
				else if (selectedOption == options.size() - 1) {
					gameContainer->stateManager->pushState(make_unique<MainMenu>(gameContainer), true);
				}
			}

			break;
		}
	}

	if (!hovering && usingMouse) {
		selectedOption = -1;
	}
}

void Popup::handleKeyEvent(sf::Event& event) {
	switch (event.key.code) {
	case sf::Keyboard::Up:
	case sf::Keyboard::W:
		usingMouse = false;
		if (selectedOption > 0) {
			selectedOption--;
		}
		else if (selectedOption == -1 || selectedOption == 0) {
			selectedOption = static_cast<int>(options.size()) - 1;
		}
		break;
	case sf::Keyboard::Down:
	case sf::Keyboard::S:
		usingMouse = false;
		if (selectedOption < options.size() - 1) {
			selectedOption++;
		}
		else if (selectedOption == -1 || selectedOption == options.size() - 1) {
			selectedOption = 0;
		}
		break;
	case sf::Keyboard::Enter:
		if (selectedOption == 0) {
			gameContainer->stateManager->popState();
		}
		else if (selectedOption == 1) {
			gameContainer->stateManager->pushState(make_unique<Play>(gameContainer), true);
		}
		else if (selectedOption == options.size() - 1) {
			gameContainer->stateManager->pushState(make_unique<MainMenu>(gameContainer), true);
		}
		break;
	case sf::Keyboard::Escape:
		gameContainer->stateManager->popState();
	default:
		break;
	}
}

void Popup::update() {
	for (int i = 0; i < options.size(); i++) {
		if (i == selectedOption) {
			options[i]->setFillColor(sf::Color::Red);
		}
		else {
			options[i]->setFillColor(sf::Color::White);
		}
	}
}

void Popup::render() {
	gameContainer->window->draw(popupBody);
	gameContainer->window->draw(title);
	for (auto& text : options) {
		gameContainer->window->draw(*text);
	}
	gameContainer->window->display();
}


Paused::Paused(shared_ptr<GameContainer>& gameContainer) 
	: Popup(gameContainer) {}

void Paused::init() {
	const sf::Vector2f windowSize(gameContainer->window->getSize());
	const sf::Vector2f baseResolution(1920.f, 1080.f);
	const sf::Vector2f scaleFactor(windowSize.x / baseResolution.x, windowSize.y / baseResolution.y);
	const float maxScaleFactor = max(scaleFactor.x, scaleFactor.y);
	const float borderThickness = 18.f * maxScaleFactor;
	const float titlePosY = windowSize.y / 4.f + borderThickness * 3.5f;

	const sf::Vector2f popupBodySize(windowSize / 2.f);
	popupBody = thor::Shapes::roundedRect(popupBodySize, 120.f * maxScaleFactor, sf::Color(65, 105, 225), borderThickness, sf::Color::White);
	popupBody.setOrigin(popupBodySize / 2.f);
	popupBody.setPosition(windowSize / 2.f);

	title = *initText("Paused", windowSize.x / 2.f, titlePosY, static_cast<unsigned int>(80.f * scaleFactor.y));
	resume = *initText("Resume", windowSize.x / 2.f, windowSize.y / 2.f - 5.f * borderThickness + title.getGlobalBounds().height / 2.f, static_cast<unsigned int>(65.f * scaleFactor.y));
	restart = *initText("Restart Game", windowSize.x / 2.f, windowSize.y / 2.f + title.getGlobalBounds().height / 2.f, static_cast<unsigned int>(65.f * scaleFactor.y));
	mainMenu = *initText("Main Menu", windowSize.x / 2.f, windowSize.y / 2.f + 5.f * borderThickness + title.getGlobalBounds().height / 2.f, static_cast<unsigned int>(65.f * scaleFactor.y));

	options.push_back(make_shared<sf::Text>(resume));
	options.push_back(make_shared<sf::Text>(restart));
	options.push_back(make_shared<sf::Text>(mainMenu));
}


GameOver::GameOver(shared_ptr<GameContainer>& gameContainer) 
	: Popup(gameContainer) {}

void  GameOver::init() {
	const sf::Vector2f windowSize(gameContainer->window->getSize());
	const sf::Vector2f baseResolution(1920.f, 1080.f);
	const sf::Vector2f scaleFactor(windowSize.x / baseResolution.x, windowSize.y / baseResolution.y);
	const float maxScaleFactor = max(scaleFactor.x, scaleFactor.y);
	const float borderThickness = 18.f * maxScaleFactor;
	const float titlePosY = windowSize.y / 4.f + borderThickness * 3.5f;

	const sf::Vector2f popupBodySize(windowSize / 2.f);
	popupBody = thor::Shapes::roundedRect(popupBodySize, 120.f * maxScaleFactor, sf::Color(65, 105, 225), borderThickness, sf::Color::White);
	popupBody.setOrigin(popupBodySize / 2.f);
	popupBody.setPosition(windowSize / 2.f);

	title = *initText("Game Over", windowSize.x / 2.f, titlePosY, static_cast<unsigned int>(80.f * scaleFactor.y), sf::Color(208, 0 ,0));
	view = *initText("View Board", windowSize.x / 2.f, windowSize.y / 2.f - 5.f * borderThickness + title.getGlobalBounds().height / 2.f, static_cast<unsigned int>(65.f * scaleFactor.y));
	restart = *initText("Play Again", windowSize.x / 2.f, windowSize.y / 2.f + title.getGlobalBounds().height / 2.f, static_cast<unsigned int>(65.f * scaleFactor.y));
	mainMenu = *initText("Main Menu", windowSize.x / 2.f, windowSize.y / 2.f + 5.f * borderThickness + title.getGlobalBounds().height / 2.f, static_cast<unsigned int>(65.f * scaleFactor.y));

	options.push_back(make_shared<sf::Text>(view));
	options.push_back(make_shared<sf::Text>(restart));
	options.push_back(make_shared<sf::Text>(mainMenu));
}
