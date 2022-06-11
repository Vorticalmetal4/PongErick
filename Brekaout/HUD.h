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
	void ChangeText(int TextW, int TextH, int TextX, int TextY);

private:
	Renderer* Rend;
	Player* MainPlayer;
	string ActualText;
	char* NText;
};
