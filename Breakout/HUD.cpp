#include "HUD.h"
#include "CommonFiles/Renderer.h"
#include "Player.h"

#include <string>
#include "Inih/cpp/INIReader.h"


HUD::HUD(Renderer *_Rend, Player* _MainPlayer)
	:Rend(_Rend),
	MainPlayer(_MainPlayer),
	Pause(false)
{
	NText[0] = ' ';
}

void HUD::UpdateHUD(GameData* Data)
{
	CurrentText = "Lives: " + to_string(Data->Lives);
	ChangeText(0, 0, 920, 30);

	

	CurrentText = "Bricks: " + to_string(Data->BricksRemaining);
	ChangeText(0, 0, 0, 30);

	CurrentText = "Power: ";

	switch (MainPlayer->getPower())
	{
		case 'T':
			CurrentText += "Traitor";
		break;	

		case 'L':
			CurrentText += "Laser";
		break;

		default:
			CurrentText += "No Power";
		break;
	}

	ChangeText(0, 0, 400, 30);

	if (Rend->CheckPause())
	{
		if (Pause)
			Pause = false;
		else
			Pause = true;
	}

	if(Pause && Data->Lives > 0 && Data->BricksRemaining > 0)
	{
		CurrentText = "Pause";
		ChangeText(50, 50, 465, 350);
		CurrentText = "Keyboard Arrows - Move";
		ChangeText(50, 50, 370, 375);
		CurrentText = "Space Bar - Shoot Ray";
		ChangeText(50, 50, 370, 400);

	}

	


	if (Data->Lives <=  0) 
	{
		CurrentText = "Game Over"; 
		ChangeText(50, 50, 470, 350);
	}
	else if (Data->BricksRemaining <= 0)
	{
		CurrentText = "Win!"; 
		ChangeText(50, 50, 470, 350);
	}
	
}

void HUD::ChangeText(int TextW, int TextH, float TextX, float TextY) 
{
	CurrentText.copy(NText, CurrentText.size() + 1);
	NText[CurrentText.size()] = '\0';
	Rend->Write(NText, TextH, TextH, TextX, TextY);
}

