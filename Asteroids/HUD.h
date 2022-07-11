#pragma once

#include "Renderer.h"
#include <vector>
#include <string>


struct HUDData
{
	int Lives;
	int Score;
};

class HUD
{
public:
	HUD(class Renderer* _Rend);
	~HUD();
	void Update(HUDData* Data);
	

private:
	Renderer* Rend;
	int Lives;
	Position LivesP1;
	Position LivesP2;
	Position LivesP3;
	HUDData Data;
	int LivesInitialX;
	int LivesY;
	int LivesHWidth;
	int LivesWidth;
	int LivesHeight;
	int LivesSeparation;
	int i;
	char NText[7];
	string ScoreText;

	void InitialPosition();
	void ChangeScore(int Score, int TextW, int TextH, int TextX, int TextY);
};