#include "Ray.h"
#include "Player.h"
#include "Brick.h"
#include "../Inih/cpp/INIReader.h"

#include <iostream>
using namespace std;

Ray::Ray(int X, int Y) {
	Position.x = X;
	Position.y = Y;

	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		cout << "Player: Couldn't find the Configuration File" << endl;

	Width = ConFile.GetInteger("Ray", "Width", 0);
	Height = ConFile.GetInteger("Ray", "Height", 0);
	Velocity = ConFile.GetInteger("Ray", "Velocity", 0);
}

Ray::~Ray() {

}

bool Ray::CheckCollition(Brick* ActualBrick, int DeltaTime, char Power, int WindowHeight) {
	int NYPosition = Position.y - DeltaTime * Velocity;

	if (NYPosition >= ActualBrick->getYPosition() && NYPosition <= ActualBrick->getYPosition() + ActualBrick->getHeight()){ 
		if (Position.x >= ActualBrick->getXPosition() && Position.x <= ActualBrick->getXPosition() + ActualBrick->getWidth()) {
			switch (Power) {
			case 'T':
				ActualBrick->setYPosition(WindowHeight - ActualBrick->getHeight());
				break;
			}
			return true;
		}
	}
	else if (NYPosition <= 0) 
		return true;
	

	return false;
}