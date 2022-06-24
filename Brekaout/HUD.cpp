#include "HUD.h"
#include "Renderer.h"
#include "Player.h"

#include <string>
#include "Inih/cpp/INIReader.h"


HUD::HUD(Renderer *_Rend, Player* _MainPlayer)
	:Rend(_Rend),
	MainPlayer(_MainPlayer),
	Pause(false)
{
}

void HUD::UpdateHUD(GameData Data)
{
	ActualText = "Lives: " + to_string(Data.Lives);
	ChangeText(0, 0, 920, 30);

	

	ActualText = "Bricks: " + to_string(Data.BricksRemaining);
	ChangeText(0, 0, 0, 30);

	ActualText = "Power: ";

	switch (MainPlayer->getPower())
	{
		case 'T':
			ActualText += "Traitor";
		break;	

		case 'L':
			ActualText += "Laser";
		break;

		default:
			ActualText += "No Power";
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

	if(Pause && Data.Lives > 0 && Data.BricksRemaining > 0)
	{
		ActualText = "Pause";
		ChangeText(50, 50, 465, 350);
		ActualText = "Keyboard Arrows - Move";
		ChangeText(50, 50, 370, 375);
		ActualText = "Space Bar - Shoot Ray";
		ChangeText(50, 50, 370, 400);

	}

	


	if (Data.Lives <=  0) 
	{
		ActualText = "Game Over"; 
		ChangeText(50, 50, 470, 350);
	}
	else if (Data.BricksRemaining <= 0)
	{
		ActualText = "Win!"; 
		ChangeText(50, 50, 470, 350);
	}
	
}

void HUD::ChangeText(int TextW, int TextH, int TextX, int TextY) 
{
	NText = (char*)malloc((ActualText.size() + 1) * sizeof(char)); // NO! buffer allocated deallocated in the loop
	ActualText.copy(NText, ActualText.size() + 1);
	NText[ActualText.size()] = '\0';
	Rend->Write(NText, TextH, TextH, TextX, TextY);
	free(NText);
}

