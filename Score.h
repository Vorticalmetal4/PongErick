#pragma once

class Score {
public:
	Score();
	void Player1Goal();
	void Player2Goal();
	int getPlayer1Score();
	int getPlayer2Score();


private:
	int Player1Score;
	int Player2Score;

};