#include "Ray.h"
#include "Player.h"
#include "Brick.h"
#include "Inih/cpp/INIReader.h"

#include <iostream>
using namespace std;

Ray::Ray(CollisionSystem* _CollisionDetector) 
	:Active(false),
	CollisionDetector(_CollisionDetector),
	NYPosition(0)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Ray could not find ConFile");

	Dimensions.Width = (float)ConFile.GetInteger("Ray", "Width", 0);
	Dimensions.Height = (float)ConFile.GetInteger("Ray", "Height", 0);
	Velocity = ConFile.GetInteger("Ray", "Velocity", 0);

	CurrentPosition.y = CurrentPosition.x = 0;

}

Ray::~Ray()
{

}

void Ray::SetData(float X, float Y, bool _Active) {
	CurrentPosition.x = X;
	CurrentPosition.y = Y;
	Active = _Active;
}

bool Ray::CheckCollition(Brick* ActualBrick, float DeltaTime, char Power, int WindowHeight)
{
	NYPosition = CurrentPosition.y - DeltaTime * Velocity;

	if (CollisionDetector->Square_Square(&CurrentPosition, ActualBrick->getPosition(), &Dimensions, ActualBrick->getDimensions()))
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
	else if (NYPosition <= 0) 
		return true;
	

	return false;
}