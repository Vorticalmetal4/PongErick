#include "Player.h"
#include "Inih/cpp/INIReader.h"
#include "Renderer.h"
#include "Laser.h"
#include "Asteroid.h"
#include "EnemyShip.h"

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const float Pi = (float)3.141592;
const float Rad = Pi / 180;
int i;

Player::Player(Renderer* _Rend)
	:Rend(_Rend),
	Velocity(0),
	CurrentCooldown(0),
	Lasers(nullptr)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Player");

	MaxVelocity = ConFile.GetInteger("Player", "MaxVelocity", 0);
	IncVelocity = ConFile.GetInteger("Player", "IncVelocity", 0);
	DecVelocity = IncVelocity / 2;
	RotationVelocity = ConFile.GetInteger("Player", "RotationVelocity", 0);
	Width = ConFile.GetInteger("Player", "Width", 0);
	float HWidth = Width / 2.0f;
	Height = ConFile.GetInteger("Player", "Height", 0);
	float HHeight = Height / 2.0f;
	FirstPoint.x = (float)ConFile.GetInteger("Player", "PositionX", 0);
	FirstPoint.y = SecondPoint.y = (float)ConFile.GetInteger("Player", "PositionY", 0);
	FirstPoint.Angle = 315;
	SecondPoint.x = FirstPoint.x + Width;
	SecondPoint.Angle = 225;
	ThirdPoint.x = FirstPoint.x + HWidth;
	ThirdPoint.y = FirstPoint.y - Height;
	ThirdPoint.Angle = 90;
	Center.x = FirstPoint.x + HWidth;
	Center.y = FirstPoint.y - HHeight;
	ShootCooldown = ConFile.GetInteger("Player", "ShootCooldown", 0);
	Invincibility = DamageCooldown = (float)ConFile.GetInteger("Player", "DamageCooldown", 0);

	H = sqrtf(powf(HHeight, 2) + powf(HWidth, 2));


	/*for (int i = 0; i < ConFile.GetInteger("Player", "NLasers", 0); i++)
	{
		Laser NLaser = Laser(Rend);
		Lasers.push_back(NLaser); // NOTE(isaveg): makes more sense to have a dynamic C array type, and not the vector
	}*/

	std::cout << sizeof(Laser) << " " << sizeof(Renderer) << endl;
	int NLasers = ConFile.GetInteger("Player", "NLasers", 0);
	Lasers = (Laser*)malloc(NLasers * sizeof(Laser));
	for (int i = 0; i < NLasers; i++)
	{
		//Laser* NLaser = new Laser(Rend);
		Lasers[i] = Laser(Rend);
	}
	
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
				for (i = 0; i < sizeof(Lasers); i++)
				{
					if (!Lasers[i].getActive())
					{
						Lasers[i].setActive(true);
						Lasers[i].setPosition(ThirdPoint.x, ThirdPoint.y, ThirdPoint.Angle, ThirdPoint.Rotation);
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

		for (i = 0; i < sizeof(Lasers); i++)
			if(Lasers[i].getActive())
				Lasers[i].Update(Pause);
	}

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

	FirstPoint.x = Center.x + cosf(FirstPoint.Rotation) * H;
	FirstPoint.y = Center.y - sinf(FirstPoint.Rotation) * H;
	SecondPoint.x = Center.x + cosf(SecondPoint.Rotation) * H;
	SecondPoint.y = Center.y - sinf(SecondPoint.Rotation) * H;
	ThirdPoint.x = Center.x + cosf(ThirdPoint.Rotation) * H;
	ThirdPoint.y = Center.y - sinf(ThirdPoint.Rotation) * H;
}

bool Player::CheckLasersCollisions(Position* Pos, double ObjectH)
{
	for(i = 0; i < sizeof(Lasers); i++)
	{
		if (Lasers[i].getActive())

			if (Lasers[i].CheckCollision(Pos, ObjectH))
				return true;
		
	}

	return false;
}

bool Player::CheckCollisions(Position* Pos, double ObjectH)
{
	if (Invincibility <= 0)
	{
		if (sqrt(pow(Center.x - Pos->x, 2) + pow(Center.y - Pos->y, 2)) < H + ObjectH)
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
	for (i = 0; i < sizeof(Lasers); i++)
		Lasers[i].setActive(false);
}
