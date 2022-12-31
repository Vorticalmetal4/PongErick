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
	void UpdateHUD(GameData* Data);
	void ChangeText(int TextW, int TextH, float TextX, float TextY);
	bool getPause() { return Pause; }

private:
	Renderer* Rend;
	Player* MainPlayer;
	string CurrentText;
	char NText[25];
	bool Pause;
};
