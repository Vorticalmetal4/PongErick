#include "Player.h"
#include "CommonFiles/Renderer.h"
#include "Wall.h"
#include "Map.h"

#include "Inih/cpp/INIReader.h"

#include <iostream>
using namespace std;

const float Pi = (float)3.141592;
const float Rad = Pi / 180;
int it;

Player::Player(Renderer* _Rend, CollisionSystem* _CollisionDetector, Map* _LevelMap)
	:Rend(_Rend),
	CollisionDetector(_CollisionDetector),
	DeltaTime(0.0f),
	MouthIncrement(-1),
	Section(3),
	LevelMap(_LevelMap)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Player: ConFile Failed");

	Center.x = (float)ConFile.GetInteger("Player", "InitialPositionX", 10);
	Center.y = (float)ConFile.GetInteger("Player", "InitialPositionY", 10);
	Center.Angle = ConFile.GetInteger("Player", "InitialAngle", 45);
	Center.Rotation = Center.Angle * Rad;
	Speed = ConFile.GetInteger("Player", "Speed", 200);
	Radius = (float)ConFile.GetInteger("Player", "Radius", 10);
	MouthSize = ConFile.GetInteger("Player", "MouthSize", 30);
	ActualMouthSize = (float)MouthSize;
	MouthSpeed = ConFile.GetInteger("Player", "MouthSpeed", 200);

	VerticalSectionsLine = LevelMap->getMapWidth() / 2.0f;
	HorizontalSectionsLine = (LevelMap->getMapHeight() + ConFile.GetInteger("Map", "ScoreSpace", 20));

	/*std::cout << HorizontalSectionsLine << std::endl;
	std::cout << VerticalSectionsLine << std::endl;*/

	AdjustMouthAngles();
}


Player::~Player()
{

}

void Player::Update()
{

	DeltaTime = Rend->getDeltaTime();

	UpdateSection();
	ObtainSectionWalls();
	std::cout << Section << std::endl;

	if (Center.x < 0)
		Center.x = (float)Rend->getWindowHeight();
	else if (Center.x > Rend->getWindowHeight())
		Center.x = 0;

	if (ActualMouthSize >= MouthSize)
		MouthIncrement = -1;
	else if (ActualMouthSize <= 0)
		MouthIncrement = 1;

	ActualMouthSize += DeltaTime * MouthIncrement * MouthSpeed;
	AuxPos = Center;

	switch(Rend->CheckMovement())
	{
		case 'R':
			Center.Angle = 0;
		break;

		case 'L':
			Center.Angle = 180;
		break;

		case 'U':
			Center.Angle = 90;
		break;

		case 'D':
			Center.Angle = 270;
		break;

		default:

		break;
	}
		
	if(Center.Angle == 0)
		Center.x += Speed * DeltaTime;
	else if(Center.Angle == 90)
		Center.y -= Speed * DeltaTime;
	else if(Center.Angle == 180)
		Center.x -= Speed * DeltaTime;
	else
		Center.y += Speed * DeltaTime;

	for (it = 0; it < SectionNWalls; it++)
	{
		if (CollisionDetector->Circle_Square(&Center, Walls[it].getPosition(), Radius, Walls[it].getDimension()))
		{
			Center = AuxPos;
			break;
		}
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

void Player::UpdateSection()
{
	if (Center.x < VerticalSectionsLine)
	{
		if (Center.y < HorizontalSectionsLine)
			Section = 1;
		else
			Section = 3;
	}
	else
	{
		if (Center.y < HorizontalSectionsLine)
			Section = 2;
		else
			Section = 4;
	}
}

void Player::ObtainSectionWalls()
{
	switch (Section)
	{
		case 1:
			Walls = LevelMap->getFirstSectionWalls();
			SectionNWalls = LevelMap->getFirstSectionWallsSize();
		break;

		case 2:
			Walls = LevelMap->getSecondSectionWalls();
			SectionNWalls = LevelMap->getSecondSectionWallsSize();
		break;

		case 3:
			Walls = LevelMap->getThirdSectionWalls();
			SectionNWalls = LevelMap->getThirdSectionWallsSize();
		break;

		case 4:
			Walls = LevelMap->getFourthSectionWalls();
			SectionNWalls = LevelMap->getFourthSectionWallsSize();
		break;
	}

}