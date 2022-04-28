#pragma once

// MODULARIDAD: Esta clase no tiene sentido, debe haber una clase Player que contenga lo que es un jugador
//   tal vez, Score pueda convertirse en un boardlist, en ese caso tendria mayor logica
class Score {
public:
	Score();
	void Player1Goal();
	void Player2Goal();
	int getPlayer1Score();
	int getPlayer2Score();


private:
	int Player1Score; // CPP: Posible overflow. El maximo numero que pudiera guardarse es 2^32, para scores es mucho mas inteligente utilizar variables long long
	int Player2Score;

};
