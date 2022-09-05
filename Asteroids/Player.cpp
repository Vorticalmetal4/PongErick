#include "Player.h"
#include "Inih/cpp/INIReader.h"
#include "CommonFiles/Renderer.h"
#include "Laser.h"
#include "Asteroid.h"
#include "EnemyShip.h"

#include <cmath>

const float Pi = (float)3.141592;
const float Rad = Pi / 180;
int it;

Player::Player(Renderer* _Rend, CollisionSystem* _CollisionDetector)
	:Rend(_Rend),
	CollisionDetector(_CollisionDetector),
	Velocity(0),
	CurrentCooldown(0)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Player: ConFile Failed");

	MaxVelocity = ConFile.GetInteger("Player", "MaxVelocity", 0);
	IncVelocity = ConFile.GetInteger("Player", "IncVelocity", 0);
	DecVelocity = IncVelocity / 2;
	RotationVelocity = ConFile.GetInteger("Player", "RotationVelocity", 0);
	OwnDimensions.Width = ConFile.GetInteger("Player", "Width", 0);
	float HWidth = OwnDimensions.Width / 2.0f;
	OwnDimensions.Height = ConFile.GetInteger("Player", "Height", 0);
	float HHeight = OwnDimensions.Height / 2.0f;
	FirstPoint.x = (float)ConFile.GetInteger("Player", "PositionX", 0);
	FirstPoint.y = SecondPoint.y = (float)ConFile.GetInteger("Player", "PositionY", 0);
	FirstPoint.Angle = 315;
	SecondPoint.x = FirstPoint.x + OwnDimensions.Width;
	SecondPoint.Angle = 225;
	ThirdPoint.x = FirstPoint.x + HWidth;
	ThirdPoint.y = FirstPoint.y - OwnDimensions.Height;
	ThirdPoint.Angle = 90;
	Center.x = FirstPoint.x + HWidth;
	Center.y = FirstPoint.y - HHeight;
	ShootCooldown = ConFile.GetInteger("Player", "ShootCooldown", 0);
	Invincibility = DamageCooldown = (float)ConFile.GetInteger("Player", "DamageCooldown", 0);

	OwnDimensions.Hypotenuse = sqrtf(powf(HHeight, 2) + powf(HWidth, 2));

	NLasers = ConFile.GetInteger("Player", "NLasers", 0);
	
	Lasers = nullptr;
	Lasers =  new Laser[NLasers]; // NOTE(isaveg): Memory leak

	if (Rend != nullptr)
		for (it = 0; it < NLasers; it++)
				Lasers[it] = Laser(Rend, CollisionDetector);

	MovePoints(true);
}


Player::~Player()
{
}

void Player::Update(bool Pause)
{
	if (!Pause)
	{
		DeltaTime = Rend->getDeltaTime();

		Rotation = (int)(RotationVelocity * DeltaTime);

		switch (Rend->CheckMovement())
		{
		case 'R':
			FirstPoint.Angle -= Rotation;
			SecondPoint.Angle -= Rotation;
			ThirdPoint.Angle -= Rotation;

			MovePoints(true);
			break;

		case 'L':
			FirstPoint.Angle += Rotation;
			SecondPoint.Angle += Rotation;
			ThirdPoint.Angle += Rotation;

			MovePoints(true);
			break;

		case 'U':
			if (Velocity + IncVelocity <= MaxVelocity)
				Velocity += IncVelocity;

			Center.x += cosf(ThirdPoint.Rotation) * Velocity * DeltaTime;
			Center.y -= sinf(ThirdPoint.Rotation) * Velocity * DeltaTime;
			MovePoints(false);
			break;

		case 'S':
			if (CurrentCooldown <= 0)
			{
				CurrentCooldown = ShootCooldown;
				for (it = 0; it < NLasers; it++)
				{
					if (!Lasers[it].getActive())
					{
						Lasers[it].setActive(true);
						Lasers[it].setPosition(ThirdPoint.x, ThirdPoint.y, ThirdPoint.Angle, ThirdPoint.Rotation);
						break;
					}
				}
			}
			break;

		}

		if (Velocity - DecVelocity >= 0)
		{
			Velocity -= DecVelocity;

			Center.x += cosf(ThirdPoint.Rotation) * Velocity * DeltaTime;
			Center.y -= sinf(ThirdPoint.Rotation) * Velocity * DeltaTime;
			MovePoints(false);
		}

		if (Center.x > Rend->getWindowWidth())
			Center.x = 0;
		else if (Center.x < 0)
			Center.x = (float)Rend->getWindowWidth();

		if (Center.y > Rend->getWindowHeight())
			Center.y = 0;
		else if (Center.y < 0)
			Center.y = (float)Rend->getWindowHeight();

		CurrentCooldown--;
		Invincibility -= DeltaTime;
	}

	for (it = 0; it < NLasers; it++)
		if (Lasers[it].getActive())
			Lasers[it].Update(Pause);

	if(Invincibility <= 0)
		Rend->DrawTriangle(&FirstPoint, &SecondPoint, &ThirdPoint, 255, 255, 255, 255);
	else
		Rend->DrawTriangle(&FirstPoint, &SecondPoint, &ThirdPoint, 255, 255, 0, 255);
} 

void Player::MovePoints(bool Rotation) 
{	
	if(Rotation)
	{
		FirstPoint.Rotation = FirstPoint.Angle * Rad;
		SecondPoint.Rotation = SecondPoint.Angle * Rad;
		ThirdPoint.Rotation = ThirdPoint.Angle * Rad;
	}

	FirstPoint.x = Center.x + cosf(FirstPoint.Rotation) * OwnDimensions.Hypotenuse;
	FirstPoint.y = Center.y - sinf(FirstPoint.Rotation) * OwnDimensions.Hypotenuse;
	SecondPoint.x = Center.x + cosf(SecondPoint.Rotation) * OwnDimensions.Hypotenuse;
	SecondPoint.y = Center.y - sinf(SecondPoint.Rotation) * OwnDimensions.Hypotenuse;
	ThirdPoint.x = Center.x + cosf(ThirdPoint.Rotation) * OwnDimensions.Hypotenuse;
	ThirdPoint.y = Center.y - sinf(ThirdPoint.Rotation) * OwnDimensions.Hypotenuse;
}

bool Player::CheckLasersCollisions(Position* OtherObjectPos, Dimension* OtherObjectDimensions, bool isObjectASquare)
{
	for(it = 0; it < NLasers; it++)
	{
		if (Lasers[it].getActive())

			if (Lasers[it].CheckCollision(OtherObjectPos, OtherObjectDimensions, isObjectASquare))
				return true;
	}

	return false;
}

bool Player::CheckCollisions(Position* OtherObjectPos, float OtherObjectHypotenuse)
{
	if (Invincibility <= 0)
	{
		if (CollisionDetector->Circle_Circle(&Center, OtherObjectPos, OwnDimensions.Hypotenuse, OtherObjectHypotenuse))
		{
			Center.x = Rend->getWindowWidth() / 2.0f;
			Center.y = Rend->getWindowHeight() / 2.0f;
			Velocity = 0;
			MovePoints(false);
			Invincibility = DamageCooldown;
			return true;
		}
	}

	return false;
}

void Player::ResetLasers()
{
	for (it = 0; it < NLasers; it++)
		Lasers[it].setActive(false);
}
