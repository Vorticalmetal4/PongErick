#pragma once

#include<string>

using namespace std;

class HUD {
public:
	HUD(class Renderer* Rend, class Player* MainPlayer, int Bricks);
	void UpdateHUD();
	void LoseALife() { Lives--; } // logica puede ir en UpdateHUD
	void DecBricks() { Bricks--; } // logica puede ir en UpdateHUD
	int getLives() { return Lives; }

private:
	Renderer* Rend;
	Player* MainPlayer;
	int Lives;
	int Bricks;
};
