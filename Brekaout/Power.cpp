#include "Power.h"
#include "Player.h"
#include "Renderer.h"
#include "../Inih/cpp/INIReader.h"

#include <string>
#include <ctime>
#include <iostream>

using namespace std;

Power::Power(Player* MainPlayer, Renderer* Rend, int X, int Y) {
	this->MainPlayer = MainPlayer;
	this->Rend = Rend;
	this->Position.x = X;
	this->Position.y = Y;

	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		cout << "Ball: Couldn't find the Configuration File" << endl;

	Velocity = ConFile.GetInteger("Power", "Velocity", 0);
	Height = ConFile.GetInteger("Power", "Height", 0);
	LaserProbability = ConFile.GetInteger("Power", "LaserProbability", 0);

	srand(time(NULL));
	if ((rand() % (100) + 1) <= LaserProbability) 
		PowerType = "L";
	else
		PowerType = "T";

}

void Power::Update() {

	string PowerText = PowerType;
	char* NText = new char[PowerText.size() + 1];
	PowerText.copy(NText, PowerText.size() + 1);
	NText[PowerText.size()] = '\0';
	Rend->Write(NText, 0, Height, Position.x, Position.y);

}

bool Power::CheckCollition() {

	float DeltaTime = Rend->getDeltaTime();
	float NPositionY = Position.y + DeltaTime * Velocity;

	if (NPositionY + Height <= Rend->getWindowHeight()) {
		if (Position.x >= MainPlayer->getXPosition() && Position.x <= MainPlayer->getXPosition() + MainPlayer->getWidth()) {
			if (NPositionY + Height >= MainPlayer->getYPosition() && NPositionY + Height <= MainPlayer->getYPosition() + MainPlayer->getHeight()) {
				MainPlayer->ChangePower(PowerType);
				return true;
			}
			else
				Position.y = NPositionY;
		}
		else
			Position.y = NPositionY;
	}
	else
		return true;

	return false;
}