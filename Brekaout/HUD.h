#pragma once
class HUD {
public:
	HUD(class Renderer* Rend);
	void UpdateHUD();
	void LoseALife();
	void IncPuntuation(int Inc);

private:
	Renderer* Rend;
	int Lives;
	int Puntuation;
};
