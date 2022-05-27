#pragma once
class HUD {
public:
	HUD(class Renderer* Rend);
	void UpdateHUD();
	void LoseALife();

private:
	Renderer* Rend;
	int Lives;
};
