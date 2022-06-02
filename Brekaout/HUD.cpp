#include "HUD.h"
#include "Renderer.h"
#include "Player.h"

#include <iostream>
#include <string>
#include "../Inih/cpp/INIReader.h"

using namespace std;

HUD::HUD(Renderer *Rend, Player* MainPlayer, int Bricks) {

	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		cout << "HUD: Couldn't find the Configuration File" << endl;

	this->Rend = Rend;
	this->MainPlayer = MainPlayer;
	Lives = ConFile.GetInteger("HUD", "Lives", -1);
	this->Bricks = Bricks;

}

void HUD::UpdateHUD() {
	string LivesText = "Lives: " + to_string(Lives);
	char* NText = new char[LivesText.size() + 1];
	LivesText.copy(NText, LivesText.size() + 1);
	NText[LivesText.size()] = '\0';
	Rend->Write(NText, 0, 0, 920, 30);

	string PuntuationText = "Bricks: " + to_string(Bricks);
	char* PText = new char[LivesText.size() + 1];
	PuntuationText.copy(PText, PuntuationText.size() + 1);
	PText[PuntuationText.size()] = '\0';
	Rend->Write(PText, 0, 0, 0 , 30);

	string PowerText = "Power: ";

	switch (MainPlayer->getPower()[0]) {
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

	char* PowText = new char[PowerText.size() + 1];
	PowerText.copy(PowText, PowerText.size() + 1);
	PowText[PowerText.size()] = '\0';
	Rend->Write(PowText, 0, 0, 400, 30);


	if (Lives <=  0) {
		string LoseText = "You Lose";
		char* LText = new char[LoseText.size() + 1];
		LoseText.copy(LText, LoseText.size() + 1);
		LText[LoseText.size()] = '\0';
		Rend->Write(LText, 50, 50, 470, 350);
	}
	else if (Bricks <= 0) {
		string VictoryText = "Victory";
		char* VText = new char[VictoryText.size() + 1];
		VictoryText.copy(VText, VictoryText.size() + 1);
		VText[VictoryText.size()] = '\0';
		Rend->Write(VText, 50, 50, 470, 350);
	}
	
}


