#include "Ray.h"
#include "Player.h"
#include "Brick.h"
#include "Renderer.h"
#include "../Inih/cpp/INIReader.h"

#include <iostream>
using namespace std;

Ray::Ray(int X, int Y, Renderer* Rend) {
	Position.x = X;
	Position.y = Y;

	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		cout << "Player: Couldn't find the Configuration File" << endl;

	Width = ConFile.GetInteger("Ray", "Width", 0);
	Height = ConFile.GetInteger("Ray", "Height", 0);
	Velocity = ConFile.GetInteger("Ray", "Velocity", 0);
	this->Rend = Rend;
}

bool Ray::CheckCollition(Brick* ActualBrick, int DeltaTime) {
	int NYPosition = Position.y + DeltaTime * Velocity;

	return true;
}