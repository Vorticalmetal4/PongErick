#include "CommonFiles/Renderer.h"
#include "Inih/cpp/INIReader.h"
#include "Player.h"
#include "Map.h"
#include "Wall.h"
#include "Ghost.h"

#include <iostream>

Ghost::Ghost(Renderer* _Rend, CollisionSystem* _CollisionDetector, int Number, Player* _Pacman, Map* _LevelMap)
	:Rend(_Rend),
	Pacman(_Pacman),
	CollisionDetector(_CollisionDetector),
	LevelMap(_LevelMap),
	PlayerCurrentPosition(nullptr),
	AuxDistance(0),
	isInitialDistance(true)
{
	switch (Number)
	{
	case 0:
		Type = EGhostType::Red;
		Color.r = Color.alpha = 255;
		Color.g = Color.b = 0;

		break;

	case 1:
		Type = EGhostType::Pink;
		Color.r = Color.alpha = 255;
		Color.g = 192;
		Color.g = 203;
		break;

	case 2:
		Type = EGhostType::Blue;
		Color.r = Color.g = 0;
		Color.b = Color.alpha = 255;
		break;

	default:
		Type = EGhostType::Orange;
		Color.r = Color.alpha = 255;
		Color.g = 165;
		Color.b = 0;
		break;

		AuxPosition = FirstPoint;
	}

	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Ghost: ConFileFailed");

	FirstPoint.x = (float)ConFile.GetInteger("Ghost", "InitialPositionX", 0);
	FirstPoint.y = (float)ConFile.GetInteger("Ghost", "InitialPositionY", 0);
	OwnDimensions.Width = OwnDimensions.Height = ConFile.GetInteger("Ghost", "Size", 10);
	Speed = (float)ConFile.GetInteger("Ghost", "Speed", 0);
	HWidth = OwnDimensions.Width / 2.0f;
	HHeight = OwnDimensions.Height / 2.0f;

	VerticalSectionsLine = LevelMap->getMapWidth() / 2.0f;
	HorizontalSectionsLine = LevelMap->getMapHeight() + ConFile.GetInteger("Map", "ScoreSpace", 20);
}

Ghost::~Ghost()
{

}

void Ghost::Update()
{
	DeltaTime = Rend->getDeltaTime();
	PlayerCurrentPosition = Pacman->getCenter();
	Center.x = FirstPoint.x + HWidth;
	Center.y = FirstPoint.y + HHeight;
	
	UpdateSection();
	ObtainSectionWalls();
	CalculateDistance(true);

	switch (Type)
	{
		case Red:
			SearchPath(PlayerCurrentPosition);
		break;

		case Pink:
		
		break;

		case Blue:

		break;

		case Orange:

		break;
	}

	Rend->DrawSimpleRect(&FirstPoint, &OwnDimensions, Color.r, Color.g, Color.b, Color.alpha);
}

void Ghost::SearchPath(Position* Goal)
{
	MovementIncrement = Speed * DeltaTime;
	CurrentDirection = EDirection::None;

	//Check Up
	AuxPosition.x = Center.x;
	AuxPosition.y = Center.y - MovementIncrement;
	AuxPosition2.x = FirstPoint.x;
	AuxPosition2.y = FirstPoint.y - MovementIncrement;
	if (!CheckCollisionWithWalls())
	{
		if (CalculateDistance(false))
			CurrentDirection = EDirection::Up;
	}

	//Check Down
	AuxPosition.y = Center.y + MovementIncrement;
	AuxPosition2.y = FirstPoint.y + MovementIncrement;
	if (!CheckCollisionWithWalls())
	{
		if (CalculateDistance(false))
			CurrentDirection = EDirection::Down;
	}

	//Check Left
	AuxPosition.y = Center.y;
	AuxPosition.x = Center.x - MovementIncrement;
	AuxPosition2.y = FirstPoint.y;
	AuxPosition2.x = FirstPoint.x - MovementIncrement;
	if (!CheckCollisionWithWalls())
	{
		if (CalculateDistance(false))
			CurrentDirection = EDirection::Left;
	}

	//CheckRight
	AuxPosition.x = Center.x + MovementIncrement;
	AuxPosition2.x = FirstPoint.x + MovementIncrement;
	if (!CheckCollisionWithWalls())
	{
		if (CalculateDistance(false))
			CurrentDirection = EDirection::Right;
	}

	cout << CurrentDirection << endl;

	switch (CurrentDirection)
	{
		case Up:
			FirstPoint.y -= MovementIncrement;
		break;

		case Down:
			FirstPoint.y += MovementIncrement;
		break;

		case Left:
			FirstPoint.x -= MovementIncrement;
		break;
		
		case Right:
			FirstPoint.x += MovementIncrement;
		break;
	}

	isInitialDistance = true;

}

bool Ghost::CalculateDistance(bool isInitialDistance)
{
	AuxDistance = sqrtf(powf(AuxPosition.x - PlayerCurrentPosition->x, 2) + powf(AuxPosition.y - PlayerCurrentPosition->y, 2));

	if (isInitialDistance)
	{
		CurrentDistance = AuxDistance;
		isInitialDistance = false;
		return true;
	}
	else
	{
		if (AuxDistance < CurrentDistance)
		{
			CurrentDistance = AuxDistance;
			return true;
		}

		return false;
	}

}

void Ghost::UpdateSection()
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


void Ghost::ObtainSectionWalls()
{
	switch (Section)
	{
	case 1:
		Walls = LevelMap->getFirstSectionWalls();
		SectionWallsNumber = LevelMap->getFirstSectionWallsSize();
		break;

	case 2:
		Walls = LevelMap->getSecondSectionWalls();
		SectionWallsNumber = LevelMap->getSecondSectionWallsSize();
		break;

	case 3:
		Walls = LevelMap->getThirdSectionWalls();
		SectionWallsNumber = LevelMap->getThirdSectionWallsSize();
		break;

	case 4:
		Walls = LevelMap->getFourthSectionWalls();
		SectionWallsNumber = LevelMap->getFourthSectionWallsSize();
		break;
	}

}

bool Ghost::CheckCollisionWithWalls()
{
	for (i = 0; i < SectionWallsNumber; i++)
	{
		if (CollisionDetector->Square_Square(&AuxPosition2, Walls[i].getPosition(), &OwnDimensions, Walls[i].getDimension()))
			return true;
	}

	return false;
}