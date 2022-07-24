#pragma once

#include "Renderer.h"
#include <vector>
#include <string>


struct HUDData
{
	int Lives;
	int Score;
	float Invincibility;
};

class HUD
{
public:
	HUD(Renderer* _Rend);
	~HUD();
	void Update(HUDData* Data);
	bool getPause() { return Pause; }
	bool getReset() { return Reset; }
	void ResetHUD(bool _Reset);
	void FreeMemory();
	

private:
	Renderer* Rend;
	int Lives;
	Position LivesP1;
	Position LivesP2;
	Position LivesP3;
	HUDData Data;
	float LivesInitialX;
	float LivesY;
	int LivesHWidth;
	int LivesWidth;
	int LivesHeight;
	int LivesSeparation;
	int i;
	char NText[7];
	string ScoreText;
	char* GameOver;
	char* Restart;
	char* Invincible;
	bool Pause;
	float HWindowWidth;
	float HWindowHeight;
	bool Reset;

	void InitialPosition();
	void ChangeScore(int Score, int TextW, int TextH, float TextX, float TextY);
};