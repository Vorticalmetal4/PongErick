#include "HUD.h"
#include "Renderer.h"
#include "Inih/cpp/INIReader.h"

#include <string>
#include <iostream>
using namespace std;
int l;

HUD::HUD(Renderer* _Rend)
	:Rend(_Rend),
	Pause(false),
	Reset(false)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("HUD");

	LivesInitialX = (float)ConFile.GetInteger("HUD", "LivesInitialX", 0);
	LivesY = (float)ConFile.GetInteger("HUD", "LivesY", 0);
	LivesWidth = ConFile.GetInteger("HUD", "LivesWidth", 0);
	LivesHeight = ConFile.GetInteger("HUD", "LivesHeight", 0);
	LivesSeparation = ConFile.GetInteger("HUD", "LivesSeparation", 0);

	LivesHWidth = LivesWidth / 2.0f;
	LivesP1.y = LivesP3.y = LivesY + LivesHeight;
	LivesP2.y = LivesY;

	string GameOverstr = ConFile.GetString("HUD", "GameOverstr", "Game Over");
	string Restartstr = ConFile.GetString("HUD", "Restartstr", "Pulse R to Restart");
	string Invincibilitystr = ConFile.GetString("HUD", "Invincibilitystr", "Invincible");
	string Scorestr = ConFile.GetString("HUD", "Scorestr", "Score: ");

	GameOver = (char*)malloc((GameOverstr.size() + 1) * sizeof(char));
	Restart = (char*)malloc((Restartstr.size() + 1) * sizeof(char));
	Invincible = (char*)malloc((Invincibilitystr.size() + 1) * sizeof(char));
	ScoreA = (char*)malloc((Scorestr.size() + 1) *  sizeof(char)); // NOTE(isaveg): Memory leak

	if (GameOver != NULL)
	{
		GameOverstr.copy(GameOver, GameOverstr.size() + 1);
		GameOver[GameOverstr.size()] = '\0';
	}

	if (Restart != NULL) {
		Restartstr.copy(Restart, Restartstr.size() + 1);
		Restart[Restartstr.size()] = '\0';
	}

	if (Invincible != NULL) {
		Invincibilitystr.copy(Invincible, Invincibilitystr.size() + 1);
		Invincible[Invincibilitystr.size()] = '\0';
	}

	if(ScoreA != NULL)
	{
		Scorestr.copy(ScoreA, Scorestr.size() + 1);
		ScoreA[Scorestr.size()] = '\0';
	}

	HWindowWidth = Rend->getWindowWidth() / 2.0f;
	HWindowHeight = Rend->getWindowHeight() / 2.0f;

	InitialPosition();

}

HUD::~HUD()
{
}

void HUD::Update(HUDData* Data)
{

	InitialPosition();

	for(l = 0; l < Data->Lives; l++)
	{
		LivesP1.x += LivesSeparation;
		LivesP2.x += LivesSeparation;
		LivesP3.x += LivesSeparation;
		Rend->DrawTriangle(&LivesP1, &LivesP2, &LivesP3, 255, 255, 255, 255);
	}

	if(Rend->CheckPause())
	{
		if (Pause)
			Pause = false;
		else
			Pause = true;
	}


	if (Data->Lives <= 0)
	{
		Rend->Write(GameOver, 100, 100, HWindowWidth - 50.0f, HWindowHeight - 50.0f);		
		Rend->Write(Restart, 100, 100, HWindowWidth - 90.0f, HWindowHeight);
		Rend->Write(ScoreA, 100, 100, HWindowWidth - 48.0f, HWindowHeight + 50.0f);
		ChangeScore(Data->Score, 50, 50, HWindowWidth + 37.0f, HWindowHeight + 50.0f);

		if (Rend->CheckReset())
			Reset = true;
	}

	else 
	{
		ChangeScore(Data->Score, 50, 50, 0, 10);
		if (Data->Invincibility >= 0)
			Rend->Write(Invincible, 100, 100, HWindowWidth - 60, 0, 255, 255, 0, 255);
	}
		
}

void HUD::InitialPosition()
{
	LivesP1.x = LivesInitialX;
	LivesP2.x = LivesInitialX + LivesHWidth;
	LivesP3.x = LivesInitialX + LivesWidth;
}

void HUD::ChangeScore(int Score, int TextW, int TextH, float TextX, float TextY)
{
	ScoreText = to_string(Score);
	ScoreText.copy(NText, ScoreText.size() + 1);
	NText[ScoreText.size() + 1] = '\0';
	Rend->Write(NText, TextH, TextH, TextX, TextY);

}

void HUD::ResetHUD(bool _Reset)
{
	Reset = _Reset;
	for (l = 0; l < strlen(NText); l++)
		NText[l] = ' ';
}

void HUD::FreeMemory()
{
	free(GameOver);
	GameOver = nullptr; 
	free(Restart);
	Restart = nullptr;
	free(Invincible);
	Invincible = nullptr;
}