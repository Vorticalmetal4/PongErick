#pragma once

#include "CommonFiles/Renderer.h"
#include "CommonFiles/Triangle.h"
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
	HUD() =  default;
	HUD(Renderer* _Rend);
	~HUD() = default;

	bool getPause() { return Pause; }
	bool getReset() { return Reset; }

	void ResetHUD(bool _Reset);
	void FreeMemory();
	void Update(HUDData* Data);
	

private:
	Renderer* Rend;

	Triangle LivesBody;

	int ite;
	int LivesSeparation;

	float LivesInitialX;
	float LivesY;
	float LivesHWidth;
	float HWindowWidth;
	float HWindowHeight;

	char NText[7];
	char* GameOver;
	char* Restart;
	char* Invincible;
	char* ScoreA;

	bool Pause;
	bool Reset;

	string ScoreText;

	void ChangeScore(int Score, int TextW, int TextH, float TextX, float TextY);
	void InitialPosition();
};