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
	string LivesText = "Lives: " + to_string(Data.Lives);
	char* NText = new char[LivesText.size() + 1]; // memory leak
	LivesText.copy(NText, LivesText.size() + 1);
	NText[LivesText.size()] = '\0';
	Rend->Write(NText, 0, 0, 920, 30);

	string PuntuationText = "Bricks: " + to_string(Data.BricksRemaining);
	char* PText = new char[LivesText.size() + 1]; // memory leak
	PuntuationText.copy(PText, PuntuationText.size() + 1);
	PText[PuntuationText.size()] = '\0';
	Rend->Write(PText, 0, 0, 0 , 30);

	string PowerText = "Power: ";

	switch (MainPlayer->getPower()[0])
	{
		case 'T':
			PowerText += "Traitor";
		break;	

		case 'L':
			PowerText += "Laser";
		break;

		default:
			PowerText += "No Power";
		break;
	}

	char* PowText = new char[PowerText.size() + 1]; // memory leak
	PowerText.copy(PowText, PowerText.size() + 1);
	PowText[PowerText.size()] = '\0';
	Rend->Write(PowText, 0, 0, 400, 30);


	if (Data.Lives <=  0) 
	{
		string LoseText = "Game Over"; // se lee un poco raro, generalmente game over
		char* LText = new char[LoseText.size() + 1]; // memory leak
		LoseText.copy(LText, LoseText.size() + 1);
		LText[LoseText.size()] = '\0';
		Rend->Write(LText, 50, 50, 470, 350);
	}
	else if (Data.BricksRemaining <= 0)
	{
		string VictoryText = "Win!"; // se lee un poco raro, generalmente win!
		char* VText = new char[VictoryText.size() + 1]; // memory leak
		VictoryText.copy(VText, VictoryText.size() + 1);
		VText[VictoryText.size()] = '\0';
		Rend->Write(VText, 50, 50, 470, 350);
	}
	
}


