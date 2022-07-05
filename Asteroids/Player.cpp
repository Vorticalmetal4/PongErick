#include "Player.h"
#include "Inih/cpp/INIReader.h"
#include "Renderer.h"
#include "Laser.h"
#include "Asteroid.h"

#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

const double Pi = 3.141592;
const double Rad = Pi / 180;
int i;

Player::Player(Renderer* _Rend) 
	:Rend(_Rend),
	Velocity(0),
	CurrentCooldown(0)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Player");

	MaxVelocity = ConFile.GetInteger("Player", "MaxVelocity", 0);
	IncVelocity = ConFile.GetInteger("Player", "IncVelocity", 0);
	DecVelocity = IncVelocity / 2;
	RotationVelocity = ConFile.GetInteger("Player", "RotationVelocity", 0);
	Width = ConFile.GetInteger("Player", "Width", 0);
	int HWidth = Width / 2;
	Height = ConFile.GetInteger("Player", "Height", 0);
	int HHeight = Height / 2;
	FirstPoint.x = ConFile.GetInteger("Player", "PositionX", 0);
	FirstPoint.y =  SecondPoint.y = ConFile.GetInteger("Player", "PositionY", 0);
	FirstPoint.Angle = 315;
	SecondPoint.x = FirstPoint.x + Width;
	SecondPoint.Angle = 225;
	ThirdPoint.x = FirstPoint.x + HWidth;
	ThirdPoint.y = FirstPoint.y - Height;
	ThirdPoint.Angle = 90;
	Center.x = FirstPoint.x + HWidth;
	Center.y = FirstPoint.y - HHeight;
	ShootCooldown = ConFile.GetInteger("Player", "ShootCooldown", 0);

	H = sqrt(pow(HHeight, 2) + pow(HWidth, 2));

	for(int i = 0; i < ConFile.GetInteger("Player", "NLasers", 0); i++)
	{
		Laser NLaser = Laser(Rend);
		Lasers.push_back(NLaser);
	}
	

	MovePoints(true);
}


Player::~Player()
{
}

void Player::Update()
{
	DeltaTime = Rend->getDeltaTime();

	switch(Rend->CheckMovement())
	{
		case 'R':
			/*FirstPoint.Angle -= (RotationVelocity * DeltaTime);
			SecondPoint.Angle -= (RotationVelocity * DeltaTime);
			ThirdPoint.Angle -= (RotationVelocity * DeltaTime);*/
			FirstPoint.Angle -= RotationVelocity;
			SecondPoint.Angle -= RotationVelocity;
			ThirdPoint.Angle -= RotationVelocity;

			MovePoints(true);
		break;

		case 'L':
			FirstPoint.Angle += RotationVelocity;
			SecondPoint.Angle += RotationVelocity;
			ThirdPoint.Angle += RotationVelocity;

			MovePoints(true);
		break;

		case 'U':
			if (Velocity + IncVelocity <= MaxVelocity)
				Velocity += IncVelocity;

			Center.x += cos(ThirdPoint.Rotation) * Velocity * DeltaTime;
			Center.y -= sin(ThirdPoint.Rotation) * Velocity * DeltaTime;
			MovePoints(false);
		break;

		case 'S':
			if (CurrentCooldown <= 0)
			{
				CurrentCooldown = ShootCooldown;
				for(i = 0; i < Lasers.size(); i++)
				{
					if(!Lasers[i].getActive())
					{
						Lasers[i].setActive(true);
						Lasers[i].setPosition(ThirdPoint.x, ThirdPoint.y, ThirdPoint.Angle,ThirdPoint.Rotation);
						break;
					}
				}
			}
		break;
		
	}
	
	if (Velocity - DecVelocity >= 0)
	{
		Velocity -= DecVelocity;

		Center.x += cos(ThirdPoint.Rotation) * Velocity * DeltaTime;
		Center.y -= sin(ThirdPoint.Rotation) * Velocity * DeltaTime;
		MovePoints(false);
	}

	if (Center.x > Rend->getWindowWidth())
		Center.x = 0;
	else if (Center.x < 0)
		Center.x = Rend->getWindowWidth();

	if (Center.y > Rend->getWindowHeight())
		Center.y = 0;
	else if (Center.y < 0)
		Center.y = Rend->getWindowHeight();

	for (i = 0; i < Lasers.size(); i++)
		Lasers[i].Update();

	CurrentCooldown--;
	Rend->DrawTriangle(&FirstPoint, &SecondPoint, &ThirdPoint, 255, 255, 255, 255);
}

void Player::MovePoints(bool Rotation) 
{	
	if(Rotation)
	{
		FirstPoint.Rotation = FirstPoint.Angle * Rad;
		SecondPoint.Rotation = SecondPoint.Angle * Rad;
		ThirdPoint.Rotation = ThirdPoint.Angle * Rad;
	}

	FirstPoint.x = Center.x + cos(FirstPoint.Rotation) * H;
	FirstPoint.y = Center.y - sin(FirstPoint.Rotation) * H;
	SecondPoint.x = Center.x + cos(SecondPoint.Rotation) * H;
	SecondPoint.y = Center.y - sin(SecondPoint.Rotation) * H;
	ThirdPoint.x = Center.x + cos(ThirdPoint.Rotation) * H;
	ThirdPoint.y = Center.y - sin(ThirdPoint.Rotation) * H;
}

void Player::CheckCollisionWLasers(Asteroid* CurrAsteroid)
{
	for(i = 0; i < Lasers.size(); i++)
	{
		if(Lasers[i].getActive())
		
			if (Lasers[i].CheckCollision(CurrAsteroid))
				break;
		
	}
}