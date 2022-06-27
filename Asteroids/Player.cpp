#include "Player.h"
#include "Inih/cpp/INIReader.h"
#include "Renderer.h"

#include <cmath>
#include <iostream>
using namespace std;

const float Pi = 3.141592;
const float Rad = Pi / 180;

Player::Player(Renderer* _Rend) 
	:Rend(_Rend)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Player");

	Velocity.x = Velocity.y = ConFile.GetInteger("Player", "PlayerVelocity", 0);
	Width = ConFile.GetInteger("Player", "Width", 0);
	HWidth = Width / 2;
	Height = ConFile.GetInteger("Player", "Height", 0);
	HHeight = Height / 2;
	FirstPoint.x = ConFile.GetInteger("Player", "PositionX", 0);
	FirstPoint.y =  SecondPoint.y = ConFile.GetInteger("Player", "PositionY", 0);
	FirstPoint.Angle = 0;
	SecondPoint.x = FirstPoint.x + Width;
	SecondPoint.Angle = 135;
	ThirdPoint.x = FirstPoint.x + Width / 2;
	ThirdPoint.y = FirstPoint.y - Height;
	ThirdPoint.Angle = 225;
	Center.x = FirstPoint.x + HWidth;
	Center.y = FirstPoint.y - HHeight;

	H = sqrt(pow(HHeight, 2) + pow(HWidth, 2));

}


Player::~Player()
{
}

void Player::Update()
{

	

	switch(Rend->CheckMovement())
	{
		case 'R':
			FirstPoint.Angle--;
			SecondPoint.Angle--;
			ThirdPoint.Angle--;

			Rotation();
		break;

		case 'L':
			FirstPoint.Angle++;
			SecondPoint.Angle++;
			ThirdPoint.Angle++;

			Rotation();
		break;

		case 'U':

		break;
	}
	
	Rend->DrawTriangle(FirstPoint.x, FirstPoint.y, SecondPoint.x, SecondPoint.y, ThirdPoint.x, ThirdPoint.y, 255, 255, 255, 255);

}

void Player::Rotation() 
{
	FirstPoint.Rotation = FirstPoint.Angle * Rad;
	SecondPoint.Rotation = SecondPoint.Angle * Rad;
	ThirdPoint.Rotation = ThirdPoint.Angle * Rad;
	FirstPoint.x = Center.x + cos(FirstPoint.Rotation) * H;
	FirstPoint.y = Center.y - sin(FirstPoint.Rotation) * H;
	SecondPoint.x = Center.x + cos(SecondPoint.Rotation) * H;
	SecondPoint.y = Center.y - sin(SecondPoint.Rotation) * H;
	ThirdPoint.x = Center.x + cos(ThirdPoint.Rotation) * H;
	ThirdPoint.y = Center.y - sin(ThirdPoint.Rotation) * H;
}