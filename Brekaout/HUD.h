#pragma once

#include<string>

using namespace std;

class HUD {
public:
	HUD(class Renderer* Rend, class Player* MainPlayer, int Bricks);
	void UpdateHUD();
	void LoseALife() { Lives--; }
	void DecBricks() { Bricks--; }
	int getLives() { return Lives; }

private:
	Renderer* Rend;
	Player* MainPlayer;
	int Lives;
	int Bricks;
};
