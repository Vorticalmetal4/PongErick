#include "HUD.h"
#include "Renderer.h"
#include "Player.h"

#include <iostream>
#include <string>
#include "../Inih/cpp/INIReader.h"

using namespace std;

HUD::HUD(Renderer *Rend, Player* MainPlayer) {

	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		cout << "HUD: Couldn't find the Configuration File" << endl;

	this->Rend = Rend;
	this->MainPlayer = MainPlayer;
	Lives = ConFile.GetInteger("HUD", "Lives", -1);
	Puntuation = ConFile.GetInteger("HUD", "Puntuation", 0);

}

void HUD::UpdateHUD() {
	string LivesText = "Lives: " + to_string(Lives);
	char* NText = new char[LivesText.size() + 1];
	LivesText.copy(NText, LivesText.size() + 1);
	NText[LivesText.size()] = '\0';
	Rend->Write(NText, 0, 0, 920, 30);

	string PuntuationText = "Puntuation: " + to_string(Puntuation);
	char* PText = new char[LivesText.size() + 1];
	PuntuationText.copy(PText, PuntuationText.size() + 1);
	PText[PuntuationText.size()] = '\0';
	Rend->Write(PText, 0, 0, 0 , 30);

	string PowerText = "Power: " + MainPlayer->getPower();
	char* PowText = new char[PowerText.size() + 1];
	PowerText.copy(PowText, PowerText.size() + 1);
	PowText[PowerText.size()] = '\0';
	Rend->Write(PowText, 0, 0, 420, 30);
	
}


void HUD::LoseALife() {
	Lives -= 1;
}

void HUD::IncPuntuation(int Inc) {
	Puntuation += Inc;
}