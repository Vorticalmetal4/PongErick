#include "Score.h"
#include "./SDL2/include/SDL.h"


Score::Score() {
	Player1Score = 0;
	Player2Score = 0;
}

void Score::Player1Goal() {
	Player1Score++;
	if (Player1Score > 9) {
		Player1Score = 0;
		Player2Score = 0;
	}
}

void Score::Player2Goal() {
	Player2Score++;
	if (Player2Score > 9) {
		Player1Score = 0;
		Player2Score = 0;

	}
}

int Score::getPlayer1Score() { return Player1Score; } // ESTILO: Este formato es mas comun en .h y no cpp

int Score::getPlayer2Score() { return Player2Score; }


