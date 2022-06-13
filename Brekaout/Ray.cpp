#include "Ray.h"
#include "Player.h"
#include "Brick.h"
#include "Inih/cpp/INIReader.h"

#include <iostream>
using namespace std;

Ray::Ray() 
{
	Active = false;

	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Ray");

	Width = ConFile.GetInteger("Ray", "Width", 0);
	Height = ConFile.GetInteger("Ray", "Height", 0);
	Velocity = ConFile.GetInteger("Ray", "Velocity", 0);
}

Ray::~Ray()
{

}

void Ray::SetData(int X, int Y, bool _Active) {
	Position.x = X;
	Position.y = Y;
	Active = _Active;
}

bool Ray::CheckCollition(Brick* ActualBrick, int DeltaTime, char Power, int WindowHeight)
{
	NYPosition = Position.y - DeltaTime * Velocity;

	if (NYPosition >= ActualBrick->getYPosition() && NYPosition <= ActualBrick->getYPosition() + ActualBrick->getHeight())
	{ 
		if (Position.x >= ActualBrick->getXPosition() && Position.x <= ActualBrick->getXPosition() + ActualBrick->getWidth())
		{
			switch (Power)
			{
				case 'T':
					ActualBrick->setYPosition(WindowHeight - ActualBrick->getHeight());
				break;

				case 'L':
					ActualBrick->setActive(false);
				break;
			}

			return true;
		}
	}
	else if (NYPosition <= 0) 
		return true;
	

	return false;
}