#include "../include/game.h"

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    Game game;
    game.open();

    return 0;
}