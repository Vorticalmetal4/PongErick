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
	Walls(nullptr),
	isInitialDistance(true),
	DeltaTime(0),
	Section(0),
	SectionWallsNumber(0),
	i(0),
	MovementIncrement(0),
	MovementDirection(None)
{
	switch (Number)
	{
		case 0:
			Type = Red;
			Color.r = Color.alpha = 255;
			Color.g = Color.b = 0;

		break;

		case 1:
			Type = Pink;
			Color.r = Color.alpha = 255;
			Color.g = 192;
			Color.g = 203;
		break;

		case 2:
			Type = Blue;
			Color.r = Color.g = 0;
			Color.b = Color.alpha = 255;
		break;

		default:
			Type = Orange;
			Color.r = Color.alpha = 255;
			Color.g = 165;
			Color.b = 0;
		break;

	}

	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Ghost: ConFileFailed");

	FirstPoint.x = (float)ConFile.GetInteger("Ghost", "InitialPositionX", 0);
	FirstPoint.y = (float)ConFile.GetInteger("Ghost", "InitialPositionY", 0);
	OwnDimensions.Width = OwnDimensions.Height = (float)ConFile.GetInteger("Ghost", "Size", 10);
	SearchPathIterations = ConFile.GetInteger("Ghost", "SearchPathIterations", 0);
	Speed = (float)ConFile.GetInteger("Ghost", "Speed", 0);
	HWidth = OwnDimensions.Width / 2.0f;
	HHeight = OwnDimensions.Height / 2.0f;
	Center.x = FirstPoint.x + HWidth;
	Center.y = FirstPoint.y - HHeight;
	cout << SearchPathIterations << endl;

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

	MovementDirection = None;

	switch (Type)
	{
		case Red:
			SearchPath(PlayerCurrentPosition, FirstPoint, SearchPathIterations, None);
		break;

		case Pink:
		
		break;

		case Blue:

		break;

		case Orange:

		break;
	}

	FirstPoint = Move(MovementDirection, FirstPoint);
	Rend->DrawSimpleRect(&FirstPoint, &OwnDimensions, Color.r, Color.g, Color.b, Color.alpha);
}

float Ghost::SearchPath(Position* Goal, Position RecPosition, int Iterations, EDirection LastDirection) 
{
	Position CurrentPosition;
	Position AuxPosition;
	Position AuxPosition2;
	Position CurrentCenter;
	EDirection CurrentDirection = None;

	CurrentPosition.x = RecPosition.x;
	CurrentPosition.y = RecPosition.y;
	CurrentCenter.x = CurrentPosition.x + HWidth;
	CurrentCenter.y = CurrentPosition.y + HHeight;

	float AuxDistance;
	float CurrentDistance = CalculateDistance(Goal, &CurrentCenter);

	MovementIncrement = Speed * DeltaTime;
	//Check Up
	AuxPosition.x = CurrentCenter.x;
	AuxPosition.y = CurrentCenter.y - MovementIncrement;
	AuxPosition2.x = CurrentPosition.x;
	AuxPosition2.y = CurrentPosition.y - MovementIncrement;
	if (!CheckCollisionWithWalls(&AuxPosition2) && LastDirection != Down)
	{
		if(Iterations > 0)
			AuxDistance = SearchPath(Goal, Move(Up, AuxPosition2), Iterations - 1, Up);
		else
			AuxDistance = CalculateDistance(Goal, &AuxPosition);

		if (AuxDistance < CurrentDistance)
		{
			CurrentDistance = AuxDistance;
			CurrentDirection = Up;
		}
	}

	//Check Down
	AuxPosition.y = CurrentCenter.y + MovementIncrement;
	AuxPosition2.y = CurrentPosition.y + MovementIncrement;
	if (!CheckCollisionWithWalls(&AuxPosition2) && LastDirection != Up)
	{
		if (Iterations > 0)
			AuxDistance = SearchPath(Goal, Move(Down, AuxPosition2), Iterations - 1, Down);
		else
			AuxDistance = CalculateDistance(Goal, &AuxPosition);

		if (AuxDistance < CurrentDistance)
		{
			CurrentDistance = AuxDistance;
			CurrentDirection = Down;
		}
	}

	//Check Left
	AuxPosition.y = CurrentCenter.y;
	AuxPosition.x = CurrentCenter.x - MovementIncrement;
	AuxPosition2.y = CurrentPosition.y;
	AuxPosition2.x = CurrentPosition.x - MovementIncrement;
	if (!CheckCollisionWithWalls(&AuxPosition2) && LastDirection != Right)
	{
		if (Iterations > 0)
			AuxDistance = SearchPath(Goal, Move(Left, AuxPosition2), Iterations - 1, Left);
		else
			AuxDistance = CalculateDistance(Goal, &AuxPosition);
			
		if (AuxDistance < CurrentDistance)
		{
			CurrentDistance = AuxDistance;
			CurrentDirection = Left;
		}
	}

	//CheckRight
	AuxPosition.x = CurrentCenter.x + MovementIncrement;
	AuxPosition2.x = CurrentPosition.x + MovementIncrement;
	if (!CheckCollisionWithWalls(&AuxPosition2) && LastDirection != Left)
	{
		if (Iterations > 0)
			AuxDistance = SearchPath(Goal, Move(Right, AuxPosition2), Iterations - 1, Right);
		else
			AuxDistance = CalculateDistance(Goal, &AuxPosition);

		if (AuxDistance < CurrentDistance)
		{
			CurrentDistance = AuxDistance;
			CurrentDirection = Right;
		}
	}

	if (Iterations == SearchPathIterations)
		MovementDirection = CurrentDirection;

	return CurrentDistance;
}

float Ghost::CalculateDistance(Position* Goal, Position* AuxPosition)
{
	return sqrtf(powf(AuxPosition->x - Goal->x, 2) + powf(AuxPosition->y - Goal->y, 2));;
}

void Ghost::UpdateSection()
{
	if (FirstPoint.x < VerticalSectionsLine)
	{
		if (FirstPoint.y < HorizontalSectionsLine)
			Section = 1;
		else
			Section = 3;
	}
	else
	{
		if (FirstPoint.y < HorizontalSectionsLine)
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

bool Ghost::CheckCollisionWithWalls(Position* AuxPosition2)
{
	for (i = 0; i < SectionWallsNumber; i++)
	{
		if (CollisionDetector->Square_Square(AuxPosition2, Walls[i].getPosition(), &OwnDimensions, Walls[i].getDimension()))
			return true;
	}

	return false;
}

Position Ghost::Move(EDirection NewDirection, Position CurrentPosition)
{
	switch (NewDirection)
	{
		case Up:
			CurrentPosition.y -= MovementIncrement;
		break;

		case Down:
			CurrentPosition.y += MovementIncrement;
		break;

		case Left:
			CurrentPosition.x -= MovementIncrement;
		break;

		case Right:
			CurrentPosition.x += MovementIncrement;
		break;

		default:

		break;
	}

	return CurrentPosition;
}