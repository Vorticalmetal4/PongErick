#pragma once
class HUD {
public:
	HUD(class Renderer* Rend, class Player* MainPlayer);
	void UpdateHUD();
	void LoseALife();
	void IncPuntuation(int Inc);

private:
	Renderer* Rend;
	Player* MainPlayer;
	int Lives;
	int Puntuation;
};
