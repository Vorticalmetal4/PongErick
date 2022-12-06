#include "CommonFiles/Renderer.h"
#include "Inih/cpp/INIReader.h"
#include "Player.h"
#include "Ghost.h"

#include <iostream>

Ghost::Ghost(Renderer* _Rend, CollisionSystem* _CollisionDetector, int Number, Player* _Pacman)
	:Rend(_Rend),
	Pacman(_Pacman),
	CollisionDetector(_CollisionDetector),
	PlayerCurrentPosition(nullptr),
	AuxDistance(0)
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
}

Ghost::~Ghost()
{

}

void Ghost::Update()
{
	DeltaTime = Rend->getDeltaTime();
	PlayerCurrentPosition = Pacman->getCenter();
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
	//Check Up
	AuxPosition.x = FirstPoint.x;
	AuxPosition.y = (FirstPoint.y - Speed * DeltaTime) + HHeight;
	if (CalculateDistance(false))
		CurrentDirection = EDirection::Up;

	//Check Down
	AuxPosition.y = (FirstPoint.y + Speed * DeltaTime) + HHeight;
	if (CalculateDistance(false))
		CurrentDirection = EDirection::Down;

	//Check Left
	AuxPosition.y = FirstPoint.y;
	AuxPosition.x = (FirstPoint.x - Speed * DeltaTime) + HWidth;
	if (CalculateDistance(false))
		CurrentDirection = EDirection::Left;

	//CheckRight
	AuxPosition.x = (FirstPoint.x + Speed * DeltaTime) + HWidth;
	if (CalculateDistance(false))
		CurrentDirection = EDirection::Left;

	switch (CurrentDirection)
	{
		case Up:
			FirstPoint.y += Speed * DeltaTime;
		break;

		case Down:
			FirstPoint.y -= Speed * DeltaTime;
		break;

		case Left:
			FirstPoint.x -= Speed * DeltaTime;
		break;
		
		case Right:
			FirstPoint.x += Speed * DeltaTime;
		break;
	}

}

bool Ghost::CalculateDistance(bool isInitialDistance)
{
	AuxDistance = sqrtf(powf(AuxPosition.x - PlayerCurrentPosition->x, 2) + powf(AuxPosition.y - PlayerCurrentPosition->y, 2));

	if (isInitialDistance)
	{
		CurrentDistance = AuxDistance;
		return false;
	}
	else
	{
		if (AuxDistance < CurrentDistance)
		{
			CurrentDistance = AuxDistance;
			return true;
		}
	}

}