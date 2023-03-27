//This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Player.h"
#include "Inih/cpp/INIReader.h"
#include "CommonFiles/Renderer.h"
#include "Laser.h"
#include "Asteroid.h"
#include "EnemyShip.h"

#include <cmath>

int ite;

Player::Player(Renderer* _Rend, CollisionSystem* _CollisionDetector)
	:Rend(_Rend),
	CollisionDetector(_CollisionDetector),
	Velocity(0),
	CurrentCooldown(0),
	DeltaTime(0),
	Rotation(0)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Player: ConFile Failed");

	MaxVelocity = ConFile.GetInteger("Player", "MaxVelocity", 0);
	IncVelocity = ConFile.GetInteger("Player", "IncVelocity", 0);
	DecVelocity = IncVelocity / 2;
	RotationVelocity = ConFile.GetInteger("Player", "RotationVelocity", 0);
	Body.setDimensions((float)ConFile.GetInteger("Player", "Width", 0), (float)ConFile.GetInteger("Player", "Height", 0));
	float HWidth = Body.getDimensions()->Width / 2.0f;
	float HHeight = Body.getDimensions()->Height / 2.0f;
	Body.setPointData( (float)ConFile.GetInteger("Player", "PositionX", 0), (float)ConFile.GetInteger("Player", "PositionY", 0), 315, 1);
	Body.setPointData(Body.getFirstPoint()->x + Body.getDimensions()->Width, Body.getFirstPoint()->y, 225, 2);
	Body.setPointData(Body.getFirstPoint()->x + HWidth, Body.getFirstPoint()->y - Body.getDimensions()->Height, 90, 3);
	Body.setPointData(Body.getThirdPoint()->x, Body.getThirdPoint()->y + HHeight, 0, 4);

	ShootCooldown = ConFile.GetInteger("Player", "ShootCooldown", 0);
	Invincibility = DamageCooldown = (float)ConFile.GetInteger("Player", "DamageCooldown", 0);

	NLasers = ConFile.GetInteger("Player", "NLasers", 0);
	Lasers = nullptr;
	Lasers =  new Laser[NLasers]; // NOTE(isaveg): Memory leak

	if (Rend != nullptr)
		for (ite = 0; ite < NLasers; ite++)
				Lasers[ite] = Laser(Rend, CollisionDetector);

	Body.MoveEdges(true);
}


Player::~Player()
{
	for (ite = 0; ite < NLasers; ite++)
		Lasers[ite].~Laser();
}

void Player::Update(bool Pause)
{
	if (!Pause)
	{
		DeltaTime = Rend->getDeltaTime();

		Rotation = RotationVelocity * DeltaTime;

		switch (Rend->CheckMovement())
		{
		case 'R':
			Body.Rotate(false, Rotation);
			Body.MoveEdges(true);
			break;

		case 'L':
			Body.Rotate(true, Rotation);
			Body.MoveEdges(true);
			break;

		case 'U':
			if (Velocity + IncVelocity <= MaxVelocity)
				Velocity += IncVelocity;

			Body.MoveCenter(3, Velocity, DeltaTime);
			break;

		case 'S':
			if (CurrentCooldown <= 0)
			{
				CurrentCooldown = ShootCooldown;
				for (ite = 0; ite < NLasers; ite++)
				{
					if (!Lasers[ite].getActive())
					{
						Lasers[ite].setActive(true);
						Lasers[ite].setPosition(Body.getThirdPoint()->x, Body.getThirdPoint()->y, Body.getThirdPoint()->Angle, Body.getThirdPoint()->Rotation);
						break;
					}
				}
			}
			break;

		}

		if (Velocity - DecVelocity >= 0)
		{
			Velocity -= DecVelocity;

			Body.MoveCenter(3, Velocity, DeltaTime);
			Body.MoveEdges(false);
		}

		if (Body.getCenter()->x > Rend->getWindowWidth())
			Body.ChangeCenterPosition(0, Body.getCenter()->y);
		else if (Body.getCenter()->x < 0)
			Body.ChangeCenterPosition((float)Rend->getWindowWidth(), Body.getCenter()->y);

		if (Body.getCenter()->y > Rend->getWindowHeight())
			Body.ChangeCenterPosition(Body.getCenter()->x, 0);
		else if (Body.getCenter()->y < 0)
			Body.ChangeCenterPosition(Body.getCenter()->x, (float)Rend->getWindowHeight());

		CurrentCooldown--;
		Invincibility -= DeltaTime;
	}

	for (ite = 0; ite < NLasers; ite++)
		if (Lasers[ite].getActive())
			Lasers[ite].Update(Pause);

	if(Invincibility <= 0)
		Rend->DrawTriangle(&Body, 255, 255, 255, 255);
	else
		Rend->DrawTriangle(&Body, 255, 255, 0, 255);
} 

bool Player::CheckLasersCollisions(Position* OtherObjectPos, Dimension* OtherObjectDimensions, bool isObjectASquare)
{
	for(ite = 0; ite < NLasers; ite++)
	{
		if (Lasers[ite].getActive())

			if (Lasers[ite].CheckCollision(OtherObjectPos, OtherObjectDimensions, isObjectASquare))
				return true;
	}

	return false;
}

bool Player::CheckCollisions(Position* OtherObjectPos, float OtherObjectHypotenuse)
{
	if (Invincibility <= 0)
	{
		if (CollisionDetector->Circle_Circle(Body.getCenter(), OtherObjectPos, Body.getDimensions()->Hypotenuse, OtherObjectHypotenuse))
		{
			Body.getCenter()->x = Rend->getWindowWidth() / 2.0f;
			Body.getCenter()->y = Rend->getWindowHeight() / 2.0f;
			Velocity = 0;
			Body.MoveEdges(false);
			Invincibility = DamageCooldown;
			return true;
		}
	}

	return false;
}

void Player::ResetLasers()
{
	for (ite = 0; ite < NLasers; ite++)
		Lasers[ite].setActive(false);
}
