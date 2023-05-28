#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

using namespace std;

class game {
private: 
    unique_ptr<sf::RenderWindow> window;
    sf::Event event;

public:
	game();
	~game();

	void open();
};

