#include "../include/save.h"

int getHighScore() {
	ifstream file("highscore.sav", ios::binary);
	if (file.is_open()) {
		int highScore;
		file.read(reinterpret_cast<char*>(&highScore), sizeof(highScore));
		file.close();
		return highScore;
	}
	return 0;
}

void saveHighScore(int highScore) {
	ofstream file("highscore.sav", ios::binary);
	if (file.is_open()) {
		file.write(reinterpret_cast<const char*>(&highScore), sizeof(highScore));
		file.close();
	}
}
