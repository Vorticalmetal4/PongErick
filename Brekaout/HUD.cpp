#include "HUD.h"
#include "Renderer.h"

#include <iostream>
#include <string>
#include "../Inih/cpp/INIReader.h"

using namespace std;

HUD::HUD(Renderer *Rend) {

	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		cout << "HUD: Couldn't find the Configuration File" << endl;

	this->Rend = Rend;
	Lives = ConFile.GetInteger("HUD", "Lives", -1);
}

void HUD::UpdateHUD() {
	string LivesText = "Lives: " + to_string(Lives);
	char* NText = new char[LivesText.size() + 1];
	LivesText.copy(NText, LivesText.size() + 1);
	NText[LivesText.size()] = '\0';
	Rend->Write(NText, 0, 0, 920, 30);
}


void HUD::LoseALife() {
	Lives -= 1;
}