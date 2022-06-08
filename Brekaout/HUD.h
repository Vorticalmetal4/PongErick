#pragma once

#include<string>

using namespace std;

struct GameData
{
	int Lives;
	int BricksRemaining;
};

class HUD 
{
public:
	HUD(class Renderer* _Rend, class Player* _MainPlayer);
	void UpdateHUD(GameData Data);

private:
	Renderer* Rend;
	Player* MainPlayer;
};
