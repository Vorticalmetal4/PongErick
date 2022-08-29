#include "Player.h"
#include "Renderer.h"

#include "Inih/cpp/INIReader.h"

#include <iostream>
using namespace std;

const float Pi = (float)3.141592;
const float Rad = Pi / 180;

Player::Player(Renderer* _Rend)
	:Rend(_Rend),
	DeltaTime(0.0f),
	MouthIncrement(-1)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("AsteroidsWindow");

	Center.x = (float)ConFile.GetInteger("Player", "InitialPositionX", 10);
	Center.y = (float)ConFile.GetInteger("Player", "InitialPositionY", 10);
	Center.Angle = ConFile.GetInteger("Player", "InitialAngle", 45);
	Center.Rotation = Center.Angle * Rad;
	Speed = ConFile.GetInteger("Player", "Speed", 200);
	Radius = ConFile.GetInteger("Player", "Radius", 10);
	MouthSize = ConFile.GetInteger("Player", "MouthSize", 30);
	ActualMouthSize = (float)MouthSize;
	MouthSpeed = ConFile.GetInteger("Player", "MouthSpeed", 200);

	AdjustMouthAngles();
}


Player::~Player()
{

}

void Player::Update()
{

	DeltaTime = Rend->getDeltaTime();

	if (ActualMouthSize >= MouthSize)
		MouthIncrement = -1;
	else if (ActualMouthSize <= 0)
		MouthIncrement = 1;

	ActualMouthSize += DeltaTime * MouthIncrement * MouthSpeed;

	switch(Rend->CheckMovement())
	{
		case 'R':
			Center.Angle = 0;
			Center.x += Speed * DeltaTime;
		break;

		case 'L':
			Center.Angle = 180;
			Center.x -= Speed * DeltaTime;
		break;

		case 'U':
			Center.Angle = 90;
			Center.y -= Speed * DeltaTime;
		break;

		case 'D':
			Center.Angle = 270;
			Center.y += Speed * DeltaTime;
		break;

		default:

		break;
	}

	AdjustMouthAngles();
	Rend->DrawIncompleteCircle(&Center, Radius, 255, 255, 0, 255, FirstMouthAngle, SecondMouthAngle);
}



void Player::AdjustMouthAngles()
{
	if (Center.Angle > 0)
	{
		FirstMouthAngle = Center.Angle - ActualMouthSize;
		SecondMouthAngle = Center.Angle + ActualMouthSize;
	}
	else
	{
		FirstMouthAngle = ActualMouthSize + Center.Angle;
		SecondMouthAngle = 360 - ActualMouthSize;	
	}
}

