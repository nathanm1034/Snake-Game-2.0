#include "../include/game.h"
//#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    Game game;
    game.open();

    return 0;
}