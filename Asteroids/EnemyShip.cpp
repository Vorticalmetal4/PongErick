#include "EnemyShip.h"
#include "CommonFiles/Renderer.h"
#include "Inih/cpp/INIReader.h"
#include "Raycaster.h"

#include <cmath>

EnemyShip::EnemyShip(Renderer* _Rend)
	:Rend(_Rend),
	Active(false),
	Ray(_Rend),
	wasPlayerUp(false),
	wasPlayerLeft(false),
	ChangeDirection(false),
	TurnLeft(false),
	DeltaTime(0)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("EnemyShip: ConFile Failed");

	Body.setDimensions((float)ConFile.GetInteger("EnemyShip", "Width", 0), (float)ConFile.GetInteger("EnemyShip", "Height", 0));
	Velocity = ConFile.GetInteger("EnemyShip", "Velocity", 0);
	HWidth = Body.getDimensions()->Width / 2.0f;
	HHeight = Body.getDimensions()->Height / 2.0f;

	setNewData(true, false);
	
}

void EnemyShip::Update(Position* PlayerCenter, float PlayerHypotenuse, bool Pause)
{
	if (!Pause)
	{
		DeltaTime = Rend->getDeltaTime();

		if (!Ray.CheckCollision(PlayerCenter->x, PlayerCenter->y, PlayerHypotenuse))
		{

			if (((PlayerCenter->y < BodyCenter->y && wasPlayerUp) || (PlayerCenter->y > BodyCenter->y && !wasPlayerUp)) && ((PlayerCenter->x < BodyCenter->x && wasPlayerLeft) || (PlayerCenter->x > BodyCenter->x && !wasPlayerLeft)))
				ChangeDirection = false;
			else
				ChangeDirection = true;

			if (ChangeDirection)
			{
				if (PlayerCenter->y <= BodyCenter->y)
					wasPlayerUp = true;
				else
					wasPlayerUp = false;

				if (PlayerCenter->x <= BodyCenter->x)
					wasPlayerLeft = true;
				else
					wasPlayerLeft = false;

				if ((wasPlayerUp && BodyThirdPoint->x >= BodyCenter->x) || (!wasPlayerUp && BodyThirdPoint->x <= BodyCenter->x))
					TurnLeft = true;
				else
					TurnLeft = false;

				ChangeDirection = false;
			}

			if (TurnLeft)
				Body.Rotate(true, 1);
			else
				Body.Rotate(false, -1);

		}
		else
			Body.MoveCenter(3, Velocity, DeltaTime);

		Ray.Update(Velocity, BodyThirdPoint);

		Body.MoveEdges(true);

		if (BodyCenter->x > Rend->getWindowWidth())
			Body.ChangeCenterPosition(0, BodyCenter->y);
		else if (BodyCenter->x < 0)
			Body.ChangeCenterPosition((float)Rend->getWindowWidth(), BodyCenter->y);

		if (BodyCenter->y > Rend->getWindowHeight())
			Body.ChangeCenterPosition(BodyCenter->x, 0);
		else if (BodyCenter->y < 0)
			Body.ChangeCenterPosition(BodyCenter->x, (float)Rend->getWindowHeight());
	}

	Rend->DrawTriangle(&Body, 255, 0, 0, 255);
}

void EnemyShip::setNewData(bool Left, bool _Active)
{
	Active = _Active;
	Ray.setActive(true);
	wasPlayerUp = false;
	wasPlayerLeft = false;

	if (Left)
	{
		Body.setPointData(0, Rend->getWindowHeight() / 2.0f, 0, 3);
		BodyThirdPoint = Body.getThirdPoint();
		Body.setPointData(-Body.getDimensions()->Height, BodyThirdPoint->y - HWidth, BodyThirdPoint->Angle + 225, 1);
		Body.setPointData(-Body.getDimensions()->Height, BodyThirdPoint->y + HWidth, BodyThirdPoint->Angle + 135, 2);
		Body.setPointData(BodyThirdPoint->x - HHeight, BodyThirdPoint->y, BodyThirdPoint->Angle, 4);
	}
	else
	{

		Body.setPointData((float)Rend->getWindowWidth(), Rend->getWindowHeight() / 2.0f, 0, 3);
		BodyThirdPoint = Body.getThirdPoint();
		Body.setPointData((float)Rend->getWindowWidth() + Body.getDimensions()->Height, BodyThirdPoint->y + HWidth, BodyThirdPoint->Angle + 225, 1);
		Body.setPointData((float)Rend->getWindowWidth() + Body.getDimensions()->Height, Body.getThirdPoint()->y + HWidth, BodyThirdPoint->Angle + 135, 2);
		Body.setPointData(BodyThirdPoint->x + HHeight, BodyThirdPoint->y, BodyThirdPoint->Angle, 4);
	}	

	BodyCenter = Body.getCenter();
}