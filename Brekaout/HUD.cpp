#include "HUD.h"
#include "Renderer.h"
#include "Player.h"

#include <string>
#include "../Inih/cpp/INIReader.h"


HUD::HUD(Renderer *_Rend, Player* _MainPlayer)
	:Rend(_Rend),
	MainPlayer(_MainPlayer)
{
}

void HUD::UpdateHUD(GameData Data)
{
	ActualText = "Lives: " + to_string(Data.Lives);
	ChangeText(0, 0, 920, 30);

	

	ActualText = "Bricks: " + to_string(Data.BricksRemaining);
	ChangeText(0, 0, 0, 30);

	ActualText = "Power: ";

	switch (MainPlayer->getPower()[0])
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
	


	if (Data.Lives <=  0) 
	{
		ActualText = "Game Over"; // se lee un poco raro, generalmente game over
		ChangeText(50, 50, 470, 350);
	}
	else if (Data.BricksRemaining <= 0)
	{
		ActualText = "Win!"; // se lee un poco raro, generalmente win!
		ChangeText(50, 50, 470, 350);
	}
	
}

void HUD::ChangeText(int TextW, int TextH, int TextX, int TextY) 
{
	NText = (char*)malloc((ActualText.size() + 1) * sizeof(char));
	ActualText.copy(NText, ActualText.size() + 1);
	NText[ActualText.size()] = '\0';
	Rend->Write(NText, TextH, TextH, TextX, TextY);
	free(NText);
}

