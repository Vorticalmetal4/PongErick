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
	TurnLeft(false)
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

EnemyShip::~EnemyShip()
{
}

void EnemyShip::Update(Position* PlayerCenter, float PlayerHypotenuse, bool Pause)
{
	if (!Pause)
	{
		DeltaTime = Rend->getDeltaTime();

		if (!Ray.CheckCollision(PlayerCenter->x, PlayerCenter->y, PlayerHypotenuse))
		{

			if (((PlayerCenter->y < Body.getCenter()->y && wasPlayerUp) || (PlayerCenter->y > Body.getCenter()->y && !wasPlayerUp)) && ((PlayerCenter->x < Body.getCenter()->x && wasPlayerLeft) || (PlayerCenter->x > Body.getCenter()->x && !wasPlayerLeft)))
				ChangeDirection = false;
			else
				ChangeDirection = true;

			if (ChangeDirection)
			{
				if (PlayerCenter->y <= Body.getCenter()->y)
					wasPlayerUp = true;
				else
					wasPlayerUp = false;

				if (PlayerCenter->x <= Body.getCenter()->x)
					wasPlayerLeft = true;
				else
					wasPlayerLeft = false;

				if ((wasPlayerUp && Body.getThirdPoint()->x >= Body.getCenter()->x) || (!wasPlayerUp && Body.getThirdPoint()->x <= Body.getCenter()->x))
					TurnLeft = true;
				else
					TurnLeft = false;

				ChangeDirection = false;
			}

			if (TurnLeft)
			{
				Body.Rotate(true, 1);
				//Center.Angle++;
			}
			else
			{
				Body.Rotate(false, -1);
				//Center.Angle--;
			}

		}
		else
			Body.MoveCenter(3, Velocity, DeltaTime);

		Ray.Update(Velocity, Body.getThirdPoint());

		Body.MoveEdges(true);

		if (Body.getCenter()->x > Rend->getWindowWidth())
			Body.ChangeCenterPosition(0, Body.getCenter()->y);
		else if (Body.getCenter()->x < 0)
			Body.ChangeCenterPosition((float)Rend->getWindowWidth(), Body.getCenter()->y);

		if (Body.getCenter()->y > Rend->getWindowHeight())
			Body.ChangeCenterPosition(Body.getCenter()->x, 0);
		else if (Body.getCenter()->y < 0)
			Body.ChangeCenterPosition(Body.getCenter()->x, (float)Rend->getWindowHeight());
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
		Body.setPointData(-Body.getDimensions()->Height, Body.getThirdPoint()->y - HWidth, Body.getThirdPoint()->Angle + 225, 1);
		Body.setPointData(-Body.getDimensions()->Height, Body.getThirdPoint()->y + HWidth, Body.getThirdPoint()->Angle + 135, 2);
		Body.setPointData(Body.getThirdPoint()->x - HHeight, Body.getThirdPoint()->y, Body.getThirdPoint()->Angle, 4);
	}
	else
	{

		Body.setPointData((float)Rend->getWindowWidth(), Rend->getWindowHeight() / 2.0f, 0, 3);
		Body.setPointData((float)Rend->getWindowWidth() + Body.getDimensions()->Height, Body.getThirdPoint()->y + HWidth, Body.getThirdPoint()->Angle + 225, 1);
		Body.setPointData((float)Rend->getWindowWidth() + Body.getDimensions()->Height, Body.getThirdPoint()->y + HWidth, Body.getThirdPoint()->Angle + 135, 2);
		Body.setPointData(Body.getThirdPoint()->x + HHeight, Body.getThirdPoint()->y, Body.getThirdPoint()->Angle, 4);
	}	
}