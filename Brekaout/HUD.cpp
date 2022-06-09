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
	NText = new char[ActualText.size() + 1]; // memory leak
	ActualText.copy(NText, ActualText.size() + 1);
	NText[ActualText.size()] = '\0';
	Rend->Write(NText, 0, 0, 920, 30);
	

	ActualText = "Bricks: " + to_string(Data.BricksRemaining);
	NText = new char[ActualText.size() + 1]; // memory leak
	ActualText.copy(NText, ActualText.size() + 1);
	NText[ActualText.size()] = '\0';
	Rend->Write(NText, 0, 0, 0 , 30);

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

	NText = new char[ActualText.size() + 1]; // memory leak
	ActualText.copy(NText, ActualText.size() + 1);
	NText[ActualText.size()] = '\0';
	Rend->Write(NText, 0, 0, 400, 30);


	if (Data.Lives <=  0) 
	{
		ActualText = "Game Over"; // se lee un poco raro, generalmente game over
		NText = new char[ActualText.size() + 1]; // memory leak
		ActualText.copy(NText, ActualText.size() + 1);
		NText[ActualText.size()] = '\0';
		Rend->Write(NText, 50, 50, 470, 350);
	}
	else if (Data.BricksRemaining <= 0)
	{
		ActualText = "Win!"; // se lee un poco raro, generalmente win!
		NText = new char[ActualText.size() + 1]; // memory leak
		ActualText.copy(NText, ActualText.size() + 1);
		NText[ActualText.size()] = '\0';
		Rend->Write(NText, 50, 50, 470, 350);
	}
	
}


