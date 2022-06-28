#include "Player.h"
#include "Inih/cpp/INIReader.h"
#include "Renderer.h"

#include <cmath>
#include <iostream>
using namespace std;

const double Pi = 3.141592;
const double Rad = Pi / 180;

Player::Player(Renderer* _Rend) 
	:Rend(_Rend),
	Velocity(0)
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

	H = sqrt(pow(HHeight, 2) + pow(HWidth, 2));
	
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

		default:
			if (Velocity - DecVelocity >= 0)
			{
				Velocity -= DecVelocity;

				Center.x += cos(ThirdPoint.Rotation) * Velocity * DeltaTime;
				Center.y -= sin(ThirdPoint.Rotation) * Velocity * DeltaTime;
				MovePoints(false);
			}
		break;
		
	}
	

	Rend->DrawTriangle(FirstPoint.x, FirstPoint.y, SecondPoint.x, SecondPoint.y, ThirdPoint.x, ThirdPoint.y, 255, 255, 255, 255);

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