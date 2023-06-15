#pragma once

#include "gameContainer.h"
#include "state.h"
#include "assetManager.h"
#include "play.h"

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Thor/Shapes.hpp>

using namespace std;

class MainMenu : public State {
private:
	shared_ptr<GameContainer> gameContainer;
	sf::Text gameTitle;
	sf::Text play;
	sf::Text highScore;
	sf::Text exit;

	vector<shared_ptr<sf::Text>> menuOptions;
	sf::Clock keyClock;
	bool usingMouse;
	bool paused;
	int selectedMenuOption;

	shared_ptr<sf::Text> initText(const string& textString, float positionX, float positionY, unsigned int charSize);
	void handleMouseEvent(sf::Event& event);
	void handleKeyEvent(sf::Event& event);

public:
	MainMenu(shared_ptr<GameContainer>& gameContainer);
	~MainMenu();

	void init() override;
	void handleInput() override;
	void update() override;
	void render() override;
	void pause() override;
	void resume() override;
};

class HighScore : public State {
private:
	shared_ptr<GameContainer> gameContainer;
	sf::ConvexShape popupBody;
	sf::CircleShape closeBody;
	sf::Text closeText;
	sf::Text highScoreTitle;
	sf::Text highScore;

	bool hovering;

	shared_ptr<sf::Text> initText(const string& textString, float positionX, float positionY, unsigned int charSize);

public:
	HighScore(shared_ptr<GameContainer>& gameContainer);
	~HighScore();

	void init() override;
	void handleInput() override;
	void update() override;
	void render() override;
};